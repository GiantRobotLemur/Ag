//! @file Ag/Core/AppMetadata.hpp
//! @brief The declaration of a structure holding fixed appliaction identity
//! information.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_CORE_APP_METADATA_HPP_
#define HEADER_AG_CORE_APP_METADATA_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <string_view>

#include "Version.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A structure which can be used to capture hard-coded application metadata.
struct AppMetadata
{
    Version AppVersion;             //!< The version of the application.
    std::string_view CompanyName;   //!< The optional name of the company that produced the application.
    std::string_view ProductName;   //!< The optioanl name of the product the appliaction is a part of.
    std::string_view AppName;       //!< The symbolic name of the application, identify to the system.
    std::string_view DisplayName;   //!< The name of the application to display to the user.
    std::string_view Description;   //!< A display description of the application.
    std::string_view Author;        //!< The optional author of the application.
    std::string_view Copyright;     //!< The copyright statement pertaining to the application.

    AppMetadata() = default;
    AppMetadata(const Version &version, const std::string_view &appName,
                const std::string_view &displayName, const std::string_view &desc,
                const std::string_view &companyName, const std::string_view &prodName,
                const std::string_view &author, const std::string_view &copyright);
};

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
