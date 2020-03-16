#pragma once

#include <GraphQL/Parser/Lexer.h>

namespace GraphQL {
    namespace Parser {
        class Parser {
        private:
            Lexer lexer_;
            Token current_token_;

        public:
            Parser(const Source& source);

            void* /*Types::Document*/ parse();
        };
    }
}
