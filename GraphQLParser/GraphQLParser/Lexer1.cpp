#include <GraphQLParser/Lexer1.h>

namespace GraphQLParser {
    Token Lexer::Lex(Source source) {
        return Lex(source, 0);
    }

    Token Lexer::Lex(Source source, int start) {
        // TODO:
        return Token(TokenKind::UNKNOWN, "", 0, 0);
        //auto context = new LexerContext(source, start, Cache);

        //return context.GetToken();
    }
}
