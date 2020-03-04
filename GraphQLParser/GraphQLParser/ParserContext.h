#pragma once

#include <stack>
#include <functional>
#include <GraphQLParser/Source.h>
#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/Token.h>
#include <GraphQLParser/AST/Enums.h>
#include <GraphQLParser/AST/GraphQLComment.h>
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
		std::stack<AST::GraphQLComment*> comments;
		Token current_token;

	public:
		ParserContext(Source source, Lexer lexer);

		AST::GraphQLDocument Parse();

		AST::GraphQLComment* GetComment();

	private:
		void Advance();

		AST::GraphQLDocument CreateDocument(int start, std::vector<AST::ASTNode*> definitions);
		AST::ASTNode* CreateOperationDefinition(int start);
		AST::ASTNode* CreateOperationDefinition(int start, AST::OperationType operation, AST::GraphQLName name);

		void Expect(TokenKind kind);
		void ExpectKeyword(std::string keyword);

		AST::GraphQLLocation GetLocation(int start);
		AST::GraphQLName GetName();

		std::vector<AST::ASTNode> ManyNode(TokenKind open, AST::ASTNode(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLArgument> ManyArgument(TokenKind open, AST::GraphQLArgument(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLVariableDefinition> ManyVariableDefinition(TokenKind open, AST::GraphQLVariableDefinition(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLOperationTypeDefinition> ManyOperationTypeDefinition(TokenKind open, AST::GraphQLOperationTypeDefinition(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLInputValueDefinition> ManyInputValueDefinition(TokenKind open, AST::GraphQLInputValueDefinition(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLEnumValueDefinition> ManyEnumValueDefinition(TokenKind open, AST::GraphQLEnumValueDefinition(*next)(ParserContext*), TokenKind close);

		std::vector<AST::GraphQLValue> Any(TokenKind open, AST::GraphQLValue(*next)(ParserContext*, bool is_constant), bool is_constant, TokenKind close);
		std::vector<AST::GraphQLFieldDefinition> Any(TokenKind open, AST::GraphQLFieldDefinition(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLInputValueDefinition> Any(TokenKind open, AST::GraphQLInputValueDefinition(*next)(ParserContext*), TokenKind close);

		std::vector<AST::GraphQLArgument> ParseArguments();
		AST::GraphQLArgument ParseArgument();
		AST::GraphQLValue ExpectColonAndParseValueLiteral(bool is_content);
		AST::GraphQLValue ParseValueLiteral(bool is_constant);

		AST::GraphQLName ParseName();
		AST::GraphQLComment* ParseComment();
		std::vector<AST::ASTNode*> ParseDefinitionsIfNotEOF();
		AST::ASTNode* ParseDefinition();
		AST::ASTNode* ParseOperationDefinition();
		AST::OperationType ParseOperationType();
		AST::GraphQLDocument ParseDocument();
		AST::ASTNode ParseSelection();
		AST::GraphQLSelectionSet ParseSelectionSet();

		AST::ASTNode ParseFragment();
		AST::ASTNode CreateGraphQLFragmentSpread(int start);
		AST::ASTNode CreateInlineFragment(int start);
		AST::GraphQLName ParseFragmentName();
		AST::GraphQLNamedType GetTypeCondition();
		AST::GraphQLNamedType ParseNamedType();

		AST::ASTNode ParseFieldSelection();
		AST::GraphQLFieldSelection CreateFieldSelection(int start, AST::GraphQLName name, AST::GraphQLName alias, AST::GraphQLComment* comment);

		std::vector<AST::GraphQLVariableDefinition> ParseVariableDefinitions();
		AST::GraphQLVariableDefinition ParseVariableDefinition();

		std::vector<AST::GraphQLDirective> ParseDirectives();
		AST::GraphQLDirective ParseDirective();

		AST::GraphQLValue ParseList(bool is_constant);
		AST::GraphQLValue ParseObject(bool is_constant);
		AST::GraphQLValue ParseInt(bool is_constant);
		AST::GraphQLValue ParseFloat(bool is_constant);
		AST::GraphQLValue ParseString(bool is_constant);
		AST::GraphQLValue ParseNameValue(bool is_constant);
		AST::GraphQLVariable ParseVariable();

		AST::GraphQLValue ParseConstantValue();
		AST::GraphQLValue ParseValueValue();

		std::vector<AST::GraphQLObjectField> ParseObjectFields(bool is_constant);
		AST::GraphQLObjectField ParseObjectField(bool is_constant);

		AST::GraphQLValue ParseBooleanValue(Token token);
		AST::GraphQLValue ParseNullValue(Token token);
		AST::GraphQLValue ParseEnumValue(Token token);

		AST::GraphQLType AdvanceThroughColonAndParseType();
		AST::GraphQLType ParseType();
		AST::GraphQLValue SkipEqualsAndParseValueLiteral();

		AST::ASTNode* ParseNamedDefinition();
		AST::GraphQLFragmentDefinition* ParseFragmentDefinition();
		AST::GraphQLNamedType ExpectOnKeywordAndParseNamedType();

		AST::GraphQLSchemaDefinition* ParseSchemaDefinition();
		AST::GraphQLOperationTypeDefinition ParseOperationTypeDefinition();

		AST::GraphQLScalarTypeDefinition* ParseScalarTypeDefinition();

		AST::GraphQLObjectTypeDefinition* ParseObjectTypeDefinition();
		std::vector<AST::GraphQLNamedType> ParseImplementsInterfaces();
		AST::GraphQLFieldDefinition ParseFieldDefinition();
		std::vector<AST::GraphQLInputValueDefinition> ParseArgumentDefs();
		AST::GraphQLInputValueDefinition ParseInputValueDef();
		AST::GraphQLValue GetDefaultConstantValue();

		AST::GraphQLInterfaceTypeDefinition* ParseInterfaceTypeDefinition();

		AST::GraphQLUnionTypeDefinition* ParseUnionTypeDefinition();
		std::vector<AST::GraphQLNamedType> ParseUnionMembers();

		AST::GraphQLEnumTypeDefinition* ParseEnumTypeDefinition();
		AST::GraphQLEnumValueDefinition ParseEnumValueDefinition();

		AST::GraphQLInputObjectTypeDefinition* ParseInputObjectTypeDefinition();

		AST::GraphQLTypeExtensionDefinition* ParseTypeExtensionDefinition();

		AST::GraphQLDirectiveDefinition* ParseDirectiveDefinition();
		bool ParseRepeatable();
		std::vector<AST::GraphQLName> ParseDirectiveLocations();

		bool Peek(TokenKind kind);
		bool Skip(TokenKind kind);
	};
}
