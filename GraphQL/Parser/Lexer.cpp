#include <GraphQL/Parser/Lexer.h>
#include <GraphQL/Exceptions/SyntaxErrorException.h>

namespace GraphQL {
    namespace Parser {
        Lexer::Lexer(const Source& source) : source_(source) {

        }

        Token Lexer::lex() {
            return lex(0);
        }

        Token Lexer::lex(int start) {
            if (source_.body.length() == 0) {
                return Token(TokenKind::EOF_, "", current_index_, current_index_);
            }

            current_index_ = get_position_after_whitespace(current_index_);

            if (current_index_ >= source_.body.length()) {
                return Token(TokenKind::EOF_, "", current_index_, current_index_);
            }

            char code = source_.body[current_index_];

            validate_character_code(code);

            Token token = check_for_punctuation_tokens(code);
            if (token.kind != TokenKind::UNKNOWN) {
                return token;
            }
            else if (code == '#') {
                return read_comment();
            }
            else if (isalpha(code) || code == '_') {
                return read_name();
            }
            else if (isdigit(code) || code == '-') {
                return read_number();
            }
            else if (code == '"') {
                return read_string();
            }

            throw Exceptions::SyntaxErrorException("Unexpected character " + code, source_, current_index_);
        }

        int Lexer::get_position_after_whitespace(int start) const {
            int position = start;

            while (position < source_.body.length()) {
                char code = source_.body[position];

                if (/*code == '\xFEFF' || */code == '\t' || code == ' ' || code == '\n' || code == '\r' || code == ',') {
                    ++position;
                }
                /*else if (code == '#') {
                    position = WaitForEndOfComment(body, position, code);
                }*/
                else {
                    return position;
                }
            }

            return position;
        }

        void Lexer::validate_character_code(char code) const {
            if (code < 0x0020 && code != 0x0009 && code != 0x000A && code != 0x000D) {
                throw Exceptions::SyntaxErrorException("Invalid character " + (char)code, source_, current_index_);
            }
        }

        Token Lexer::check_for_punctuation_tokens(char code) const {
            switch (code) {
            case '!':
                return create_punctuation_token(TokenKind::BANG, 1);
            case '$':
                return create_punctuation_token(TokenKind::DOLLAR, 1);
            case '(':
                return create_punctuation_token(TokenKind::PAREN_L, 1);
            case ')':
                return create_punctuation_token(TokenKind::PAREN_R, 1);
            case '.':
                return check_for_spread_operator();
            case ':':
                return create_punctuation_token(TokenKind::COLON, 1);
            case '=':
                return create_punctuation_token(TokenKind::EQUALS, 1);
            case '@':
                return create_punctuation_token(TokenKind::AT, 1);
            case '[':
                return create_punctuation_token(TokenKind::BRACKET_L, 1);
            case ']':
                return create_punctuation_token(TokenKind::BRACKET_R, 1);
            case '{':
                return create_punctuation_token(TokenKind::BRACE_L, 1);
            case '|':
                return create_punctuation_token(TokenKind::PIPE, 1);
            case '}':
                return create_punctuation_token(TokenKind::BRACE_R, 1);
            default:
                return create_unknown_token();
            }
        }

        Token Lexer::create_punctuation_token(TokenKind kind, int offset) const {
            return Token(kind, "", current_index_, current_index_ + offset);
        }

        Token Lexer::create_unknown_token() const {
            return Token(TokenKind::UNKNOWN, "", current_index_, current_index_);
        }

        Token Lexer::check_for_spread_operator() const {
            char char1 = source_.body.length() > current_index_ + 1 ? source_.body[current_index_ + 1] : 0;
            char char2 = source_.body.length() > current_index_ + 2 ? source_.body[current_index_ + 2] : 0;

            if (char1 == '.' && char2 == '.') {
                return create_punctuation_token(TokenKind::SPREAD, 3);
            }

            return create_unknown_token();
        }

        Token Lexer::read_comment() {
            int start = current_index_;

            size_t chunk_start = ++current_index_;
            char code = get_code();
            std::string value = "";

            while (is_not_at_the_end_of_query() && code != 0x000A && code != 0x000D) {
                code = process_character(value, chunk_start);
            }

            value += source_.body.substr(chunk_start, current_index_ - chunk_start);

            return Token(TokenKind::COMMENT, value, start, current_index_ + 1);
        }

        Token Lexer::read_name() {
            int start = current_index_;
            char code;

            do {
                ++current_index_;
                code = get_code();
            } while (is_not_at_the_end_of_query() && is_valid_name_character(code));

            return Token(TokenKind::NAME, source_.body.substr(start, current_index_ - start), start, current_index_);
        }

