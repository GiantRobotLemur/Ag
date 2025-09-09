//! @file SymbolPackager/Utils.hpp
//! @brief The declaration of stand-alone helper functions for use by the
//! symbol packager tool.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SYMBOL_PACKAGER_HPP__
#define __AG_SYMBOL_PACKAGER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdarg>
#include <string>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A structure referencing a bounded character string.
struct BoundedString
{
    const char *Text;
    size_t Length;
    size_t HashCode;

    BoundedString(const char *text);
    BoundedString(const char *text, size_t length);
    BoundedString(const std::string &text);

    bool operator==(const BoundedString &rhs) const;
    bool operator!=(const BoundedString &rhs) const;
    bool isEqualIgnoreCase(const BoundedString &rhs) const;
    bool startsWith(const BoundedString &rhs) const;
};

//! @brief An object which can automatically close an std::FILE as part of a
//! std::unique_ptr<>.
struct StdFileCloser
{
    //! @brief Closes a file if the pointer is valid.
    //! @param[in] file The file to close.
    void operator()(FILE *file) const
    {
        if (file != nullptr)
        {
            fclose(file);
        }
    }
};

//! @brief A unique pointer to an stdio-FILE object which calls fclose() on the
//! pointer at destruction.
typedef std::unique_ptr<FILE, StdFileCloser> StdFilePtr;

namespace Ag {

//! @brief A simple interface for reading and writing binary data which is
//! compatible enough with the Ag::IStream interface that both are compatible
//! with the structures defined in Ag/Private/SymbolEnding.hpp.
class IStream
{
public:
    // Construction/Destruction
    virtual ~IStream() = default;

    // Operations
 
    //! @brief Reads bytes from the stream.
    //! @param[in] targetBuffer The buffer to receive the bytes read.
    //! @param[in] requiredByteCount The maximum number of bytes to read.
    //! @return The actual number of bytes read.
    //! @throws Ag::Exception If an error occurs during the read.
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) = 0;

    //! @brief Writes bytes to the stream.
    //! @param[in] sourceBuffer The bytes to write.
    //! @param[in] sourceByteCount The maximum count of bytes to write.
    //! @return The actual number of bytes written.
    //! @throws Ag::Exception If an error occurs during the write.
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) = 0;
};

} // namespace Ag

//! @brief An implementation of IStream backed by an stdio FILE object.
class FileStream : public Ag::IStream
{
public:
    // Construction/Destruction
    FileStream();
    virtual ~FileStream();

    // Accessors
    bool isOpen() const;

    // Operations
    bool tryOpen(const char *fileName, const char *mode);
    void close();

    // Overrides
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;

private:
    // Internal Fields
    FILE *_file;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
bool tryOpenFile(const char *fileName, const char *mode, StdFilePtr &file);
bool tryRead(FILE *fp, void *buffer, size_t byteCount);
bool tryRead(StdFilePtr &fp, void *buffer, size_t byteCount);
bool tryParseHex(const char *str, uint64_t &value);
void appendFormat(std::string &target, const char *format, ...);
bool isEqualIgnoreCase(const std::string &lhs, const char *rhs);
std::string makeFullPath(const std::string &basePath, const std::string &path);

////////////////////////////////////////////////////////////////////////////////
// Template Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Overwrites a POD structure with zeros.
//! @tparam T The data type of the object.
//! @param[in] object %A reference to the object to fill.
template<typename T> void zeroFill(T &object)
{
    std::memset(static_cast<void *>(&object), 0, sizeof(T));
}

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
