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

		Token(TokenKind kind, std::string value, int start, int end) : Kind(kind), Value(value), Start(start), End(end) {

		}

		static std::string get_token_kind_description(TokenKind kind) {
			switch (kind) {
			case TokenKind::EOF:
				return "EOF";
			case TokenKind::BANG:
				return "!";
			case TokenKind::DOLLAR:
				return "$";
			case TokenKind::PAREN_L:
				return "(";
			case TokenKind::PAREN_R:
				return ")";
			case TokenKind::SPREAD:
				return "...";
			case TokenKind::COLON:
				return ":";
			case TokenKind::EQUALS:
				return "=";
			case TokenKind::AT:
				return "@";
			case TokenKind::BRACKET_L:
				return "[";
			case TokenKind::BRACKET_R:
				return "]";
			case TokenKind::BRACE_L:
				return "{";
			case TokenKind::PIPE:
				return "|";
			case TokenKind::BRACE_R:
				return "}";
			case TokenKind::NAME:
				return "Name";
			case TokenKind::INT:
				return "Int";
			case TokenKind::FLOAT:
				return "Float";
			case TokenKind::STRING:
				return "String";
			case TokenKind::COMMENT:
				return "#";
			default:
				return "";
			}
		}

		std::string to_string() {
			return (Value.length() > 0) ? get_token_kind_description(Kind) + " \"" + Value + "\"" : get_token_kind_description(Kind);
		}
	};
}
