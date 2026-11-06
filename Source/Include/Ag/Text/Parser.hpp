//! @file Ag/Text/Parser.hpp
//! @brief The declaration of a template for a parser which operates on top of
//! the infrastructure provided by the TokenStream template class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _AG_TEXT_PARSER_HPP__
#define _AG_TEXT_PARSER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Tokeniser.hpp"
#include "ParseMessage.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Text {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
template<typename TTokenClassType, typename TTokenType = Token<TTokenClassType> >
class ParseContext
{
public:
    // Public Types
    using TokenClass = typename TTokenClassType;
    using Token = typename TTokenType;
    using TokenStream = typename TokenStream<TokenClass, Token>;

    //! @brief An interface to an node in the Abstract Syntax Tree created by the
    //! parser.
    class ISyntaxNode
    {
    protected:
        // Construction/Destruction
        ISyntaxNode() = default;
    public:
        virtual ~ISyntaxNode() = default;

        // Accessors
        //! @brief Indicates whether the current node is in a state where is does
        //! not require further tokens.
        //! @retval true The node is completed, though further tokens maybe accepted.
        //! @retval false The node is incomplete, further tokens or child nodes are
        //! required to complete it.
        virtual bool isComplete() const = 0;

        //! @brief Indicates whether the syntax node was completed without error so
        //! that post-parsing processing can be performed.
        virtual bool isValid() const = 0;

        // Operations
        //! @brief Attempts to further develop the node by allowing it to consume a
        //! token from the input stream.
        //! @param[in] context The state of the parsing process.
        //! @param[in] token The token to possibly consume.
        //! @returns Either nullptr if the token could not be applied, or a pointer
        //! to the resultant syntax node which replaces the current one if the token
        //! was consumed.
        virtual ISyntaxNode *applyToken(ParseContext &context, const Token &token) = 0;

        //! @brief Attempts to further develop the node by allowing it to consume a
        //! complete child syntax node.
        //! @param[in] context The state of the parsing process.
        //! @param[in] childNode The abstract syntax node to possibly consume.
        //! @return A pointer to of the node to replace the current one with if
        //! the child node is consumed, null if the child node is not consumed.
        virtual ISyntaxNode *applyNode(ParseContext &context, ISyntaxNode *childNode) = 0;

        //! @brief Forces the node to consume a child which failed tryApplyNode().
        //! Error messages should be generated and the node should be kept or disposed
        //! of as required.
        virtual void recover(ParseContext &context, ISyntaxNode *node) = 0;

        //! @brief As the node at the top of the parse stack, attempts to create
        //! AST node from a leading token.
        //! @param[in] nextToken The next token in the input stream.
        //! @param[out] node Receives the node, if one could be created.
        //! @retval true A node was successfully created and returned in @p node.
        //! @retval false The token was not recognised as the start of a relevant
        //! AST node, so no new node was created.
        virtual bool tryCreateNode(const Token &nextToken, ISyntaxNode *&node) const = 0;
    };

    using ISyntaxNodePtr = ISyntaxNode *;
    using ISyntaxNodeStack = std::vector<ISyntaxNodePtr>;

private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    TokenStream &_input;
    Messages &_messages;
    ISyntaxNodeStack _partialNodes;
    bool _exitRequested;
public:
    // Construction/Destruction
    ParseContext(Messages &messages, TokenStream &input, ISyntaxNodePtr rootNode) :
        _input(input),
        _messages(messages),
        _exitRequested(false)
    {
    }


    // Accessors

    //! @brief Determines whether a request has been made to exit the 
    //! parsing process.
    //! @retval true Exit was requested.
    //! @retval false No exit has been requested since the last reset.
    constexpr bool isExitRequested() const noexcept { return isExitRequested(); }
    TokenStream &getTokenInput() { return _input; }
    Messages &getMessages() { return _messages; }

    // Operations
    void requestExit()
    {
        _exitRequested = true;
    }

    //! @brief Pushes a new incomplete syntax node onto the stack of partially
    //! complete nodes.
    //! @param[in] node The syntax node to push onto the stack.
    //! @returns The size of the stack before the new node was added.
    size_t pushSyntaxNode(ISyntaxNodePtr node)
    {
        size_t state = _partialNodes.size();

        if (node != nullptr)
        {
            _partialNodes.push_back(node);
        }

        return state;
    }

