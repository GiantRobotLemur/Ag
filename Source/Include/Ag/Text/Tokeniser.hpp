//! @file Ag/Text/Tokeniser.hpp
//! @brief The declaration of a collection of template classes which can form
//! the basis of a lexical analysis pipeline.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _AG_TEXT_TOKENISER_HPP__
#define _AG_TEXT_TOKENISER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <type_traits>
#include <vector>

#include "CharacterAnalyser.hpp"

namespace Ag {
namespace Text {

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief A template class describing a token recognised from a sequence of
//! characters.
//! @tparam TTokenClassType The scalar type used to identify the token class
template<typename TTokenClassType,
    typename std::enable_if_t<std::is_enum_v<TTokenClassType>, bool> = true>
class Token
{
public:
    // Public Types
    using TokenClass = typename TTokenClassType;
private:
    // Internal Fields
    SourceReference _location;
    String _value;
    TokenClass _id;
public:
    // Construction/Destruction
    Token() :
        _id()
    {
    }

    //! @brief Constructs an immutable anonymous token.
    //! @param[in] at The location in the source where the token was found.
    //! @param[in] id The identifier of the class of token recognised.
    Token(const SourceReference &at, TokenClass id) :
        _location(at),
        _id(id)
    {
    }

    //! @brief Constructs an immutable unique token.
    //! @param[in] at The location in the source where the token was found.
    //! @param[in] id The identifier of the class of token recognised.
    //! @param[in] value The value of the token recognised.
    Token(const SourceReference &at, TokenClass id, utf8_cptr_t value) :
        _location(at),
        _value(value),
        _id(id)
    {
    }

    //! @brief Constructs an immutable unique token.
    //! @param[in] at The location in the source where the token was found.
    //! @param[in] id The identifier of the class of token recognised.
    //! @param[in] value The value of the token recognised.
    Token(const SourceReference &at, TokenClass id, String &value) :
        _location(at),
        _value(value),
        _id(id)
    {
    }

    //! @brief Constructs an immutable unique token.
    //! @param[in] at The location in the source where the token was found.
    //! @param[in] id The identifier of the class of token recognised.
    //! @param[in] value The value of the token recognised as a buffer of
    //! accumulated characters to be copied.
    Token(const SourceReference &at, TokenClass id, const CodePointBuffer &value) :
        _location(at),
        _value(value.data(), value.size()),
        _id(id)
    {
    }

    ~Token() = default;

    // Accessors

    //! @brief Gets the classification of token recognised.
    TokenClass getClass() const { return _id; }

    //! @brief Gets the text of the recognised token if it was unique.
    string_cref_t getValue() const { return _value; }

    //! @brief Gets the location in source from where the token was recognised.
    const SourceReference &getLocation() const { return _location; }
};

//! @brief Converts a stream of characters to a stream of tokens.
//! @tparam TTokenClassType The scalar type used to identify the token class
//! @tparam TTokenType The structure representing a recognised token, preferably
//! derived from the Token<> template.
//! @remarks Implementations hold no state, they merely understand how to
//! convert characters into tokens in a specific way.
template<typename TTokenClassType, typename TTokenType = Token<TTokenClassType> >
class ITokeniser
{
public:
    // Public Types
    using TokenClass = typename TTokenClassType;
    using Token = typename TTokenType;

    // Construction/Destruction
protected:
    ITokeniser() = default;
public:
    virtual ~ITokeniser() = default;

    // Operations
    //! @brief Attempts to recognise a token from the characters of an input
    //! stream.
    //! @param[in] analyser The stream of input characters to create a token from.
    //! @param[in] scratchBuffer A buffer re-used between tokeniser to accumulate
    //! characters of interest in order to form token values. The buffer will be
    //! empty when the member function is called and the contents unpredictable
    //! after returning.
    //! @param[out] nextToken Receives the token created from the next characters
    //! provided by @p analyser.
    //! @retval true A token was successfully recognised and returned
    //! in @p nextToken.
    //! @retval false Either there were no characters left or no token could be
    //! recognised from the next characters.
    virtual bool tryRecogniseToken(CharacterAnalyser &analyser,
                                   CodePointBuffer &scratchBuffer,
                                   Token &nextToken) const = 0;
};

//! @brief Represents a stream of tokens as an input to a parser.
//! @tparam TTokenClassType The scalar type used to identify the token class
//! @tparam TTokenType The structure representing a recognised token, preferably
//! derived from the Token<> template.
template<typename TTokenClassType, typename TTokenType = Token<TTokenClassType> >
class TokenStream
{
public:
    // Public Types
    using TokenClass = typename TTokenClassType;
    using Token = typename TTokenType;
    using Tokeniser = ITokeniser<TokenClass, Token>;
    using TokeniserCPtr = const Tokeniser *;

private:
    // Internal Types
    //! @brief Manages the resources associated with an independent token stream.
    class TokenSource
    {
    private:
        // Internal Fields
        IStreamUPtr _inputStream;
        ICharacterSourceUPtr _characterStream;
        CharacterAnalyser _analyser;
        std::vector<TokeniserCPtr> _tokeniserStack;
    public:
        // Construction/Destruction

