//! @file Ag/Gfx2D/GraphicArtefact.hpp
//! @brief The declaration of a base class for any graphic resource or description
//! which can be updated as part of animation.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_GRAPHIC_ARTEFACT_HPP__
#define __GFX_2D_GRAPHIC_ARTEFACT_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A base class for any graphic resource or description which can be
//! updated as part of animation.
class GraphicArtefact : public std::enable_shared_from_this<GraphicArtefact>
{
protected:
    // Construction/Destruction
    GraphicArtefact(bool isFrozen = false);
public:
    virtual ~GraphicArtefact() = default;

    // Accessors
    bool isFrozen() const noexcept;

    // Operations
    std::shared_ptr<GraphicArtefact> createFrozenClone() const;

    // Overrides
    virtual void freeze();

    //! @brief Creates a clone of the artefact which is not frozen.
    virtual std::shared_ptr<GraphicArtefact> clone() const = 0;
protected:
    // Internal Types

    // Internal Functions
    void verifyAccess(const std::string_view &artefactType,
                      const std::string_view &operation);

private:
    // Internal Fields
    mutable std::shared_ptr<GraphicArtefact> _frozenCopy;
    bool _isFrozen;
};

using GraphicArtefactSPtr = std::shared_ptr<GraphicArtefact>;

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
