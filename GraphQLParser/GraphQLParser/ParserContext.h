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
#include <GraphQLParser/AST/GraphQLFragmentDefinition.h>
#include <GraphQLParser/AST/GraphQLSchemaDefinition.h>
#include <GraphQLParser/AST/GraphQLScalarTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLObjectTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLInterfaceTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLUnionTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLEnumTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLInputObjectTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLTypeExtensionDefinition.h>
#include <GraphQLParser/AST/GraphQLDirectiveDefinition.h>

namespace GraphQLParser {
	class ParserContext {
	private:
		Lexer lexer;
		Source source;
		std::stack<AST::GraphQLComment> comments;
		Token current_token;

	public:
		/*DONE*/ParserContext(Source source, Lexer lexer);

		/*DONE*/AST::GraphQLDocument Parse();

		/*DONE*/AST::GraphQLComment GetComment();

	private:
		/*DONE*/void Advance();

		/*DONE*/AST::GraphQLDocument CreateDocument(int start, std::vector<AST::ASTNode> definitions);
		/*DONE*/AST::ASTNode CreateOperationDefinition(int start);
		/*DONE*/AST::ASTNode CreateOperationDefinition(int start, AST::OperationType operation, AST::GraphQLName name);

		/*DONE*/void Expect(TokenKind kind);
		/*DONE*/void ExpectKeyword(std::string keyword);

		/*DONE*/AST::GraphQLLocation GetLocation(int start);
		/*DONE*/AST::GraphQLName GetName();

		/*DONE*/std::vector<AST::ASTNode> ManyNode(TokenKind open, AST::ASTNode(*next)(ParserContext*), TokenKind close);
		/*DONE*/std::vector<AST::GraphQLArgument> ManyArgument(TokenKind open, AST::GraphQLArgument(*next)(ParserContext*), TokenKind close);
		/*DONE*/std::vector<AST::GraphQLVariableDefinition> ManyVariableDefinition(TokenKind open, AST::GraphQLVariableDefinition(*next)(ParserContext*), TokenKind close);
		/*DONE*/std::vector<AST::GraphQLOperationTypeDefinition> ManyOperationTypeDefinition(TokenKind open, AST::GraphQLOperationTypeDefinition(*next)(ParserContext*), TokenKind close);
		/*DONE*/std::vector<AST::GraphQLInputValueDefinition> ManyInputValueDefinition(TokenKind open, AST::GraphQLInputValueDefinition(*next)(ParserContext*), TokenKind close);
		/*DONE*/std::vector<AST::GraphQLEnumValueDefinition> ManyEnumValueDefinition(TokenKind open, AST::GraphQLEnumValueDefinition(*next)(ParserContext*), TokenKind close);

		/*DONE*/std::vector<AST::GraphQLValue> Any(TokenKind open, AST::GraphQLValue(*next)(ParserContext*, bool is_constant), bool is_constant, TokenKind close);
		/*DONE*/std::vector<AST::GraphQLFieldDefinition> Any(TokenKind open, AST::GraphQLFieldDefinition(*next)(ParserContext*), TokenKind close);
		/*DONE*/std::vector<AST::GraphQLInputValueDefinition> Any(TokenKind open, AST::GraphQLInputValueDefinition(*next)(ParserContext*), TokenKind close);

		/*DONE*/std::vector<AST::GraphQLArgument> ParseArguments();
		/*DONE*/AST::GraphQLArgument ParseArgument();
		/*DONE*/AST::GraphQLValue ExpectColonAndParseValueLiteral(bool is_content);
		/*DONE*/AST::GraphQLValue ParseValueLiteral(bool is_constant);

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

		/*DONE*/AST::GraphQLType AdvanceThroughColonAndParseType();
		/*DONE*/AST::GraphQLType ParseType();

		/*DONE*/AST::ASTNode ParseNamedDefinition();
		/*DONE*/AST::GraphQLFragmentDefinition ParseFragmentDefinition();
		/*DONE*/AST::GraphQLNamedType ExpectOnKeywordAndParseNamedType();

		/*DONE*/AST::GraphQLSchemaDefinition ParseSchemaDefinition();
		/*DONE*/AST::GraphQLOperationTypeDefinition ParseOperationTypeDefinition();

		/*DONE*/AST::GraphQLScalarTypeDefinition ParseScalarTypeDefinition();

		/*DONE*/AST::GraphQLObjectTypeDefinition ParseObjectTypeDefinition();
		/*DONE*/std::vector<AST::GraphQLNamedType> ParseImplementsInterfaces();
		/*DONE*/AST::GraphQLFieldDefinition ParseFieldDefinition();
		/*DONE*/std::vector<AST::GraphQLInputValueDefinition> ParseArgumentDefs();
		/*DONE*/AST::GraphQLInputValueDefinition ParseInputValueDef();
		/*DONE*/AST::GraphQLValue GetDefaultConstantValue();

		/*DONE*/AST::GraphQLInterfaceTypeDefinition ParseInterfaceTypeDefinition();

		/*DONE*/AST::GraphQLUnionTypeDefinition ParseUnionTypeDefinition();
		/*DONE*/std::vector<AST::GraphQLNamedType> ParseUnionMembers();

		/*DONE*/AST::GraphQLEnumTypeDefinition ParseEnumTypeDefinition();
		/*DONE*/AST::GraphQLEnumValueDefinition ParseEnumValueDefinition();

		/*DONE*/AST::GraphQLInputObjectTypeDefinition ParseInputObjectTypeDefinition();

		/*DONE*/AST::GraphQLTypeExtensionDefinition ParseTypeExtensionDefinition();

		/*DONE*/AST::GraphQLDirectiveDefinition ParseDirectiveDefinition();
		/*DONE*/bool ParseRepeatable();
		/*DONE*/std::vector<AST::GraphQLName> ParseDirectiveLocations();

		/*DONE*/bool Peek(TokenKind kind);
		/*DONE*/bool Skip(TokenKind kind);
	};
}
