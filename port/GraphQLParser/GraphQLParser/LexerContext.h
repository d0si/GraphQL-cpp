#pragma once

#include <GraphQLParser/Source.h>
#include <GraphQLParser/Token.h>

namespace GraphQLParser {
	class LexerContext {
	private:
		int current_index;
		const Source source;

	public:
		LexerContext(Source source, int index);

		Token GetToken();

	private:
		Token CreateEOFToken();
		int GetPositionAfterWhitespace(std::string body, int start);
		void ValidateCharacterCode(int code);

		Token CheckForPunctuationTokens(char code);
		Token CreatePunctuationToken(TokenKind kind, int offset);
		Token CreateUnknownToken();
		Token CheckForSpreadOperator();

		Token ReadComment();
		Token ReadName();
		Token ReadNumber();
		Token ReadString();

		char GetCode();
		bool IsNotAtTheEndOfQuery();
		char ProcessCharacter(std::string& value, int& chunk_start);
		std::string AppendToValueByCode(std::string value, char code);
		std::string AppendCharactersFromLastChunk(std::string value, int chunk_start);
		char GetUnicodeChar();
		int CharToHex(char code);
		char NextCode();

		bool IsValidNameCharacter(char code);
		Token CreateNameToken(int start);

		char ReadDigitsFromOwnSource(char code);
		int ReadDigits(Source source, int start, char first_code);
		std::string ResolveCharName(char code, std::string unicode_string = "");
		Token CreateFloatToken(int start);
		Token CreateIntToken(int start);

		std::string ProcessStringChunks();
		void CheckForInvalidCharacters(char code);
		void CheckStringTermination(char code);
	};
}
