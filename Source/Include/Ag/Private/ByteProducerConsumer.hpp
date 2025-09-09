//! @file Ag/Private/ByteProducerConsumer.hpp
//! @brief The declaration of an object which simplifies the task of buffering
//! bytes.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_BYTE_PRODUCER_CONSUMER_HPP__
#define __AG_BYTE_PRODUCER_CONSUMER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <cstring>

#include <algorithm>
#include <vector>

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// ByteProducerConsumer Definition
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which manages the buffering of bytes in a simple
//! producer/consumer relationship.
class ByteProducerConsumer
{
private:
    // Internal Fields
    std::vector<uint8_t> _buffer;
    size_t _bytesProduced;
    size_t _bytesConsumed;
public:
    // Construction/Destruction
    //! @brief Constructs a new object with a fixed sized buffer.
    ByteProducerConsumer(size_t bufferSize) :
        _bytesProduced(0),
        _bytesConsumed(0)
    {
        _buffer.resize(bufferSize);
    }

    ~ByteProducerConsumer() = default;

    // Accessors

    //! @brief Determines if there are no bytes in the buffer.
    //! @retval true The buffer is empty.
    //! @retval false The buffer contains at least one byte.
    constexpr bool isEmpty() const noexcept { return _bytesProduced == _bytesConsumed; }

    //! @brief Gets the maximum count of bytes which can be buffered.
    size_t getSize() const noexcept { return _buffer.size(); }

    //! @brief Gets the total count of free bytes in the buffer, although
    //! not necessarily in a contiguous block.
    size_t getTotalBufferFree() const noexcept
    {
        return _bytesConsumed + (_buffer.size() - _bytesProduced);
    }

    //! @brief Determines if the object can consume more bytes.
    //! @retval true There is room for at least one more byte in the buffer.
    //! @retval false The buffer is full.
    bool canConsume() const noexcept
    {
        return getTotalBufferFree() > 0;
    }

    //! @brief Indicates whether there are any buffered bytes can be produced.
    //! @retval true There it at least one byte left in the buffer.
    //! @retval false The buffer is empty.
    constexpr bool canProduce() const noexcept
    {
        return _bytesConsumed < _bytesProduced;
    }

    //! @brief Gets the count of unconsumed bytes left in the buffer.
    constexpr size_t getBufferedByteCount() const noexcept
    {
        return _bytesProduced - _bytesConsumed;
    }

    //! @brief Gets a pointer to all bytes which can be consumed.
    //! @param[out] bytesAvailable Receives the count of consumable bytes.
    //! @return A pointer to the first consumable byte.
    const uint8_t *getConsumable(size_t &bytesAvailable) const
    {
        bytesAvailable = _bytesProduced - _bytesConsumed;

        return _buffer.data() + _bytesConsumed;
    }

    // Operations

    //! @brief Resets the size of the buffer - all previous contents are lost.
    void reset(size_t newBufferSize)
    {
        _bytesConsumed = _bytesProduced = 0;

        _buffer.resize(newBufferSize, 0);
    }

    //! @brief Removes any previously consumed bytes to free up space
    //! to receive newly produced bytes.
    //! @retval true The buffer was reconfigured to maximize space for new data.
    //! @retval false No change was made to the object.
    bool removeConsumed()
    {
        bool bufferChanged = false;

        if (_bytesConsumed > 0)
        {
            if (_bytesConsumed == _bytesProduced)
            {
                // Reset the buffer state.
                _bytesConsumed = _bytesProduced = 0;
            }
            else
            {
                memmove(_buffer.data(), _buffer.data() + _bytesConsumed,
                        _bytesProduced - _bytesConsumed);
                _bytesProduced -= _bytesConsumed;
                _bytesConsumed = 0;
            }

            bufferChanged = true;
        }

        return bufferChanged;
    }

    //! @brief Makes the free portion of the buffer available to be filled.
    //! @param[out] maxConsumable Receives the maximum number of bytes which
    //! can be written to the returned buffer.
    //! @return A pointer to the portion of the buffer which can receive
    //! newly produced bytes.
    void *lockProduceable(size_t &maxConsumable)
    {
        if (_bytesConsumed > (_buffer.size() / 2))
        {
            // Free up maximum space for produced bytes.
            removeConsumed();
        }

        maxConsumable = _buffer.size() - _bytesProduced;

        return _buffer.data() + _bytesProduced;
    }

    //! @brief Adds to the count of consumed bytes after a previous call to
    //! lockProduceable().
    //! @param[in] extraBytesConsumed The actual count of bytes written to the
    //! buffer returned by lockProduceable().
    void unlockProduceable(size_t extraBytesConsumed)
    {
        _bytesProduced = std::min(_bytesProduced + extraBytesConsumed,
                                  _buffer.size());
    }

    //! @brief Marks a run of bytes as consumed which were extracted via the
    //! getConsumable() member function.
    //! @param[in] byteCount The count of bytes to consume.
    //! @return The actual number of bytes consumed.
    size_t consume(size_t byteCount)
    {
        size_t bytesConsumed = std::min(_bytesProduced - _bytesConsumed, byteCount);
        _bytesConsumed += bytesConsumed;

        if (_bytesConsumed == _bytesProduced)
            _bytesConsumed = _bytesProduced = 0;

        return bytesConsumed;
    }

    //! @brief Consumes newly produced data.
    //! @param[in] data An array of bytes to buffer.
    //! @param[in] byteCount The count of bytes in @p data.
    //! @return The actual count of bytes from @p data consumed.
    size_t consume(const void *data, size_t byteCount)
    {
        if (_bytesConsumed > (_buffer.size() / 2))
        {
            removeConsumed();
        }

        size_t bufferFree = _buffer.size() - _bytesProduced;
        size_t bytesProduced = std::min(bufferFree, byteCount);

        memcpy(_buffer.data() + _bytesProduced, data, bytesProduced);
        _bytesProduced += bytesProduced;

        return bytesProduced;
    }

    //! @brief Produces buffered data, removing it from the buffer.
    //! @param[in] data An array to receive the consumed data.
    //! @param[in] byteCount The maximum count of bytes which @p data
    //! can receive.
    //! @return The actual count of bytes read from @p data.
    size_t produce(void *data, size_t byteCount)
    {
        size_t bytesAvailable = _bytesProduced - _bytesConsumed;
        size_t bytesToConsume = std::min(bytesAvailable, byteCount);

        memcpy(data, _buffer.data() + _bytesConsumed, bytesToConsume);

        _bytesConsumed += bytesToConsume;

        if (_bytesConsumed == _bytesProduced)
        {
            // All bytes in the buffer have been consumed, reset the pointers.
            _bytesConsumed = _bytesProduced = 0;
        }

        return bytesToConsume;
    }
};

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