    //! @brief Removes and returns the top items from the syntax node stack.
    //! @return The top item which was popped or nullptr.
    ISyntaxNodePtr popSyntaxNode()
    {
        ISyntaxNodePtr node = nullptr;

        if (_partialNodes.empty())
            return nullptr;

        node = _partialNodes.back();
        _partialNodes.pop_back();

        return node;
    }

    //! @brief Attempts to pop an incomplete syntax node from the top of the stack.
    //! @param[out] node Receives the popped node.
    //! @retval true A node was successfully popped.
    //! @retval false The stack was empty.
    bool tryPopSyntaxNode(ISyntaxNodePtr &node)
    {
        if (_partialNodes.empty())
        {
            node = nullptr;
            return false;
        }

        node = _partialNodes.back();
        _partialNodes.pop_back();
        return true;
    }

    //! @brief Attempts to obtain a syntax node from the top of the 
    //! without popping it.
    //! @param[out] node Receives the top node.
    //! @retval true The stack contains nodes and the top one was returned.
    //! @retval false The stack was empty, node is set to nullptr.
    bool tryPeekTopSyntaxNode(ISyntaxNode *&node)
    {
        node = nullptr;

        if (_partialNodes.empty() == false)
        {
            node = _partialNodes.back();
        }

        return node != nullptr;
    }

    //! @brief Disposes of syntax nodes on the top of the stack until it reaches
    //! a specified size.
    //! @param[in] state The required stack size, possibly returned by
    //! pushSyntaxNode().
    void restoreSyntaxStack(size_t state)
    {
        while (_partialNodes.size() > state)
        {
            ISyntaxNode *node = _partialNodes.back();
            _partialNodes.pop_back();
            Ag::safeDelete(node);
        }
    }

    //! @brief Consumes tokens until a specific class is found to recover from a
    //! previous error.
    //! @param[in] recoveryMarker The class of token to search for to recover the
    //! state of the parser to something predictable.
    void recover(TokenClass recoveryMarker)
    {
        Token next;

        while (tryGetNextToken(next))
        {
            if (next.getClass() == recoveryMarker)
            {
                break;
            }
        }
    }

    //! @brief Attempts to get the next token from the input stream.
    //! @param[out] next Receives the next recognised token if there is input left
    //! to process.
    //! @retval true A token was generated, although it maybe erroneous input.
    //! @retval false There were not enough characters left in the current input
    //! source to generate any token.
    bool tryGetNextToken(Token &next)
    {
        return _input.tryGetNextToken(next);
    }

    //! @brief Attempts to create a new abstract syntax node from a single
    //! starting token using the current lexical context.
    //! @param[in] startToken The token used to determine what kind of syntax node
    //! to create and to initially populate it.
    //! @param[out] node Receives a pointer to a new syntax node if successful.
    //! @retval true The token was consumed to create an object returned in node.
    //! @retval false The token was not consumed, no new node was created.
    bool tryCreateNode(const Token &startToken, ISyntaxNodePtr &node)
    {
        if ((_partialNodes.empty() == false) && 
            _partialNodes.back()->tryCreateNode(startToken, node))
        {
            // We successfully created a token, so we have no need to rewind.
            _input.commit();
            return true;
        }

        node = nullptr;
        return false;
    }

    //! @brief Marks all previously read tokens as committed, i.e. that they cannot
    //! be rewound over.
    void commitReadTokens()
    {
        _input.commit();
    }

    //! @brief Re-inserts a token back into the input stream.
    //! @param[in] previous The token to re-insert so that it will be returned by
    //! the next call to tryGetToken() or used by the next call to ensureToken().
    //! @note Only a single token can be put back at once. The returned token
    //! must be consumed before ungetToken() can be called again.
    void ungetLastToken()
    {
        _input.rewind(0);
    }

    ////! @brief Continues with the parsing process until the root node is complete
    ////! or a fatal error occurs.
    ////! @retval true No error or fatal messages were logged.
    ////! @retval false At least one error or fatal message was logged.
    //bool parseAll()
    //{
    //    return false;
    //}

    ////! @brief Continues with the parsing process until the root node is complete,
    ////! a fatal error occurs, or a mid-process exit is requested.
    ////! @return The incomplete syntax node at the top of the stack when exit was requested.
    //ISyntaxNodePtr parseIncremental()
    //{
    //    return nullptr;
    //}
};

//! @brief A structure which defined parser types based on
//! template parameters.
//! @tparam TTokenClassType The scalar type used to identify the token class
//! @tparam TTokenType The structure representing a recognised token, preferably
//! derived from the Token<> template.
template<typename TTokenClassType, typename TTokenType = Token<TTokenClassType> >
struct ParserTraits
{
    ParserTraits() = delete;
    ~ParserTraits() = delete;