        //! @brief Constructs an object which can produce tokens from an input source.
        //! @param[in] tokenStream The object which recognises tokens from characters.
        //! @param[in] sourceIdentifier Text identifying the input stream, such
        //! as a file path or URI.
        //! @param[in] characterStream The optional character stream to be disposed
        //! of when this object is destroyed.
        //! @param[in] inputStream The optional binary input stream, to be disposed
        //! of when this object is destroyed.
        TokenSource(TokeniserCPtr tokenStream,
                    string_cref_t sourceIdentifier,
                    ICharacterSourceUPtr &&characterStream,
                    IStreamUPtr &&inputStream) :
            _inputStream(std::move(inputStream)),
            _characterStream(std::move(characterStream)),
            _analyser(_characterStream.get(), sourceIdentifier)
        {
            _tokeniserStack.reserve(4);
            _tokeniserStack.push_back(tokenStream);
        }

        TokenSource(TokenSource &&rhs) noexcept :
            _inputStream(std::move(rhs._inputStream)),
            _characterStream(std::move(rhs._characterStream)),
            _analyser(std::move(rhs._analyser)),
            _tokeniserStack(std::move(rhs._tokeniserStack))
        {
        }

        TokenSource operator=(TokenSource &&rhs) noexcept
        {
            _inputStream = std::move(rhs._inputStream);
            _characterStream = std::move(rhs._characterStream);
            _analyser = std::move(rhs._analyser);
            _tokeniserStack = std::move(rhs._tokeniserStack);
        }

        TokenSource() = delete;
        TokenSource(const TokenSource &) = delete;
        TokenSource &operator=(const TokenSource &) = delete;

        ~TokenSource() = default;

        // Operations
        //! @brief Gets the next available token from the embedded
        //! character stream.
        //! @param[in] scratchBuffer A buffer re-used between tokeniser to
        //! accumulate characters of interest in order to form token values.
        //! @param[out] next Receives the next available token created by
        //! recognising a sequence of characters from the input stream.
        //! @retval true A new token was recognised and returned in @p next.
        //! @retval false No new token was recognised.
        bool tryGetNextToken(Token &next, CodePointBuffer &scratchBuffer)
        {
            if (_tokeniserStack.empty())
                return false;

            if (_tokeniserStack.back()->tryRecogniseToken(_analyser,
                                                          scratchBuffer,
                                                          next))
            {
                // If we have a whole token, we won't need to re-wind.
                _analyser.commit();

                return true;
            }

            return false;
        }

        //! @brief Pushes a new tokeniser implementation to recognise subsequent
        //! characters from the input stream.
        //! @param[in] tokeniser The new tokeniser implementation.
        //! @return The value to pass to restoreTokeniser() to restore the
        //! previous state of the token source.
        size_t pushTokeniser(TokeniserCPtr tokeniser)
        {
            size_t oldSize = _tokeniserStack.size();

            _tokeniserStack.push_back(tokeniser);

            return oldSize;
        }

        //! @brief Restores the token source to some previous state.
        //! @param[in] oldState A state value returned by pushTokeniser().
        void restoreTokeniser(size_t oldState)
        {
            if (oldState == 0)
                throw ArgumentException("A value of 0 would leave no tokeniser left.", "oldState");

            if (oldState < _tokeniserStack.size())
            {
                _tokeniserStack.erase(_tokeniserStack.begin() + oldState,
                                      _tokeniserStack.end());
            }
        }
    };

    // Internal Fields
    CodePointBuffer _scratchBuffer;
    std::vector<TokenSource> _sourceStack;
    std::vector<Token> _tokenCache;
    size_t _committed;
    size_t _read;

    // Internal Functions

