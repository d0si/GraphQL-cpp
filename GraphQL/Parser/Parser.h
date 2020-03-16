#pragma once

#include <string>
#include <regex>

namespace GraphQL {
    namespace Parser {
        enum class TokenKind {
            EOF_ = 1,
            BANG = 2,
            DOLLAR = 3,
            PAREN_L = 4,
            PAREN_R = 5,
            SPREAD = 6,
            COLON = 7,
            EQUALS = 8,
            AT = 9,
            BRACKET_L = 10,
            BRACKET_R = 11,
            BRACE_L = 12,
            PIPE = 13,
            BRACE_R = 14,
            NAME = 15,
            INT = 16,
            FLOAT = 17,
            STRING = 18,
            COMMENT = 19,
            UNKNOWN = 20
        };

        class Token {
        public:
            const TokenKind kind;
            const std::string value;
            const int start;
            const int end;

            Token(const TokenKind& kind, const std::string& value, int start, int end) : kind(kind), value(value), start(start), end(end) {

            }

            std::string to_string() const {
                return (value.length() > 0) ? get_token_kind_description(kind) + " \"" + value + "\"" : get_token_kind_description(kind);
            }

            static std::string get_token_kind_description(const TokenKind& kind) {
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
        };

        class Lexer {
        private:
            int current_index_;
            const Source& source_;

        public:
            Lexer(const Source& source) : source_(source) {

            }

            Token lex() {
                return lex(0);
            }

            Token lex(int start) {
                
            }
        };

        class Source {
        private:
            std::string body_;
            std::string name_;

        public:
            Source(const std::string& body) : Source(body, "GraphQL") {

            }

            Source(const std::string& body, const std::string& name) : body_(monetize_line_breaks(body)), name_(name) {

            }

            std::string monetize_line_breaks(const std::string& input) const {
                return std::regex_replace(std::regex_replace(input, std::regex("\r\n"), "\n"), std::regex("\r"), "\n");
            }

            const std::string& get_body() const {
                return body_;
            }

            const std::string& get_name() const {
                return name_;
            }
        };

        class Parser {
        private:
            Lexer lexer_;
            Token current_token_;

        public:
            Parser(const Source& source) : lexer_(Lexer(source)), current_token_(lexer_.lex()) {
                
            }

            void* /*Types::Document*/ parse() {
                int start = current_token_.start;


                return nullptr;
            }

        private:

        };
    }
}
