#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/LexerContext.h>

namespace GraphQLParser {
    Token Lexer::Lex(Source source) {
        return Lex(source, 0);
    }

    Token Lexer::Lex(Source source, int start) {
        LexerContext context(source, start/*, Cache*/);

        return context.GetToken();
    }
}
