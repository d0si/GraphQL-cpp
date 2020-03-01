#pragma once

#include <stack>
#include <GraphQLParser/Source.h>
#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/Token.h>
#include <GraphQLParser/AST/Enums.h>
#include <GraphQLParser/AST/GraphQLDocument.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	class ParserContext {
	private:
		Lexer lexer;
		Source source;
		std::stack<AST::GraphQLComment> comments;
		Token current_token;

	public:
		ParserContext(Source source, Lexer lexer);

		/*NICE*/AST::GraphQLDocument Parse();

	private:
		/*NICE*/void Advance();

		/*NICE*/AST::GraphQLDocument CreateDocument(int start, std::vector<AST::ASTNode> definitions);
		AST::ASTNode CreateOperationDefinition(int start, AST::OperationType operation, AST::GraphQLName name);

		/*NICE*/void Expect(TokenKind kind);

		/*NICE*/AST::GraphQLLocation GetLocation(int start);
		/*NICE*/AST::GraphQLName GetName();

		/*NICE*/AST::GraphQLName ParseName();
		/*NICE*/AST::GraphQLComment ParseComment();
		/*NICE*/std::vector<AST::ASTNode> ParseDefinitionsIfNotEOF();
		AST::ASTNode ParseDefinition();
		AST::ASTNode ParseOperationDefinition();
		/*NICE*/AST::OperationType ParseOperationType();
		/*NICE*/AST::GraphQLDocument ParseDocument();



		/*NICE*/bool Peek(TokenKind kind);
		/*NICE*/bool Skip(TokenKind kind);


	};
}
