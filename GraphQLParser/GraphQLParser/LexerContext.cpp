#include <GraphQLParser/LexerContext.h>
#include <ctype.h>
#include <GraphQLParser/Exceptions/GraphQLSyntaxErrorException.h>

namespace GraphQLParser {
	LexerContext::LexerContext(Source source, int index) : source(source), current_index(index) {

	}

	Token LexerContext::GetToken() {
		if (source.Body == "") {
			return CreateEOFToken();
		}

		current_index = GetPositionAfterWhitespace(source.Body, current_index);

		if (current_index >= source.Body.length()) {
			return CreateEOFToken();
		}

		char code = source.Body[current_index];

		ValidateCharacterCode(code);

		Token token = CheckForPunctuationTokens(code);
		if (token.Kind != TokenKind::UNKNOWN) {
			return token;
		}
		else if (code == '#') {
			return ReadComment();
		}
		else if (isalpha(code) || code == '_') {
			return ReadName();
		}
		else if (isdigit(code) || code == '-') {
			return ReadNumber();
		}
		else if (code == '"') {
			return ReadString();
		}

		throw Exceptions::GraphQLSyntaxErrorException("Unexpected character " + code, source, current_index);
	}

	Token LexerContext::CreateEOFToken() {
		return Token(TokenKind::EOF_, "", current_index, current_index);
	}