        Token Lexer::read_number() {
            bool is_float = false;
            int start = current_index_;
            char code = source_.body[start];

            if (code == '-') {
                code = next_code();
            }

            char code_1 = (code == '0') ? next_code() : read_digits(code);

            if (code_1 >= 48 && code_1 <= 57) {
                std::string error_message = "Invalid number, unexpected digit after " + code;
                error_message += ": \"" + code_1;
                error_message += "\"";
                throw Exceptions::SyntaxErrorException(error_message, source_, current_index_);
            }

            code = code_1;
            if (code == '.') {
                is_float = true;
                code = read_digits(next_code());
            }

            if (code == 'E' || code == 'e') {
                is_float = true;
                code = next_code();
                if (code == '+' || code == '-') {
                    code = next_code();
                }

                code = read_digits(code);
            }

            return Token(is_float ? TokenKind::FLOAT : TokenKind::INT, source_.body.substr(start, current_index_ - start), start, current_index_);
        }

        Token Lexer::read_string() {
            int start = current_index_;

            int chunk_start = ++current_index_;
            char code = get_code();
            std::string value = "";
            while (is_not_at_the_end_of_query() && code != 0x000A && code != 0x000D && code != '"') {
                check_for_invalid_characters(code);
                code = process_character(value, chunk_start);
            }

            check_string_termination(code);
            value += source_.body.substr(chunk_start, current_index_ - chunk_start);

            return Token(TokenKind::STRING, value, start, current_index_ + 1);
        }

        char Lexer::process_character(std::string& value, size_t chunk_start) {
            char code = get_code();
            ++current_index_;

            if (code == '\\') {
                value += source_.body.substr(chunk_start, current_index_ - chunk_start - 1)
                    + get_value_from_escape_sequence_code(get_code());

                ++current_index_;
                chunk_start = current_index_;
            }

            return get_code();
        }

        char Lexer::get_code() const {
            return is_not_at_the_end_of_query() ? source_.body[current_index_] : (char)0;
        }

        bool Lexer::is_not_at_the_end_of_query() const {
            return current_index_ < source_.body.length();
        }

        char Lexer::get_value_from_escape_sequence_code(char code) {
            switch (code) {
            case '"':
                return '"';
            case '/':
                return '/';
            case '\\':
                return '\\';
            case 'b':
                return '\b';
            case 'f':
                return '\f';
            case 'n':
                return '\n';
            case 'r':
                return '\r';
            case 't':
                return '\t';
            case 'u':
                return get_unicode_char();
            }

            throw Exceptions::SyntaxErrorException("Invalid character escape sequence \\" + code, source_, current_index_);
        }

        char Lexer::get_unicode_char() {
            if (current_index_ + 5 > source_.body.length()) {
                std::string truncated_expression = source_.body.substr(current_index_);

                throw Exceptions::SyntaxErrorException("Invalid character escape sequence at EOF: \\" + truncated_expression, source_, current_index_);
            }

            return (char)(
                char_to_hex(next_code()) << 12 |
                char_to_hex(next_code()) << 8 |
                char_to_hex(next_code()) << 4 |
                char_to_hex(next_code()));
        }

        int Lexer::char_to_hex(char code) const {
            throw Exceptions::SyntaxErrorException("Hex conversion is currently not implemented", source_, current_index_);
        }

        char Lexer::next_code() {
            ++current_index_;

            return is_not_at_the_end_of_query() ? source_.body[current_index_] : (char)0;
        }

        bool Lexer::is_valid_name_character(char code) const {
            return code == '_' || isalnum(code);
        }

        char Lexer::read_digits(char first_code) {
            char code = first_code;

            if (!isdigit(code)) {
                throw Exceptions::SyntaxErrorException("Invalid number, expected digit but got: " + resolve_char_name(code), source_, current_index_);
            }

            do {
                code = (current_index_ < source_.body.length()) ? source_.body[current_index_] : (char)0;
            } while (isdigit(code));

            return get_code();
        }
        
        std::string Lexer::resolve_char_name(char code, std::string unicode_string = "") const {
            if (code == '\0') {
                return "<EOF>";
            }

            if (unicode_string != "") {
                return "\"" + unicode_string + "\"";
            }

            return "\"" + code + '\"';
        }
        
        void Lexer::check_for_invalid_characters(char code) const {
            if (code < 0x0020 && code != 0x0009) {
                throw Exceptions::SyntaxErrorException("Invalid character within String: " + code, source_, current_index_);
            }
        }

        void Lexer::check_string_termination(char code) const {
            if (code != '"') {
                throw Exceptions::SyntaxErrorException("Unterminated string.", source_, current_index_);
            }
        }
    }
}
