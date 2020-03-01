#pragma once

#include <GraphQLParser/ILexer.h>
#include <GraphQLParser/Token.h>
#include <GraphQLParser/ISource.h>

namespace GraphQLParser {
	class Lexer : public ILexer {
    public:
        ILexemeCache Cache;

        Token Lex(ISource source) {
            return Lex(source, 0);
        }

        Token Lex(ISource source, int start) {
            auto context = new LexerContext(source, start, Cache);

            return context.GetToken();
        }
	};
}