	int LexerContext::GetPositionAfterWhitespace(std::string body, int start) {
		int position = start;

		while (position < body.length()) {
			char code = body[position];

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

	void LexerContext::ValidateCharacterCode(int code) {
		if (code < 0x0020 && code != 0x0009 && code != 0x000A && code != 0x000D) {
			throw Exceptions::GraphQLSyntaxErrorException("Invalid character " + (char)code, source, current_index);
		}
	}

	Token LexerContext::CheckForPunctuationTokens(char code) {
		switch (code) {
		case '!':
			return CreatePunctuationToken(TokenKind::BANG, 1);
		case '$':
			return CreatePunctuationToken(TokenKind::DOLLAR, 1);
		case '(':
			return CreatePunctuationToken(TokenKind::PAREN_L, 1);
		case ')':
			return CreatePunctuationToken(TokenKind::PAREN_R, 1);
		case '.':
			return CheckForSpreadOperator();
		case ':':
			return CreatePunctuationToken(TokenKind::COLON, 1);
		case '=':
			return CreatePunctuationToken(TokenKind::EQUALS, 1);
		case '@':
			return CreatePunctuationToken(TokenKind::AT, 1);
		case '[':
			return CreatePunctuationToken(TokenKind::BRACKET_L, 1);
		case ']':
			return CreatePunctuationToken(TokenKind::BRACKET_R, 1);
		case '{':
			return CreatePunctuationToken(TokenKind::BRACE_L, 1);
		case '|':
			return CreatePunctuationToken(TokenKind::PIPE, 1);
		case '}':
			return CreatePunctuationToken(TokenKind::BRACE_R, 1);
		default:
			return CreateUnknownToken();
		}
	}

	Token LexerContext::CreatePunctuationToken(TokenKind kind, int offset) {
		return Token(kind, "", current_index, current_index + offset);
	}

	Token LexerContext::CreateUnknownToken() {
		return Token(TokenKind::UNKNOWN, "", current_index, current_index);
	}

	Token LexerContext::CheckForSpreadOperator() {
		char char1 = source.Body.length() > current_index + 1 ? source.Body[current_index + 1] : 0;
		char char2 = source.Body.length() > current_index + 2 ? source.Body[current_index + 2] : 0;

		if (char1 == '.' && char2 == '.') {
			return CreatePunctuationToken(TokenKind::SPREAD, 3);
		}

		return CreateUnknownToken();
	}

	Token LexerContext::ReadComment() {
		int start = current_index;

		int chunk_start = ++current_index;
		char code = GetCode();
		std::string value = "";

		while (IsNotAtTheEndOfQuery() && code != 0x000A && code != 0x000D) {
			code = ProcessCharacter(value, chunk_start);
		}

		value += source.Body.substr(chunk_start, current_index - chunk_start);

		return Token(TokenKind::COMMENT, value, start, current_index + 1);
	}

	Token LexerContext::ReadName() {
		int start = current_index;
		char code;

		do {
			current_index++;
			code = GetCode();
		} while (IsNotAtTheEndOfQuery() && IsValidNameCharacter(code));

		return CreateNameToken(start);
	}

	Token LexerContext::ReadNumber() {
		bool is_float = false;
		int start = current_index;
		char code = source.Body[start];

		if (code == '-') {
			code = NextCode();
		}

		char next_code = (code == '0') ? NextCode() : ReadDigitsFromOwnSource(code);

		if (next_code >= 48 && next_code <= 57) {
			std::string error_message = "Invalid number, unexpected digit after " + code;
			error_message += ": \"" + next_code;
			error_message += "\"";
			throw Exceptions::GraphQLSyntaxErrorException(error_message, source, current_index);
		}

		code = next_code;
		if (code == '.') {
			is_float = true;
			code = ReadDigitsFromOwnSource(NextCode());
		}

		if (code == 'E' || code == 'e') {
			is_float = true;
			code = NextCode();
			if (code == '+' || code == '-') {
				code = NextCode();
			}

			code = ReadDigitsFromOwnSource(code);
		}

		return is_float ? CreateFloatToken(start) : CreateIntToken(start);
	}

	Token LexerContext::ReadString() {
		int start = current_index;
		std::string value = ProcessStringChunks();

		return Token(TokenKind::STRING, value, start, current_index + 1);
	}

	char LexerContext::GetCode() {
		return IsNotAtTheEndOfQuery() ? source.Body[current_index] : (char)0;
	}

	bool LexerContext::IsNotAtTheEndOfQuery() {
		return current_index < source.Body.length();
	}

	char LexerContext::ProcessCharacter(std::string& value, int& chunk_start) {
		char code = GetCode();
		++current_index;

		if (code == '\\') {
			value = AppendToValueByCode(AppendCharactersFromLastChunk(value, chunk_start), GetCode());

			++current_index;
			chunk_start = current_index;
		}

		return GetCode();
	}

	std::string LexerContext::AppendToValueByCode(std::string value, char code) {
		switch (code) {
		case '"':
			value += '"';
			break;
		case '/':
			value += '/';
			break;
		case '\\':
			value += '\\';
			break;
		case 'b':
			value += '\b';
			break;
		case 'f':
			value += '\f';
			break;
		case 'n':
			value += '\n';
			break;
		case 'r':
			value += '\r';
			break;
		case 't':
			value += '\t';
			break;
		case 'u':
			value += GetUnicodeChar();
			break;
		default:
			throw Exceptions::GraphQLSyntaxErrorException("Invalid character escape sequence \\" + code, source, current_index);
		}

		return value;
	}

	std::string LexerContext::AppendCharactersFromLastChunk(std::string value, int chunk_start) {
		return value + source.Body.substr(chunk_start, current_index - chunk_start - 1);
	}

	char LexerContext::GetUnicodeChar() {
		if (current_index + 5 > source.Body.length()) {
			std::string truncated_expression = source.Body.substr(current_index);

			throw Exceptions::GraphQLSyntaxErrorException("Invalid character escape sequence at EOF: \\" + truncated_expression, source, current_index);
		}

		return (char)(
			CharToHex(NextCode()) << 12 |
			CharToHex(NextCode()) << 8 |
			CharToHex(NextCode()) << 4 |
			CharToHex(NextCode()));
	}

	int LexerContext::CharToHex(char code) {
		throw Exceptions::GraphQLSyntaxErrorException("Hex conversion is currently not implemented", source, current_index);
	}

	char LexerContext::NextCode() {
		current_index++;

		return IsNotAtTheEndOfQuery() ? source.Body[current_index] : (char)0;
	}

	bool LexerContext::IsValidNameCharacter(char code) {
		return code == '_' || isalnum(code);
	}
	
	Token LexerContext::CreateNameToken(int start) {
		return Token(TokenKind::NAME, source.Body.substr(start, current_index - start), start, current_index);
	}

	char LexerContext::ReadDigitsFromOwnSource(char code) {
		current_index = ReadDigits(source, current_index, code);

		return GetCode();
	}
	
	int LexerContext::ReadDigits(Source source, int start, char first_code) {
		std::string body = source.Body;
		int position = start;
		char code = first_code;

		if (!isdigit(code)) {
			throw Exceptions::GraphQLSyntaxErrorException("Invalid number, expected digit but got: " + ResolveCharName(code), source, current_index);
		}

		do {
			code = (++position < body.length()) ? body[position] : (char)0;
		} while (isdigit(code));

		return position;
	}

	std::string LexerContext::ResolveCharName(char code, std::string unicode_string) {
		if (code == '\0') {
			return "<EOF>";
		}

		if (unicode_string != "") {
			return "\"" + unicode_string + "\"";
		}

		return "\"" + code + '\"';
	}

	Token LexerContext::CreateFloatToken(int start) {
		return Token(TokenKind::FLOAT, source.Body.substr(start, current_index - start), start, current_index);
	}

	Token LexerContext::CreateIntToken(int start) {
		return Token(TokenKind::INT, source.Body.substr(start, current_index - start), start, current_index);
	}

	std::string LexerContext::ProcessStringChunks() {
		int chunk_start = ++current_index;
		char code = GetCode();
		std::string value = "";

		while (IsNotAtTheEndOfQuery() && code != 0x000A && code != 0x000D && code != '"') {
			CheckForInvalidCharacters(code);
			code = ProcessCharacter(value, chunk_start);
		}

		CheckStringTermination(code);
		value += source.Body.substr(chunk_start, current_index - chunk_start);

		return value;
	}

	void LexerContext::CheckForInvalidCharacters(char code) {
		if (code < 0x0020 && code != 0x0009) {
			throw Exceptions::GraphQLSyntaxErrorException("Invalid character within String: " + code, source, current_index);
		}
	}

	void LexerContext::CheckStringTermination(char code) {
		if (code != '"') {
			throw Exceptions::GraphQLSyntaxErrorException("Unterminated string.", source, current_index);
		}
	}
}