    //! @brief Gets the next token from the current input stream
    //! @param[out] next Receives the next available token created by
    //! recognising a sequence of characters from the input stream.
    //! @retval true A new token was recognised and returned in @p next.
    //! @retval false No new token was recognised.
    bool tryGetNextTokenInternal(Token &next)
    {
        if (_sourceStack.empty())
            return false;

        _scratchBuffer.clear();

        return _sourceStack.back().tryGetNextToken(next, _scratchBuffer);
    }
public:
    // Construction/Destruction
    TokenStream() = delete;
    ~TokenStream() = default;
    TokenStream(const TokenStream &rhs) = delete;
    TokenStream &operator=(const TokenStream &) = delete;

    //! @brief Constructs an object to provide token input to a parser.
    //! @param[in] initialTokeniser The object which initially groups characters
    //! into valid tokens.
    //! @param[in] sourceIdentifier The identifier of the initial input stream,
    //! such as a file path or URL.
    //! @param[in] characterStream An r-value reference to the character input
    //! stream, for the new object to take ownership of.
    TokenStream(TokeniserCPtr initialTokeniser,
                string_cref_t sourceIdentifier,
                ICharacterSourceUPtr &&characterStream) :
        _committed(0),
        _read(0)
    {
        _sourceStack.reserve(8);
        _tokenCache.reserve(16);
        _scratchBuffer.reserve(32);

        IStreamUPtr noStream;

        // Stoke with the first stream.
        _sourceStack.emplace_back(initialTokeniser, sourceIdentifier,
                                  std::move(characterStream),
                                  std::move(noStream));
    }

    TokenStream(TokenStream &&rhs) noexcept :
        _scratchBuffer(std::move(rhs._scratchBuffer)),
        _sourceStack(std::move(rhs._sourceStack)),
        _tokenCache(std::move(rhs._tokenCache)),
        _committed(rhs._committed),
        _read(rhs._read)
    {
        rhs._committed = 0;
        rhs._read = 0;
    }

    TokenStream &operator=(TokenStream &&rhs) noexcept
    {
        _scratchBuffer = std::move(rhs._scratchBuffer);
        _sourceStack = std::move(rhs._sourceStack);
        _tokenCache = std::move(rhs._tokenCache);
        _committed = rhs._committed,
        _read = rhs._read;

        rhs._committed = 0;
        rhs._read = 0;
    }

    //! @brief Constructs an object to provide token input to a parser.
    //! @param[in] initialTokeniser The object which initially groups characters
    //! into valid tokens.
    //! @param[in] sourceIdentifier The identifier of the initial input stream,
    //! such as a file path or URL.
    //! @param[in] characterStream An r-value reference to the character input
    //! stream, for the new object to take ownership of.
    //! @param[in] inputStream An r-value reference to the stream which
    //! underlies the @p characterStream for the new object to take ownership of.
    TokenStream(TokeniserCPtr initialTokeniser,
                string_cref_t sourceIdentifier,
                ICharacterSourceUPtr &&characterStream,
                IStreamUPtr &&inputStream) :
        _committed(0),
        _read(0)
    {
        _sourceStack.reserve(8);
        _tokenCache.reserve(16);
        _scratchBuffer.reserve(32);

        // Stoke with the first stream.
        _sourceStack.emplace_back(initialTokeniser, sourceIdentifier,
                                  std::move(characterStream),
                                  std::move(inputStream));
    }

    // Accessors

    // Operations

    //! @brief Commits all previously read tokens as the client not longer has
    //! a need to rewind back to them.
    void commit()
    {
        _committed = _read;

        if (_committed == _tokenCache.size())
        {
            _committed = _read = 0;
            _tokenCache.clear();
        }
    }

    //! @brief Rewinds over one or more read but uncommitted tokens.
    //! @param[in] tokenCount The count of tokens to "unget".
    void rewind(size_t tokenCount)
    {
        size_t maxRewind = _read - _committed;

        if (tokenCount > maxRewind)
            throw OperationException("Not enough uncommitted tokens to rewind over.");

        _read -= tokenCount;
    }

    //! @brief Gets a next new token from the current input stream
    //! @param[out] next Receives the next available token created by
    //! recognising a sequence of characters from the input stream.
    //! @retval true A new token was recognised and returned in @p next.
    //! @retval false No new token was recognised.
    bool tryGetNextToken(Token &next)
    {
        if (_read < _tokenCache.size())
        {
            // Return a cached token if there is one.
            next = _tokenCache.at(_read++);

            return true;
        }
        else if (tryGetNextTokenInternal(next))
        {
            // Keep a copy of the token so it can be "ungot" later.
            _tokenCache.push_back(next);
            _read = _tokenCache.size();

            return true;
        }
        else
        {
            return false;
        }
    }

