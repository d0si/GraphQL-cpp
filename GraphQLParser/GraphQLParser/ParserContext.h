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
#include <GraphQLParser/AST/GraphQLVariableDefinition.h>
#include <GraphQLParser/AST/GraphQLNamedType.h>
#include <GraphQLParser/AST/GraphQLValue.h>
#include <GraphQLParser/AST/GraphQLObjectField.h>

namespace GraphQLParser {
	class ParserContext {
	private:
		Lexer lexer;
		Source source;
		std::stack<AST::GraphQLComment> comments;
		Token current_token;

	public:
		ParserContext(Source source, Lexer lexer);

		/*DONE*/AST::GraphQLDocument Parse();

		/*DONE*/AST::GraphQLComment GetComment();

	private:
		/*DONE*/void Advance();

		/*DONE*/AST::GraphQLDocument CreateDocument(int start, std::vector<AST::ASTNode> definitions);
		AST::ASTNode CreateOperationDefinition(int start);
		AST::ASTNode CreateOperationDefinition(int start, AST::OperationType operation, AST::GraphQLName name);

		/*DONE*/void Expect(TokenKind kind);

		/*DONE*/AST::GraphQLLocation GetLocation(int start);
		/*DONE*/AST::GraphQLName GetName();

		/*DONE*/std::vector<AST::ASTNode> ManyNode(TokenKind open, AST::ASTNode(*next)(ParserContext*), TokenKind close);
		/*DONE*/std::vector<AST::GraphQLArgument> ManyArgument(TokenKind open, AST::GraphQLArgument(*next)(ParserContext*), TokenKind close);
		/*DONE*/std::vector<AST::GraphQLVariableDefinition> ManyVariableDefinition(TokenKind open, AST::GraphQLVariableDefinition(*next)(ParserContext*), TokenKind close);

		/*DONE*/std::vector<AST::GraphQLValue> Any(TokenKind open, AST::GraphQLValue(*next)(ParserContext*, bool is_constant), bool is_constant, TokenKind close);

		/*DONE*/std::vector<AST::GraphQLArgument> ParseArguments();
		/*DONE*/AST::GraphQLArgument ParseArgument();
		/*DONE*/AST::GraphQLValue ExpectColonAndParseValueLiteral(bool is_content);
		AST::GraphQLValue ParseValueLiteral(bool is_constant);

		/*DONE*/AST::GraphQLName ParseName();
		/*DONE*/AST::GraphQLComment ParseComment();
		/*DONE*/std::vector<AST::ASTNode> ParseDefinitionsIfNotEOF();
		AST::ASTNode ParseDefinition();
		/*DONE*/AST::ASTNode ParseOperationDefinition();
		/*DONE*/AST::OperationType ParseOperationType();
		/*DONE*/AST::GraphQLDocument ParseDocument();
		/*DONE*/AST::ASTNode ParseSelection();
		/*DONE*/AST::GraphQLSelectionSet ParseSelectionSet();

		/*DONE*/AST::ASTNode ParseFragment();
		/*DONE*/AST::ASTNode CreateGraphQLFragmentSpread(int start);
		/*DONE*/AST::ASTNode CreateInlineFragment(int start);
		/*DONE*/AST::GraphQLName ParseFragmentName();
		/*DONE*/AST::GraphQLNamedType GetTypeCondition();
		/*DONE*/AST::GraphQLNamedType ParseNamedType();

		/*DONE*/AST::ASTNode ParseFieldSelection();
		/*DONE*/AST::GraphQLFieldSelection CreateFieldSelection(int start, AST::GraphQLName name, AST::GraphQLName alias, AST::GraphQLComment comment);

		/*DONE*/std::vector<AST::GraphQLVariableDefinition> ParseVariableDefinitions();
		AST::GraphQLVariableDefinition ParseVariableDefinition();

		/*DONE*/std::vector<AST::GraphQLDirective> ParseDirectives();
		/*DONE*/AST::GraphQLDirective ParseDirective();

		/*DONE*/AST::GraphQLValue ParseList(bool is_constant);
		/*DONE*/AST::GraphQLValue ParseObject(bool is_constant);
		/*DONE*/AST::GraphQLValue ParseInt(bool is_constant);
		/*DONE*/AST::GraphQLValue ParseFloat(bool is_constant);
		/*DONE*/AST::GraphQLValue ParseString(bool is_constant);
		/*DONE*/AST::GraphQLValue ParseNameValue(bool is_constant);
		/*DONE*/AST::GraphQLVariable ParseVariable();

		/*DONE*/AST::GraphQLValue ParseConstantValue();
		/*DONE*/AST::GraphQLValue ParseValueValue();

		/*DONE*/std::vector<AST::GraphQLObjectField> ParseObjectFields(bool is_constant);
		/*DONE*/AST::GraphQLObjectField ParseObjectField(bool is_constant);

		/*DONE*/AST::GraphQLValue ParseBooleanValue(Token token);
		/*DONE*/AST::GraphQLValue ParseNullValue(Token token);
		/*DONE*/AST::GraphQLValue ParseEnumValue(Token token);

		/*DONE*/bool Peek(TokenKind kind);
		/*DONE*/bool Skip(TokenKind kind);


	};
}
