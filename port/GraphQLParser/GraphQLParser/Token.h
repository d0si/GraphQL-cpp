#pragma once

#include <string>
#include <GraphQLParser/TokenKind.h>

namespace GraphQLParser {
	class Token {
	public:
		int End;
		TokenKind Kind;
		int Start;
		std::string Value;

		Token(const TokenKind& kind, const std::string& value, int start, int end);

		std::string to_string() const;

		static std::string get_token_kind_description(const TokenKind& kind);
	};
}
