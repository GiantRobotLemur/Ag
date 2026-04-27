//! @file Gfx2D/GraphicArtefact.cpp
//! @brief The definition of a base class for any graphic resource or description
//! which can be updated as part of animation.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/GraphicArtefact.hpp"

namespace Ag {
namespace Gfx2D {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An exception thrown when an attempt is made to alter the graphic
//! state of a GraphicArtefact-derived object which is in a frozen state.
class ArtefactFrozenException : public Ag::Exception
{
public:
    ArtefactFrozenException(const std::string_view &artefactType,
                            const std::string_view &operation)
    {
        std::string message;
        message.assign("An attempt was made to change a ");
        message.append(artefactType);
        message.append(" artefact which was in a frozen state.");

        std::string detail;

        detail.assign("The program attempted to ");
        detail.append(operation);
        detail.append(" on a ");
        detail.append(artefactType);
        detail.append(" artefact.");

        initialise("ArtefactFrozenException", message, detail, 0);
    }
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GraphicArtefact Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an artefact, possibly already frozen.
//! @param[in] isFrozen The initial frozen state of the artefact.
GraphicArtefact::GraphicArtefact(bool isFrozen /*= false*/) :
    _isFrozen(isFrozen)
{
}

//! @brief Determines if the object is in a frozen state and therefore cannot
//! be changed.
//! @retval true The object is frozen, any further changes to its graphic state
//! will raise an exception.
//! @retval false The object can be changed freely.
bool GraphicArtefact::isFrozen() const noexcept
{
    return _isFrozen;
}

//! @brief Gets a version of the artefact which is frozen, possibly
//! returning the original if it is already frozen.
std::shared_ptr<GraphicArtefact> GraphicArtefact::createFrozenClone() const
{
    if (_isFrozen)
    {
        // Please forgive this transgression - the graphic state isn't
        // being changed by creating another reference, so, no harm?
        return const_cast<GraphicArtefact *>(this)->shared_from_this();
    }

    if (!_frozenCopy)
    {
        _frozenCopy = clone();
        _frozenCopy->freeze();
    }

    return _frozenCopy;
}

//! @brief Marks the object as frozen, preventing any further changes from being
//! made without raising an exception.
//! @remarks If the object is already frozen, this member function has no effect.
void GraphicArtefact::freeze()
{
    _isFrozen = true;

    // Release the frozen copy so that we don't needlessly end up with a long
    // chain of frozen artefacts.
    _frozenCopy = nullptr;
}

//! @brief Verifies that changes can be made to an artefact before it is edited.
//! @param[in] artefactType The name of the artefact type to appear in the
//! exception description.
//! @param[in] operation A description of the operation to appear in the
//! exception description.
//! @throws ArtefactFrozenException If the object is already in a frozen state.
//! @remarks This functions throws an exception if the object is frozen, or
//! clears the frozen copy of the object if it is about to be changed so that
//! next time a frozen copy is requested, a new one will be created.
void GraphicArtefact::verifyAccess(const std::string_view &artefactType,
                                   const std::string_view &operation)
{
    if (_isFrozen)
    {
        throw ArtefactFrozenException(artefactType, operation);
    }

    _frozenCopy = nullptr;
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

