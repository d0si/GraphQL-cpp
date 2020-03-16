#include <GraphQLParser/Token.h>

namespace GraphQLParser {
	Token::Token(const TokenKind& kind, const std::string& value, int start, int end) : Kind(kind), Value(value), Start(start), End(end) {

	}

	std::string Token::to_string() const {
		return (Value.length() > 0) ? get_token_kind_description(Kind) + " \"" + Value + "\"" : get_token_kind_description(Kind);
	}

	std::string Token::get_token_kind_description(const TokenKind& kind) {
		switch (kind) {
		case TokenKind::EOF_:
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
}
