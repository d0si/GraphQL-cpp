#include "pch.h"
#include "CppUnitTest.h"
#include <GraphQLParser/Token.h>
#include <GraphQLParser/Lexer1.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GraphQLParser;

namespace GraphQLParserTests {
	TEST_CLASS(LexerTests) {
	public:
		TEST_METHOD(Lex_ATPunctuation_HasCorrectEnd) {
			auto token = GetATPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_ATPunctuation_HasCorrectKind) {
			auto token = GetATPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::AT == token.Kind);
		}

		TEST_METHOD(Lex_ATPunctuation_HasCorrectStart) {
			auto token = GetATPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}
		
		TEST_METHOD(Lex_ATPunctuation_HasCorrectValue) {
			auto token = GetATPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}
		

		TEST_METHOD(Lex_BangPunctuation_HasCorrectEnd) {
			auto token = GetBangPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_BangPunctuation_HasCorrectKind) {
			auto token = GetBangPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::BANG == token.Kind);
		}

		TEST_METHOD(Lex_BangPunctuation_HasCorrectStart) {
			auto token = GetBangPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_BangPunctuation_HasCorrectValue) {
			auto token = GetBangPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_ColonPunctuation_HasCorrectEnd) {
			auto token = GetColonPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_ColonPunctuation_HasCorrectKind) {
			auto token = GetColonPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::COLON == token.Kind);
		}

		TEST_METHOD(Lex_ColonPunctuation_HasCorrectStart) {
			auto token = GetColonPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_ColonPunctuation_HasCorrectValue) {
			auto token = GetColonPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_DollarPunctuation_HasCorrectEnd) {
			auto token = GetDollarPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_DollarPunctuation_HasCorrectKind) {
			auto token = GetDollarPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::DOLLAR == token.Kind);
		}

		TEST_METHOD(Lex_DollarPunctuation_HasCorrectStart) {
			auto token = GetDollarPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_DollarPunctuation_HasCorrectValue) {
			auto token = GetDollarPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_EmptySource_ReturnsEOF) {
			auto token = Lexer().Lex(Source(""));

			Assert::IsTrue(TokenKind::EOF_ == token.Kind);
		}


		TEST_METHOD(Lex_EqualsPunctuation_HasCorrectEnd) {
			auto token = GetEqualsPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_EqualsPunctuation_HasCorrectKind) {
			auto token = GetEqualsPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::EQUALS == token.Kind);
		}

		TEST_METHOD(Lex_EqualsPunctuation_HasCorrectStart) {
			auto token = GetEqualsPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_EqualsPunctuation_HasCorrectValue) {
			auto token = GetEqualsPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_EscapedStringPunctuation_HasCorrectEnd) {
			auto token = GetEscapedStringPunctuationTokenLexer();
			Assert::AreEqual(20, token.End);
		}

		TEST_METHOD(Lex_EscapedStringPunctuation_HasCorrectKind) {
			auto token = GetEscapedStringPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::STRING == token.Kind);
		}

		TEST_METHOD(Lex_EscapedStringPunctuation_HasCorrectStart) {
			auto token = GetEscapedStringPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_EscapedStringPunctuation_HasCorrectValue) {
			auto token = GetEscapedStringPunctuationTokenLexer();
			Assert::AreEqual(std::string("escaped \n\r\b\t\f"), token.Value);
		}


		TEST_METHOD(Lex_LeftBracePunctuation_HasCorrectEnd) {
			auto token = GetLeftBracePunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_LeftBracePunctuation_HasCorrectKind) {
			auto token = GetLeftBracePunctuationTokenLexer();
			Assert::IsTrue(TokenKind::BRACE_L == token.Kind);
		}

		TEST_METHOD(Lex_LeftBracePunctuation_HasCorrectStart) {
			auto token = GetLeftBracePunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_LeftBracePunctuation_HasCorrectValue) {
			auto token = GetLeftBracePunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_LeftBracketPunctuation_HasCorrectEnd) {
			auto token = GetLeftBracketPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_LeftBracketPunctuation_HasCorrectKind) {
			auto token = GetLeftBracketPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::BRACKET_L == token.Kind);
		}

		TEST_METHOD(Lex_LeftBracketPunctuation_HasCorrectStart) {
			auto token = GetLeftBracketPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_LeftBracketPunctuation_HasCorrectValue) {
			auto token = GetLeftBracketPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_LeftParenthesisPunctuation_HasCorrectEnd) {
			auto token = GetLeftParenthesisPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_LeftParenthesisPunctuation_HasCorrectKind) {
			auto token = GetLeftParenthesisPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::PAREN_L == token.Kind);
		}

		TEST_METHOD(Lex_LeftParenthesisPunctuation_HasCorrectStart) {
			auto token = GetLeftParenthesisPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_LeftParenthesisPunctuation_HasCorrectValue) {
			auto token = GetLeftParenthesisPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_MultipleDecimalsIntToken_HasCorrectEnd) {
			auto token = GetMultipleDecimalsIntTokenLexer();
			Assert::AreEqual(3, token.End);
		}

		TEST_METHOD(Lex_MultipleDecimalsIntToken_HasIntKind) {
			auto token = GetMultipleDecimalsIntTokenLexer();
			Assert::IsTrue(TokenKind::INT == token.Kind);
		}

		TEST_METHOD(Lex_MultipleDecimalsIntToken_HasCorrectStart) {
			auto token = GetMultipleDecimalsIntTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_MultipleDecimalsIntToken_HasCorrectValue) {
			auto token = GetMultipleDecimalsIntTokenLexer();
			Assert::AreEqual(std::string("123"), token.Value);
		}


		TEST_METHOD(Lex_NameTokenWithComments_HasCorrectEnd) {
			auto token = GetSingleNameTokenLexerWithComments();
			Assert::AreEqual(10, token.End);
		}

		TEST_METHOD(Lex_NameTokenWithComments_HasNameKind) {
			auto token = GetSingleNameTokenLexerWithComments();
			Assert::IsTrue(TokenKind::COMMENT == token.Kind);
		}

		TEST_METHOD(Lex_NameTokenWithComments_HasCorrectStart) {
			auto token = GetSingleNameTokenLexerWithComments();
			Assert::AreEqual(1, token.Start);
		}

		TEST_METHOD(Lex_NameTokenWithComments_HasCorrectValue) {
			auto token = GetSingleNameTokenLexerWithComments();
			Assert::AreEqual(std::string("comment"), token.Value);
		}
		

		TEST_METHOD(Lex_NameTokenWithWhitespaces_HasCorrectEnd) {
			auto token = GetSingleNameTokenLexerSurroundedWithWhitespaces();
			Assert::AreEqual(12, token.End);
		}

		TEST_METHOD(Lex_NameTokenWithWhitespaces_HasNameKind) {
			auto token = GetSingleNameTokenLexerSurroundedWithWhitespaces();
			Assert::IsTrue(TokenKind::NAME == token.Kind);
		}

		TEST_METHOD(Lex_NameTokenWithWhitespaces_HasCorrectStart) {
			auto token = GetSingleNameTokenLexerSurroundedWithWhitespaces();
			Assert::AreEqual(9, token.Start);
		}

		TEST_METHOD(Lex_NameTokenWithWhitespaces_HasCorrectValue) {
			auto token = GetSingleNameTokenLexerSurroundedWithWhitespaces();
			Assert::AreEqual(std::string("foo"), token.Value);
		}


		// Unsupported usage case
		/*TEST_METHOD(Lex_NullInput_ReturnsEOF) {
			auto token = Lexer().Lex(Source(nullptr));

			Assert::AreEqual(TokenKind::EOF_, token.Kind);
		}*/


		TEST_METHOD(Lex_PipePunctuation_HasCorrectEnd) {
			auto token = GetPipePunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_PipePunctuation_HasCorrectKind) {
			auto token = GetPipePunctuationTokenLexer();
			Assert::IsTrue(TokenKind::PIPE == token.Kind);
		}

		TEST_METHOD(Lex_PipePunctuation_HasCorrectStart) {
			auto token = GetPipePunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_PipePunctuation_HasCorrectValue) {
			auto token = GetPipePunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_QuoteString_HasCorrectEnd) {
			auto token = GetQuoteStringTokenLexer();
			Assert::AreEqual(10, token.End);
		}

		TEST_METHOD(Lex_QuoteString_HasCorrectKind) {
			auto token = GetQuoteStringTokenLexer();
			Assert::IsTrue(TokenKind::STRING == token.Kind);
		}

		TEST_METHOD(Lex_QuoteString_HasCorrectStart) {
			auto token = GetQuoteStringTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_QuoteString_HasCorrectValue) {
			auto token = GetQuoteStringTokenLexer();
			Assert::AreEqual(std::string("quote \""), token.Value);
		}


		TEST_METHOD(Lex_RightBracePunctuation_HasCorrectEnd) {
			auto token = GetRightBracePunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_RightBracePunctuation_HasCorrectKind) {
			auto token = GetRightBracePunctuationTokenLexer();
			Assert::IsTrue(TokenKind::BRACE_R == token.Kind);
		}

		TEST_METHOD(Lex_RightBracePunctuation_HasCorrectStart) {
			auto token = GetRightBracePunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_RightBracePunctuation_HasCorrectValue) {
			auto token = GetRightBracePunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_RightBracketPunctuation_HasCorrectEnd) {
			auto token = GetRightBracketPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_RightBracketPunctuation_HasCorrectKind) {
			auto token = GetRightBracketPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::BRACKET_R == token.Kind);
		}

		TEST_METHOD(Lex_RightBracketPunctuation_HasCorrectStart) {
			auto token = GetRightBracketPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_RightBracketPunctuation_HasCorrectValue) {
			auto token = GetRightBracketPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}


		TEST_METHOD(Lex_RightParenthesisPunctuation_HasCorrectEnd) {
			auto token = GetRightParenthesisPunctuationTokenLexer();
			Assert::AreEqual(1, token.End);
		}

		TEST_METHOD(Lex_RightParenthesisPunctuation_HasCorrectKind) {
			auto token = GetRightParenthesisPunctuationTokenLexer();
			Assert::IsTrue(TokenKind::PAREN_R == token.Kind);
		}

		TEST_METHOD(Lex_RightParenthesisPunctuation_HasCorrectStart) {
			auto token = GetRightParenthesisPunctuationTokenLexer();
			Assert::AreEqual(0, token.Start);
		}

		TEST_METHOD(Lex_RightParenthesisPunctuation_HasCorrectValue) {
			auto token = GetRightParenthesisPunctuationTokenLexer();
			Assert::AreEqual((size_t)0, token.Value.length());
		}



	private:
		static Token GetATPunctuationTokenLexer() {
			return Lexer().Lex(Source("@"));
		}

		static Token GetBangPunctuationTokenLexer() {
			return Lexer().Lex(Source("!"));
		}

		static Token GetColonPunctuationTokenLexer() {
			return Lexer().Lex(Source(":"));
		}

		static Token GetDollarPunctuationTokenLexer() {
			return Lexer().Lex(Source("$"));
		}

		static Token GetEqualsPunctuationTokenLexer() {
			return Lexer().Lex(Source("="));
		}

		static Token GetEscapedStringPunctuationTokenLexer() {
			return Lexer().Lex(Source("\"escaped \\n\\r\\b\\t\\f\""));
		}

		static Token GetLeftBracePunctuationTokenLexer() {
			return Lexer().Lex(Source("{"));
		}

		static Token GetLeftBracketPunctuationTokenLexer() {
			return Lexer().Lex(Source("["));
		}

		static Token GetLeftParenthesisPunctuationTokenLexer() {
			return Lexer().Lex(Source("("));
		}

		static Token GetMultipleDecimalsIntTokenLexer() {
			return Lexer().Lex(Source("123"));
		}

		static Token GetSingleNameTokenLexerWithComments() {
			return Lexer().Lex(Source("\n#comment\nfoo#comment"));
		}

		static Token GetSingleNameTokenLexerSurroundedWithWhitespaces() {
			return Lexer().Lex(Source("\n        foo\n\n    "));
		}

		static Token GetPipePunctuationTokenLexer() {
			return Lexer().Lex(Source("|"));
		}

		static Token GetQuoteStringTokenLexer() {
			return Lexer().Lex(Source("\"quote \\\"\""));
		}

		static Token GetRightBracePunctuationTokenLexer() {
			return Lexer().Lex(Source("}"));
		}

		static Token GetRightBracketPunctuationTokenLexer() {
			return Lexer().Lex(Source("]"));
		}

		static Token GetRightParenthesisPunctuationTokenLexer() {
			return Lexer().Lex(Source(")"));
		}

	};
}