    //! @brief Starts reading tokens from a new input stream.
    //! @param[in] tokenStream The initial object to recognise tokens from a
    //! stream of characters.
    //! @param[in] identifier Text identifying the input stream, such as a
    //! file path or URI.
    //! @param[in] characterStream An object which provides a stream of
    //! characters to be disposed of when the stream is popped.
    //! @param[in] inputStream An optional binary input stream which feeds
    //! the character stream, to be disposed of when the stream is popped.
    //! @return The value to pass to restoreTokenStream() to remove the
    //! new stream and all streams pushed after it.
    size_t pushTokenStream(TokeniserCPtr tokenStream,
                           string_cref_t identifier,
                           ICharacterSourceUPtr &&characterStream,
                           IStreamUPtr &&inputStream)
    {
        size_t prevSize = _sourceStack.size();

        _sourceStack->emplace_back(tokenStream, sourceIdentifier,
                                   std::move(characterStream),
                                   std::move(inputStream));

        return prevSize;
    }

    //! @brief Starts reading tokens from a new input stream.
    //! @param[in] tokenStream The initial object to recognise tokens from a
    //! stream of characters.
    //! @param[in] identifier Text identifying the input stream, such as a
    //! file path or URI.
    //! @param[in] characterStream An object which provides a stream of
    //! characters to be disposed of when the stream is popped.
    //! @param[in] inputStream An optional binary input stream which feeds
    //! the character stream, to be disposed of when the stream is popped.
    //! @return The value to pass to restoreTokenStream() to remove the
    //! new stream and all streams pushed after it.
    size_t pushTokenStream(TokeniserCPtr tokenStream,
                           string_cref_t identifier,
                           ICharacterSourceUPtr &&characterStream)
    {
        size_t prevSize = _sourceStack.size();
        IStreamUPtr noStream;

        _sourceStack.emplace_back(tokenStream, identifier,
                                  std::move(characterStream),
                                  std::move(noStream));

        return prevSize;
    }

    //! @brief Pops open token streams to restore the state to a value
    //! previously returned by pushTokenStream().
    //! @param[in] oldPos The value representing the state to restore.
    void restoreTokenStream(size_t oldPos)
    {
        while (oldPos < _sourceStack.size())
            _sourceStack.pop_back();
    }

    //! @brief Pops the last token stream from the top of the stack of streams
    //! being processed.
    void popTokenStream()
    {
        if (!_sourceStack.empty())
            _sourceStack.pop_back();
    }

    //! @brief Pushes a new tokeniser implementation to recognise subsequent
    //! characters from the current input stream.
    //! @param[in] tokeniser The new tokeniser implementation.
    //! @return The value to pass to restoreTokeniser() to restore the
    //! previous state of the token source.
    size_t pushTokeniser(TokeniserCPtr tokeniser)
    {
        if (_sourceStack.empty())
            return 0;

        return _sourceStack.back().pushTokeniser(tokeniser);
    }

    //! @brief Restores the current token source to some previous state.
    //! @param[in] oldState A state value returned by pushTokeniser().
    void restoreTokeniser(size_t oldState)
    {
        if (oldState == 0)
            throw ArgumentException("A value of 0 would leave no tokeniser left.", "oldState");

        if (_sourceStack.empty() == false)
        {
            _sourceStack.back().restoreTokeniser(oldState);
        }
    }
};

//! @brief A structure which defined token pipeline types based on
//! template parameters.
//! @tparam TTokenClassType The scalar type used to identify the token class
//! @tparam TTokenType The structure representing a recognised token, preferably
//! derived from the Token<> template.
template<typename TTokenClassType, typename TTokenType = Token<TTokenClassType> >
struct TokenPipelineTraits
{
    TokenPipelineTraits() = delete;
    ~TokenPipelineTraits() = delete;

    using TokenClass = TTokenClassType;
    using Token = TTokenType;
    using ITokeniser = ITokeniser<TokenPipelineTraits::TokenClass, TokenPipelineTraits::Token>;
    using ITokeniserCPtr = const TokenPipelineTraits::ITokeniser *;
    using TokenStream = TokenStream<TokenPipelineTraits::TokenClass, TokenPipelineTraits::Token>;
};

}} // namespace Ag::Text

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
