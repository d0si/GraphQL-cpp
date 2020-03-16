#pragma once

#include <string>
#include <GraphQL/Parser/TokenKind.h>

namespace GraphQL {
	namespace Parser {
        class Token {
        public:
            const TokenKind kind;
            const std::string value;
            const int start;
            const int end;

            Token(const TokenKind& kind, const std::string& value, int start, int end);

            std::string to_string() const;

            static std::string get_token_kind_description(const TokenKind& kind);
        };
	}
}
