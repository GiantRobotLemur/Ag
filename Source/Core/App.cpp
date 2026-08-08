//! @file Core/App.cpp
//! @brief The definition of an object which represents the root of an
//! application object hierarchy.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "Ag/Core/App.hpp"
#include "Ag/Core/ProgramArguments.hpp"
#include "Ag/Core/ErrorGuard.hpp"
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utf.hpp"
#include "CoreInternal.hpp"
#include "FsPathSchema.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An object describing a command line to be processed.
struct CommandLineInfo
{
    //! @brief The object which will parse the command line.
    CommandLineUPtr Manager;

    //! @brief Receives an error message if command line parsing fails.
    String Error;

    //! @brief The WinMain() Unicode command line.
    wchar_cptr_t CommandLine;

    //! @brief The count of elements in the Args array.
    int ArgCount;

    //! @brief The main() command line arguments to parse.
    const char * const *Args;

    //! @brief The wmain() command line arguments to parse.
    const wchar_t * const *WideArgs;

    //! @brief Indicates whether parsing was successful.
    bool Success;

    //! @brief Constructs an object describing a console of POSIX command line.
    CommandLineInfo(Ag::CommandLineUPtr &&processor, int argc, const char * const *argv) :
        Manager(std::move(processor)),
        CommandLine(nullptr),
        ArgCount(argc),
        Args(argv),
        WideArgs(nullptr),
        Success(false)
    {
    }

    //! @brief Constructs an object describing a console of a Unicode command line.
    CommandLineInfo(Ag::CommandLineUPtr &&processor, int argc, const wchar_t *const *argv) :
        Manager(std::move(processor)),
        CommandLine(nullptr),
        ArgCount(argc),
        Args(nullptr),
        WideArgs(argv),
        Success(false)
    {
    }

    //! @brief Constructs an object describing a the command line for a Win32
    //! application which uses WinMain() as its entry point.
    CommandLineInfo(Ag::CommandLineUPtr &&processor, wchar_cptr_t commandLine) :
        Manager(std::move(processor)),
        CommandLine(commandLine),
        ArgCount(0),
        Args(nullptr),
        WideArgs(nullptr),
        Success(false)
    {
    }
};

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static App *g_singletonApp = nullptr;

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Makes a path element with a '.' prefix if not already done.
//! @param[in] element The element to optionally prefix.
//! @param[in,out] needsHiddenRoot True if the element should have the prefix
//! added, then it will be updated to false. False if the prefix has already
//! been added to a previous path element.
//! @returns The value of @p element, possibly prefixed with '.'.
String makeHiddenElement(string_cref_t element, bool &needsHiddenRoot)
{
    if (needsHiddenRoot)
    {
        std::string builder;
        builder.reserve(element.getUtf8Length() + 1);
        builder.push_back('.');
        appendAgString(builder, element);

        needsHiddenRoot = false;
        return String(builder);
    }

    return element;
}

//! @brief Appends elements to a path if they are non-empty.
//! @param[in] path The path to append to.
//! @param[in] company The optional company name path element.
//! @param[in] product The optional product name path element.
//! @param[in] app The application name path element, which is always added.
//! @param[in] makeHidden True if the first path element appended should be
//! prefixed with a '.' character to mark it as hidden in POSIX semantics.
void appendAppElements(Fs::PathBuilder &path, string_cref_t company,
                       string_cref_t product, string_cref_t app,
                       bool makeHidden = false)
{
    bool needsRoot = makeHidden;

    if (company.isEmpty() == false)
        path.pushElement(makeHiddenElement(company, needsRoot));

    if (product.isEmpty() == false)
        path.pushElement(makeHiddenElement(product, needsRoot));

    path.pushElement(makeHiddenElement(app, needsRoot));
}

