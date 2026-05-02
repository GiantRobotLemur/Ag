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

    //! @brief Updates a pointer to a GraphicArtefact-derived instance frozen,
    //! re-using an inner frozen clone if possible.
    //! @tparam T The GraphicArtefact-derived data type of the artefact to clone.
    //! @param[in,out] artefact The reference to the artefact to freeze,
    //! possibly null, updated with a frozen clone if necessary. A null
    //! reference leads to a non-op.
    template<typename T>
    static void makeFrozen(std::shared_ptr<T> &artefact)
    {
        if (artefact && !artefact->isFrozen())
            artefact = std::dynamic_pointer_cast<T>(artefact->createFrozenClone());
    }

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
