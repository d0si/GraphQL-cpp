#include <GraphQL/Parser/Parser.h>

namespace GraphQL {
    namespace Parser {
        Parser::Parser(const Source& source) : lexer_(Lexer(source)), current_token_(lexer_.lex()) {

        }

        void* /*Types::Document*/ Parser::parse() {
            int start = current_token_.start;


            return nullptr;
        }
    }
}