    using TokenClass = typename TTokenClassType;
    using Token = typename TTokenType;
    using ITokeniser = typename ITokeniser<TTokenClassType, TTokenType>;
    using ITokeniserCPtr = typename const ITokeniser *;
    using TokenStream = typename TokenStream<TTokenClassType, TTokenType>;
    using ParseContext = typename ParseContext<TTokenClassType, TTokenType>;
    using ISyntaxNode = typename ParseContext::ISyntaxNode;
    using ISyntaxNodePtr = typename ISyntaxNode *;
    using ISyntaxNodeCPtr = typename const ISyntaxNode *;

    static bool expandNode(ParseContext &context, ISyntaxNodePtr &currentNode)
    {
        bool nodeExpanded = false;

        Token currentToken;

        // Attempt to augment the node with further tokens.
        while (context.tryGetNextToken(currentToken))
        {
            // Develop the node with more tokens, possibly replacing it.
            ISyntaxNodePtr replacement = currentNode->applyToken(context,
                                                                 currentToken);

            if (replacement == nullptr)
            {
                context.ungetLastToken();
                break;
            }
            else
            {
                context.commitReadTokens();
                currentNode = replacement;
                nodeExpanded = true;
            }
        }

        ISyntaxNodePtr parentNode = nullptr;

        if (currentNode->isComplete() && context.tryPopSyntaxNode(parentNode))
        {
            // Try to apply the current node to the parent node.
            ISyntaxNodePtr updatedParentNode = parentNode->applyNode(context, currentNode);

            if (updatedParentNode == nullptr)
            {
                // The current node could not be applied to the parent, i.e.
                // it is an orphan.
                context.pushSyntaxNode(parentNode);

                // TODO: Do something sane here.
                Ag::safeDelete(currentNode);
            }
            else
            {
                // Pop the parent node from the stack for further development
                // now that it has consumed the current node.
                currentNode = updatedParentNode;
                nodeExpanded = true;
            }
        }

        if ((currentNode != nullptr) && (nodeExpanded == false))
        {
            // No changes were made to the node on the last iteration.
            if (currentNode->isComplete())
            {
                parentNode = nullptr;

                if (context.tryPeekTopSyntaxNode(parentNode))
                {
                    // It's a complete node which its parent doesn't
                    // want to consume.
                    parentNode->recover(context, currentNode);
                }
                else
                {
                    // It's the root node, put it back.
                    context.pushSyntaxNode(currentNode);
                }
            }
            else
            {
                // Push the incomplete node back onto the stack.
                context.pushSyntaxNode(currentNode);
            }

            // Either way, we don't want to develop this node further
            // at this time.
            currentNode = nullptr;
        }

        return nodeExpanded;
    }

    static void parseAll(TokenStream &input,
                         ISyntaxNodePtr rootNode,
                         Messages &messages)
    {
        // Constructs a new context for the parsing process.
        ParseContext context(messages, input, rootNode);

        // Pair the syntax node stack back down to the root element.
        context.restoreSyntaxStack(0);
        context.pushSyntaxNode(rootNode);

        ISyntaxNodePtr currentNode = nullptr;

        // Process all tokens in the current input source.
        Token currentToken;

        while (context.tryGetNextToken(currentToken) &&
               context.tryCreateNode(currentToken, currentNode))
        {
            // Keep developing the current node, perhaps with more tokens
            // or by applying it to a partially complete parent node and making
            // the parent the current node.
            while (currentNode != nullptr)
            {
                // Attempt to augment the node with further tokens.
                expandNode(context, currentNode);
            }
        }

        if (currentNode == nullptr)
        {
            //if (currentToken.getClass() != TokenClass::Empty)
            //{
            //    // We failed to process the token into a syntax node.
            //    if (currentToken.getValue().isEmpty())
            //    {
            //        context.getMessages().log(currentToken.getLocation(),
            //                                  Severity::Error,
            //                                  "Unexpected token.");
            //    }
            //    else
            //    {
            //        context.getMessages().log(currentToken.getLocation(),
            //                                  Severity::Error,
            //                                  "Unexpected token '{0}'.",
            //                                  { currentToken.getValue() });
            //    }
            //}
        }
        else
        {
            // The input source has been processed, try to revert back to the
            // one which it was referenced from, if any.
            context.pushSyntaxNode(currentNode);
            currentNode = nullptr;
        }
    }
};

}} // namespace Ag::Text

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
