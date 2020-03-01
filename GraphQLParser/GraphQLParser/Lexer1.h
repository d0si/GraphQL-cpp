#pragma once

#include <GraphQLParser/Token.h>
#include <GraphQLParser/Source.h>

namespace GraphQLParser {
	class Lexer {
    public:
        //ILexemeCache Cache;

        Token Lex(Source source);
        Token Lex(Source source, int start);
	};
}