//! @brief Attempts to parse command line arguments in a guarded context.
//! @param[in,out] info A structure holding the parameters to parse, the object
//! to parse them and which will be updated with the result.
void guardedTryParse(CommandLineInfo &info)
{
    if (info.CommandLine != nullptr)
    {
        info.Success = info.Manager->tryParse(info.CommandLine, info.Error);
    }
    else if (info.ArgCount > 0)
    {
        if (info.Args != nullptr)
        {
            info.Success = info.Manager->tryParse(info.ArgCount, info.Args,
                                                  info.Error);
        }
        else if (info.WideArgs != nullptr)
        {
            info.Success = info.Manager->tryParse(info.ArgCount, info.WideArgs,
                                                  info.Error);
        }
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// AppPaths Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object with paths derived from the name and location
//! of the application binary file.
AppPaths::AppPaths()
{
    // Create basic App metadata based on the name of the program file.
    String programName = Fs::Path::getProgramFile().getFileBaseName();
    std::string_view empty;

    AppMetadata fakeData(Version(1, 0, 0, 0), programName.toUtf8View(),
                         programName.toUtf8View(), empty, empty, empty,
                         empty, empty);

    initialise(fakeData, true);
}

//! @brief Constructs an object with paths derived from application metadata,
//! specifically the company, product and application name.
//! @param[in] appInfo The application metadata used to derive application-centric
//! path element names.
//! @param[in] stripSpaces True to remove spaces from path element names, false
//! to leave them in.
AppPaths::AppPaths(const AppMetadata &appInfo, bool stripSpaces /* = true */)
{
    initialise(appInfo, stripSpaces);
}

//! @brief Gets the absolute path to an application-centric directory.
//! @param[in] dirID The identifier of the directory  to query.
//! @returns The resolved canonical path to the application-centric directory.
//! @throws ArgumentException Thrown if @p dirID is out of range.
const Fs::PathBuilder &AppPaths::getPath(AppDir dirID) const
{
    if (dirID >= AppDir::Max)
        throw ArgumentException("Invalid application path identifier.", "dirID");

    return _roots[toScalar(dirID)];
}

//! @brief Gets the absolute path to an application-centric resource.
//! @param[in] dirID The identifier of the directory the path should be resolved
//! relative to.
//! @param[in] relativePath The relative path to the resource within the
//! known application directory structure.
//! @returns The resolved canonical path to the resource.
//! @throws ArgumentException Thrown if @p dirID is out of range.
//! @throws Fs::InvalidFilePathException Thrown if @p relativePath is not a
//! valid path, but not if it is blank.
Fs::Path AppPaths::getPath(AppDir dirID, string_cref_t relativePath) const
{
    if (dirID >= AppDir::Max)
        throw ArgumentException("Invalid application path identifier.", "dirID");

    if (relativePath.isEmpty())
        return _roots[toScalar(dirID)];

    Fs::PathBuilder inputPath;
    String error;

    if (inputPath.tryParse(relativePath, error) == false)
        throw Fs::InvalidFilePathException(relativePath, error);

    return getPath(dirID, inputPath);
}

//! @brief Gets the absolute path to an application-centric resource.
//! @param[in] dirID The identifier of the directory the path should be resolved
//! relative to.
//! @param[in] relativePath The relative path to the resource within the
//! known application directory structure.
//! @returns The resolved canonical path to the resource.
//! @throws ArgumentException Thrown if @p dirID is out of range.
//! @throws Fs::InvalidFilePathException Thrown if @p relativePath is not a
//! valid path, but not if it is empty.
Fs::Path AppPaths::getPath(AppDir dirID, const Fs::Path &relativePath) const
{
    if (dirID >= AppDir::Max)
        throw ArgumentException("Invalid application path identifier.", "dirID");

    // If the path isn't relative, there is no point resolving anything.
    if (relativePath.hasRoot())
        return relativePath;

    const Fs::PathBuilder &rootPath = _roots[toScalar(dirID)];
    Fs::PathBuilder builder(relativePath);
    builder.convertToAbsolute(rootPath);
    builder.makeCanonical();

    return Fs::Path(builder);
}

//! @brief Gets the absolute path to an application-centric resource.
//! @param[in] dirID The identifier of the directory the path should be resolved
//! relative to.
//! @param[in] relativePath The relative path to the resource within the
//! known application directory structure.
//! @returns The resolved canonical path to the resource.
//! @throws ArgumentException Thrown if @p dirID is out of range.
//! @throws Fs::InvalidFilePathException Thrown if @p relativePath is not a
//! valid path, but not if it is blank.
Fs::Path AppPaths::getPath(AppDir dirID, const Fs::PathBuilder &relativePath) const
{
    if (dirID >= AppDir::Max)
        throw ArgumentException("Invalid application path identifier.", "dirID");

    // If the path is absolute, there is no point doing more.
    if (relativePath.hasRoot())
        return Fs::Path(relativePath);

    const Fs::PathBuilder &rootPath = _roots[toScalar(dirID)];

    Fs::PathBuilder resolvedPath(relativePath);
    resolvedPath.convertToAbsolute(rootPath);
    resolvedPath.makeCanonical();

    return Fs::Path(resolvedPath);
}

//! @brief Overrides the path to an application-centric directory used to
//! resolve paths to application resources.
//! @param[in] dirID The identifier of the directory path to be overridden.
//! @throws ArgumentException Thrown if @p dirID is out of range or @p path
//! is relative.
void AppPaths::setOverride(AppDir dirID, const Fs::Path &path)
{
    if (dirID >= AppDir::Max)
        throw ArgumentException("Invalid application path identifier.", "dirID");

    if (path.hasRoot() == false)
        throw ArgumentException("An application path cannot be relative.", "path");

    _roots[toScalar(dirID)] = path;
}

//! @brief Performs shared initialisation of application paths based on
//! application metadata.
//! @param[in] appInfo The application metadata used to derive application-centric
//! path element names.
//! @param[in] stripSpaces True to remove spaces from path element names, false
//! to leave them in.
void AppPaths::initialise(const AppMetadata &appInfo, bool stripSpaces)
{
    if (appInfo.AppName.empty())
        throw ArgumentException("Cannot derive application paths from an empty application name.",
                                "appInfo");

    Fs::PathSchemaID schema = Fs::getNativeSchema();

    String appNamePathElement;

    if (schema->tryMakeValidPathElement(appInfo.AppName, appNamePathElement,
                                        stripSpaces) == false)
    {
        std::string detail;
        detail.assign("Cannot derive a valid path element from the application name '");
        detail.append(appInfo.AppName);
        detail.append("'.");

        throw ArgumentException(detail.c_str(), "appInfo");
    }

    String companyNamePathElement;
    String productNamePathElement;

    schema->tryMakeValidPathElement(appInfo.CompanyName, companyNamePathElement,
                                    stripSpaces);

    schema->tryMakeValidPathElement(appInfo.ProductName, productNamePathElement,
                                    stripSpaces);

    Fs::PathBuilder &progs = _roots[toScalar(AppDir::Programs)];
    progs.assignProgramDirectory();
    progs.makeCanonical();

    Fs::PathBuilder &libs = _roots[toScalar(AppDir::Libraries)];
    libs = progs;

    Fs::PathBuilder &appRO = _roots[toScalar(AppDir::ReadOnlyData)];
    Fs::PathBuilder &globalRO = _roots[toScalar(AppDir::GlobalReadOnlyConfig)];
    Fs::PathBuilder &globalRW = _roots[toScalar(AppDir::GlobalWriteableConfig)];
    Fs::PathBuilder &userData = _roots[toScalar(AppDir::UserConfig)];

#ifdef _WIN32
    appRO = progs;
    globalRO = progs;
    globalRW.tryParse(getKnownDirectory(FOLDERID_ProgramData));
    appendAppElements(globalRW, companyNamePathElement, productNamePathElement, appNamePathElement);
    globalRW.makeCanonical();

    userData.tryParse(getKnownDirectory(FOLDERID_RoamingAppData));
    appendAppElements(userData, companyNamePathElement, productNamePathElement, appNamePathElement);
    userData.makeCanonical();
#else
    libs.popElement();
    libs.pushElement("lib");
    libs.makeCanonical();

    appRO = progs;
    appRO.popElement();
    appRO.pushElement("share");
    appendAppElements(appRO, companyNamePathElement, productNamePathElement, appNamePathElement);
    appRO.makeCanonical();

    globalRW.tryParse("/etc");
    appendAppElements(globalRW, companyNamePathElement, productNamePathElement, appNamePathElement);
    globalRW.makeCanonical();
    globalRO = globalRW;

    userData.assignHomeDirectory();
    appendAppElements(userData, companyNamePathElement, productNamePathElement,
                      appNamePathElement, /* makeHidden = */ true);
    userData.makeCanonical();
#endif
}

////////////////////////////////////////////////////////////////////////////////
// App Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a singleton instance of a class which administers the
//! structure of the application.
//! @throw OperationException If any other instances of an App-derived class
//! are currently instantiated.
//! @remarks
//! Runtime application initialisation should be implemented by overriding the
//! initialise() member function, but static initialisation, such as calls to
//! initialisePaths() can be made in the constructor so that metadata is
//! available for the lifetime of the app.
App::App()
{
    if (g_singletonApp == nullptr)
    {
        // Register the application object.
        g_singletonApp = this;
    }
    else
    {
        throw OperationException("Only one instance of an Ag::App-derived class "
                                 "can be instantiated at any one time.");
    }
}

//! @brief Disposes of resources owned by the object and de-registers this as
//! the singleton instance.
App::~App()
{
    if (g_singletonApp == this)
    {
        // De-register the application object.
        g_singletonApp = nullptr;
    }
}

//! @brief Gets the singleton instance of an App-derived object instantiated
//! within the process.
//! @returns A pointer to the current App instance, nullptr if no instances of
//! and App-derived class are currently instantiated.
App *App::get()
{
    return g_singletonApp;
}

//! @brief Obtains an output stream to write console output to.
//! @return The console output stream, possibly nullptr if one could not
//! be created.
FILE *App::getConsoleOutputStream()
{
    // Ensure STDOUT is open and attempt to re-enable it if it isn't.
    if (isStdoutEnabled() == false)
        enableStdout(false);

    return stdout;
}

//! @brief Gets the application-centric file paths, lazily initialising them
//! if necessary.
AppPaths &App::getPaths()
{
    if (_paths)
        return *_paths.get();

    // Lazily initialise the paths from (possibly derived) metadata.
    _paths = std::make_unique<AppPaths>(_metadata, true);

    return *_paths.get();
}

//! @brief Gets the application-centric file paths, lazily initialising them
//! if necessary.
const AppPaths &App::getPaths() const
{
    if (_paths)
        return *_paths.get();

    // Appologies for the const_cast<>() - we need to lazily initialise the
    // application metadata and paths, I didn't want to make the two fields
    // mutable, so this is the result.
    return const_cast<App *>(this)->getPaths();
}

//! @brief Gets the application metadata, either derived from the program binary
//! or explicitly initialised from metadata.
const AppMetadata &App::getMetadata() const
{
    return _metadata;
}

//! @brief Executes the application using the command line arguments it was
//! launched with.
//! @returns The global process result value to return from main().
//! @details This function is intended to run a traditional POSIX application
//! or a Win32 console application.
int App::exec()
{
#ifdef _WIN32
    CommandLineInfo cliInfo(createCommandLineArguments(), ::GetCommandLineW());
#else
    // Read /proc/self/cmdline and parse into tokens.
    std::vector<utf8_cptr_t> args;
    std::vector<char> buffer;

    getProgramArgs(buffer, args);
    CommandLineInfo cliInfo(createCommandLineArguments(),
                            static_cast<int>(args.size()),
                            args.data());
#endif

    return innerExec(cliInfo);
}

//! @brief Executes the application.
//! @param[in] argc The count of command line arguments.
//! @param[in] argv The array of command line argument tokens. The first argument
//! is expected to be the path to the binary used to launch the application.
//! @returns The global process result value to return from main().
//! @details This function is intended to run a traditional POSIX application
//! or a Win32 ANSI console application.
int App::exec(int argc, const char * const *argv)
{
    CommandLineInfo commandLineInfo(createCommandLineArguments(), argc, argv);

    return innerExec(commandLineInfo);
}

//! @brief Executes the application.
//! @param[in] argc The count of command line arguments.
//! @param[in] argv The array of wide character command line argument tokens.
//! The first argument is expected to be the path to the binary used to launch
//! the application.
//! @returns The global process result value to return from main().
//! @details This function is intended to run a Unicode-enabled Win32 console
//! application .
int App::exec(int argc, const wchar_t * const *argv)
{
    CommandLineInfo commandLineInfo(createCommandLineArguments(), argc, argv);

    return innerExec(commandLineInfo);
}

//! @brief Executes the application.
//! @param[in] commandLine The entire command line expressed as a null-terminated
//! array of wide characters. The path to the binary used to launch the
//! application is not expected to be included.
//! @returns The global process result value to return from main().
//! @details This function is intended to receive the command line string passed
//! to the Win32 GUI application entry point WinMain().
int App::exec(wchar_cptr_t commandLine)
{
    CommandLineInfo commandLineInfo(createCommandLineArguments(), commandLine);

    return innerExec(commandLineInfo);
}

//! @brief Explicitly initialises the application paths based on application metadata.
void App::initialisePaths(const AppMetadata &metadata)
{
    _metadata = metadata;

    _paths = std::make_unique<AppPaths>(_metadata);
}

//! @brief Can be called from anywhere in the program where an exception is
//! caught unexpectedly.
//! @param[in] error The exception which went unhandled.
void App::onUnhandledException(const std::exception &error)
{
    reportException(error);
}

//! @brief Overridden in derived classes in order to instantiate an
//! application-specific CommandLine-derived class to process command line
//! parameters.
//! @returns A unique pointer to a pre-configured CommandLine-derived object
//! which will be used to process command line options.
//! @details The this function will be called by exec() before initialise()
//! and the resultant instance disposed of after initialise() has returned.
//! The default implementation returns a ProgramArguments instance with an empty
//! schema which will ignore arguments and disallow any options.
CommandLineUPtr App::createCommandLineArguments() const
{
    Cli::SchemaBuilder builder;

    // Use whatever metadata has been defined thus far to stoke a basic
    // command line interpreter.
    builder.setAppInfo(_metadata);

    Cli::Schema emptySchema = builder.createSchema();

    return std::make_unique<Cli::ProgramArguments>(emptySchema);
}

//! @brief Overridden by derived classes in order to perform one-time
//! application setup tasks based on default behaviour or parameters passed
//! on the command line.
//! @param[in] args An instance of a CommandLine-derived object returned by
//! createCommandLineArguments().
//! @retval true The application has successfully initialised, it can now
//! operate by calling the run() member function followed by the shutdown()
//! member function.
//! @retval false Initialisation failed, the application will exit with a
//! non-zero process result.
//! @details The default implementation always returns true;
bool App::initialise(const Cli::ProgramArguments * /* args */)
{
    return true;
}

//! @brief Implemented in derived classes to perform the main function of the
//! application after a successful initialisation.
//! @param[in] args The arguments parsed from the command line.
//! @return The global process result to be returned from the process entry
//! point function i.e. main() or WinMain().
//! @details The default implementation executes run(void).
int App::run(const Cli::ProgramArguments */* args */)
{
    return run();
}

//! @brief Implemented in derived classes to perform the main function of the
//! application after a successful initialisation.
//! @return The global process result to be returned from the process entry
//! point function i.e. main() or WinMain().
//! @details The default implementation always returns 0 with no previous processing.
int App::run()
{
    return 0;
}

//! @brief Implemented in derived classes to perform clean-up tasks once the
//! run() member function has returned. Errors from this function will be ignored.
void App::shutdown()
{
    // Do nothing.
}

//! @brief Processes an exception caught at the outermost level of nesting.
//! @param[in] error The exception to report.
//! @note The default implementation forms an error message and calls the
//! reportError() member function.
void App::reportException(const std::exception &error)
{
    const Ag::Exception *agError = dynamic_cast<const Exception *>(&error);

    if ((agError != nullptr) && (agError->isEmpty() == false))
    {
        std::string buffer;

        appendPrintf(buffer, "%.*s caught: %.*s\n%.*s\n",
                     static_cast<int>(agError->getDomain().length()),
                     agError->getDomain().data(),
                     static_cast<int>(agError->getMessage().length()),
                     agError->getMessage().data(),
                     static_cast<int>(agError->getDetail().length()),
                     agError->getDetail().data());

        if (agError->getErrorCode() != 0)
        {
            appendPrintf(buffer, "Error code: 0x%.4jX\n", agError->getErrorCode());
        }

        if (agError->getStackTrace().isEmpty() == false)
        {
            buffer.append("\nStack Trace:\n");
            agError->getStackTrace().appendToString(buffer, true);
        }

        reportError(buffer.c_str());
    }
}

//! @brief Processes error message text.
//! @param[in] errorText The null-terminated UTF-8 encoded text defining the,
//! possibly multi-line, error output.
//! @note The default implementation writes to stderr and the Windows debugger
//! console if one is attached.
void App::reportError(utf8_cptr_t errorText)
{
#ifdef _WIN32
    if (::IsDebuggerPresent())
    {
        // Copy the text to the Win32 debug console.
        std::wstring wideBuffer;
        Utf::appendToWide(wideBuffer, errorText, strlen(errorText));

        ::OutputDebugStringW(wideBuffer.c_str());
    }
#endif

    // Write the text to the error stream.
    FILE *output = App::getConsoleOutputStream();

    if (output != nullptr)
        fputs(errorText, output);
}

//! @brief Common logic for the exec() member function.
//! @param[in] info Abstracted details of the command line arguments to be
//! processed.
//! @return The global process result.
int App::innerExec(CommandLineInfo &info)
{
    ErrorGuard guard;
    int processResult = 0;

    if (info.Manager)
    {
        // Attempt to process the command line arguments.
        if (guard.tryExecProcedure(guardedTryParse, info))
        {
            if (info.Success == false)
            {
                // The processing logic detected an error.
                processResult = 1;
                std::string buffer;

                appendPrintf(buffer, "Command line arguments were invalid: %s\n",
                             info.Error.getUtf8Bytes());

                reportError(buffer.c_str());
            }
        }
        else
        {
            // An exception was thrown while processing the command line.
            std::string buffer;
            appendPrintf(buffer, "Error processing the command line arguments: %.*s\n%.*s\n",
                         static_cast<int>(guard.getError().getMessage().length()),
                         guard.getError().getMessage().data(),
                         static_cast<int>(guard.getError().getDetail().length()),
                         guard.getError().getDetail().data());

            reportError(buffer.c_str());
            processResult = 1;
        }
    }

    if (processResult == 0)
    {
        // Attempt to perform application initialisation.
        bool isOK = false;
        if (guard.tryExecFunction<bool, App *, const Cli::ProgramArguments *>(
                guardedInitialise, isOK, this, info.Manager.get()))
        {
            if (isOK)
            {
                // Initialisation was successful, execute the run() member function.
                if (guard.tryExecFunction<int, App *, const Cli::ProgramArguments *>(
                        guardedRun, processResult, this, info.Manager.get()) == false)
                {
                    onUnhandledException(guard.getError());
                    processResult = 1;
                }

                // Ensure shutdown is properly performed.
                if (guard.tryExecProcedure(guardedShutdown, this) == false)
                {
                    // Signal failure, but otherwise ignore the error.
                    processResult = 1;
                }
            }
            else
            {
                // No failure message, but exit the process without shutdown.
                processResult = 1;
            }
        }
        else
        {
            // Application initialisation threw an exception.
            std::string buffer;

            appendPrintf(buffer, "An initialisation error occurred: %.*s\n%.*s\n",
                         static_cast<int>(guard.getError().getMessage().length()),
                         guard.getError().getMessage().data(),
                         static_cast<int>(guard.getError().getDetail().length()),
                         guard.getError().getDetail().data());
            reportError(buffer.c_str());
            processResult = 1;
        }
    }

    return processResult;
}

//! @brief Makes a call to the overridden version of the initialise() member
//! function in a guarded context.
//! @param[in] instance The application instance to call initialise() on.
//! @param[in] args The parsed command line arguments.
//! @returns The initialisation result.
bool App::guardedInitialise(App *instance, const Cli::ProgramArguments *args)
{
    return instance->initialise(args);
}

//! @brief Makes a call to the overridden version of the run() member function
//! in a guarded context.
//! @param[in] instance The application instance to call run() on.
//! @returns The global process result.
int App::guardedRun(App *instance, const Cli::ProgramArguments *args)
{
    return instance->run(args);
}

//! @brief Makes a call to the overridden version of the shutdown() member function
//! in a guarded context.
//! @param[in] instance The application instance to call shutdown() on.
void App::guardedShutdown(App *instance)
{
    instance->shutdown();
}

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

