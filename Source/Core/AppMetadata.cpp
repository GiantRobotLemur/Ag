//! @file Core/AppMetadata.cpp
//! @brief The definition of a structure holding fixed appliaction identity
//! information.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/AppMetadata.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// AppMetadata Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object pointing to fixed application metadata.
//! @param[in] version The version of the application.
//! @param[in] appName The symbolic name of the application, used to identify
//! the application to the system.
//! @param[in] displayName The name of the application to display to the user.
//! @param[in] companyName The optional name of the company that produced the
//! application.
//! @param[in] prodName The name of the product the appliaction is a part of.
//! @param[in] desc A display description of the application.
//! @param[in] author The optional author of the application.
//! @param[in] copyright The copyright statement pertaining to the application.
AppMetadata::AppMetadata(const Version &version, const std::string_view &appName,
                         const std::string_view &displayName, const std::string_view &desc,
                         const std::string_view &companyName, const std::string_view &prodName,
                         const std::string_view &author, const std::string_view &copyright) :
    AppVersion(version),
    CompanyName(companyName),
    ProductName(prodName),
    AppName(appName),
    DisplayName(displayName),
    Description(desc),
    Author(author),
    Copyright(copyright)
{
}

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

