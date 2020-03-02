#pragma once

#include <stack>
#include <functional>
#include <GraphQLParser/Source.h>
#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/Token.h>
#include <GraphQLParser/AST/Enums.h>
#include <GraphQLParser/AST/GraphQLDocument.h>
#include <GraphQLParser/AST/GraphQLFieldSelection.h>
#include <GraphQLParser/AST/GraphQLName.h>
#include <GraphQLParser/AST/GraphQLSelectionSet.h>

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

		/*NICE*/AST::GraphQLComment GetComment();

	private:
		/*NICE*/void Advance();

		/*NICE*/AST::GraphQLDocument CreateDocument(int start, std::vector<AST::ASTNode> definitions);
		AST::ASTNode CreateOperationDefinition(int start);
		AST::ASTNode CreateOperationDefinition(int start, AST::OperationType operation, AST::GraphQLName name);

		/*NICE*/void Expect(TokenKind kind);

		/*NICE*/AST::GraphQLLocation GetLocation(int start);
		/*NICE*/AST::GraphQLName GetName();

		/*NICE*/std::vector<AST::ASTNode> ManyNode(TokenKind open, std::vector<AST::ASTNode>(*next)(ParserContext*), TokenKind close);
		/*NICE*/std::vector<AST::GraphQLArgument> ManyArgument(TokenKind open, std::vector<AST::GraphQLArgument>(*next)(ParserContext*), TokenKind close);
		/*NICE*/std::vector<AST::GraphQLVariableDefinition> ManyVariableDefinition(TokenKind open, std::vector<AST::GraphQLVariableDefinition>(*next)(ParserContext*), TokenKind close);

		/*NICE*/std::vector<AST::GraphQLArgument> ParseArguments();
		/*NICE*/AST::GraphQLArgument ParseArgument();
		/*NICE*/AST::GraphQLValue ExpectColonAndParseValueLiteral(bool is_content);
		AST::GraphQLValue ParseValueLiteral(bool is_constant);

		/*NICE*/AST::GraphQLName ParseName();
		/*NICE*/AST::GraphQLComment ParseComment();
		/*NICE*/std::vector<AST::ASTNode> ParseDefinitionsIfNotEOF();
		AST::ASTNode ParseDefinition();
		AST::ASTNode ParseOperationDefinition();
		/*NICE*/AST::OperationType ParseOperationType();
		/*NICE*/AST::GraphQLDocument ParseDocument();
		/*NICE*/AST::ASTNode ParseSelection();
		/*NICE*/AST::GraphQLSelectionSet ParseSelectionSet();

		AST::ASTNode ParseFragment();
		AST::ASTNode CreateGraphQLFragmentSpread(int start);
		AST::ASTNode CreateInlineFragment(int start);

		/*NICE*/AST::ASTNode ParseFieldSelection();
		AST::GraphQLFieldSelection CreateFieldSelection(int start, AST::GraphQLName name, AST::GraphQLName alias, AST::GraphQLComment comment);

		std::vector<AST::GraphQLVariableDefinition> ParseVariableDefinitions();

		/*NICE*/std::vector<AST::GraphQLDirective> ParseDirectives();
		/*NICE*/AST::GraphQLDirective ParseDirective();


		/*NICE*/bool Peek(TokenKind kind);
		/*NICE*/bool Skip(TokenKind kind);


	};
}
