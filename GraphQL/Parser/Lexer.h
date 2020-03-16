#pragma once

#include <GraphQL/Parser/Token.h>
#include <GraphQL/Parser/Source.h>

namespace GraphQL {
    namespace Parser {
        class Lexer {
        private:
            size_t current_index_ = 0;
            const Source& source_;

        public:
            Lexer(const Source& source);

            Token lex();
            Token lex(int start);

        private:
            int get_position_after_whitespace(int start) const;
            void validate_character_code(char code) const;

            Token check_for_punctuation_tokens(char code) const;
            Token create_punctuation_token(TokenKind kind, int offset) const;
            Token create_unknown_token() const;
            Token check_for_spread_operator() const;

            Token read_comment();
            Token read_name();
            Token read_number();
            Token read_string();

            char process_character(std::string& value, size_t chunk_start);
            char get_code() const;
            bool is_not_at_the_end_of_query() const;

            char get_value_from_escape_sequence_code(char code);
            char get_unicode_char();
            int char_to_hex(char code) const;
            char next_code();

            bool is_valid_name_character(char code) const;

            char read_digits(char first_code);
            std::string resolve_char_name(char code, std::string unicode_string = "") const;

            void check_for_invalid_characters(char code) const;
            void check_string_termination(char code) const;
        };
    }
}
