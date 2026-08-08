//! @file Ag/Core/App.hpp
//! @brief The declaration of an object which represents the root of an
//! application object hierarchy.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_CORE_APP_HPP_
#define HEADER_AG_CORE_APP_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
// Needed in order to use wWinMain().
#ifdef _WIN32
////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
// Define macros to minimise the definitions introduced by including windows.h.
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#ifndef UNICODE
#define UNICODE
#endif

#ifndef NOMINMAX
#define NOMINMAX    // Macros min(a,b) and max(a,b)
#endif

#include <Windows.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <thread>
#include <string_view>

#include "Configuration.hpp"
#include "AppMetadata.hpp"
#include "FsPath.hpp"
#include "Utils.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#ifdef _GUI // Defined by CMake script

#ifdef _MSC_VER

#define IMPLEMENT_MAIN(AppType) int WINAPI wWinMain(_In_ HINSTANCE, \
_In_opt_ HINSTANCE, _In_ LPWSTR cmdLine, _In_ int) \
{ AppType theApp; return theApp.exec(cmdLine); }

#else ifndef _MSC_VER

#define IMPLEMENT_MAIN(AppType) int WINAPI wWinMain(HINSTANCE, HINSTANCE, \
LPWSTR cmdLine, int) { AppType theApp; return theApp.exec(cmdLine); }

#endif // ifdef _MSC_VER

#else // !defined _GUI
#define IMPLEMENT_MAIN(AppType) int wmain(int argc, wchar_t *argv[], wchar_t *[]) \
{ AppType theApp; return theApp.exec(argc, argv); }
#endif
#else // !defined _WIN32
#define IMPLEMENT_MAIN(AppType) int main(int argc, char *argv[]) \
{ AppType theApp; return theApp.exec(argc, argv); }
#endif

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Expresses the identities of application-centric file system directories.
enum class AppDir : uint8_t
{
    //! @brief Identifies the directory containing the application binary.
    //! @remarks
    //! Under Windows this might be C:\\Program Files\\<app name>. Under Linux
    //! this could be /usr/bin.
    Programs,

    //! @brief Identifies the directory containing the shared libraries related
    //! to the application.
    //! @remarks
    //! Under Windows this might be the same as the Programs folder, i.e.
    //! C:\\Program Files\\<app name>. Under Linux, it could be /usr/lib.
    Libraries,

    //! @brief Identifies the directory containing application-specific read-only data.
    //! @remarks
    //! Under Windows this might be the same as the Programs folder, i.e.
    //! C:\\Program Files\\<app name>. Under Linux, it could be /usr/share/<app name>.
    ReadOnlyData,

    //! @brief Identifies the directory containing architecture-independent global
    //! data shared across all users, which aren't settable without elevated priviledges.
    //! @remarks
    //! Under Windows this might be the same as the Programs folder, i.e.
    //! C:\\Program Files\\<app name>. Under Linux, it could be /etc/<app name>.
    GlobalReadOnlyConfig,

    //! @brief Identifies the directory containing architecture-independent global
    //! data shared across all users that can be updated by any user.
    //! @remarks
    //! Under Windows this might be C:\\ProgramData\\<app name>. Under Linux,
    //! it could be /etc/<app name>.
    GlobalWriteableConfig,

    //! @brief Identifies the directory containing writeable architecture independent
    //! user-specific data.
    //! @remarks
    //! Under Windows this might be %USERPROFILE%\\AppData\\Roaming\<app name>.
    //! Under Linux, this is likely to be $HOME/.<app name>
    UserConfig,

    //! @brief A value only used for bounds checking.
    Max,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
namespace Cli
{
class ProgramArguments;
}
struct CommandLineInfo;
class Exception;
typedef std::unique_ptr<Cli::ProgramArguments> CommandLineUPtr;

//! @brierf An object which manages application-specific file paths.
//! @remarks
//! While the object derives the directory paths based on the program file
//! location and application metadata, the object does not create them. It is
//! up to the application or the installer (where priviledge eleveration is
//! required) to create the directories in question.
//!
//! The ability have been created to override the root directories so that
//! different locations can be used by debug builds during development.
class AppPaths
{
public:
    // Construction/Destruction
    AppPaths();
    AppPaths(const AppMetadata &appInfo, bool stripSpaces = true);
    ~AppPaths() = default;

    // Accessors
    const Fs::PathBuilder &getPath(AppDir dirID) const;
    Fs::Path getPath(AppDir dirID, string_cref_t relativePath) const;
    Fs::Path getPath(AppDir dirID, const Fs::Path &relativePath) const;
    Fs::Path getPath(AppDir dirID, const Fs::PathBuilder &relativePath) const;

    // Operations
    void setOverride(AppDir dirID, const Fs::Path &path);
private:
    // Internal Functions
    void initialise(const AppMetadata &appInfo, bool stripSpaces);

    // Internal Fields
    Fs::PathBuilder _roots[toScalar(AppDir::Max)];
};

//! @brief An object which represents the root of an application object hierarchy.
class App
{
public:
    // Construction/Destruction
    App();
    virtual ~App();

    // Accessors
    static App *get();
    static FILE *getConsoleOutputStream();
    AppPaths &getPaths();
    const AppPaths &getPaths() const;
    const AppMetadata &getMetadata() const;

    // Operations
    int exec();
    int exec(int argc, const char * const *argv);
    int exec(int argc, const wchar_t * const *argv);
    int exec(wchar_cptr_t commandLine);
    void initialisePaths(const AppMetadata &metadata);

    // Overrides
    virtual void onUnhandledException(const std::exception &error);
protected:
    virtual CommandLineUPtr createCommandLineArguments() const;
    virtual bool initialise(const Cli::ProgramArguments *args);
    virtual int run(const Cli::ProgramArguments *args);
    virtual int run();
    virtual void shutdown();
    virtual void reportException(const std::exception &error);
    virtual void reportError(utf8_cptr_t errorText);

private:
    // Internal Types
    using AppPathsUPtr = std::unique_ptr<AppPaths>;

    // Internal Functions
    int innerExec(CommandLineInfo &info);
    static bool guardedInitialise(App *instance, const Cli::ProgramArguments *args);
    static int guardedRun(App *instance, const Cli::ProgramArguments *args);
    static void guardedShutdown(App *instance);

    // Internal Fields
    AppPathsUPtr _paths;
    AppMetadata _metadata;
};

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
