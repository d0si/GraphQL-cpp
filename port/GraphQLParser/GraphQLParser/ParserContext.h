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
		std::stack<std::shared_ptr<AST::GraphQLComment>> comments;
		Token current_token;

	public:
		ParserContext(const Source& source, Lexer lexer);

		AST::GraphQLDocument Parse();

		std::shared_ptr<AST::GraphQLComment> GetComment();

	private:
		void Advance();

		AST::GraphQLDocument CreateDocument(int start, std::vector<std::shared_ptr<AST::ASTNode>> definitions) const;
		std::shared_ptr<AST::ASTNode> CreateOperationDefinition(int start);
		std::shared_ptr<AST::ASTNode> CreateOperationDefinition(int start, AST::OperationType operation, std::shared_ptr<AST::GraphQLName> name);

		void Expect(TokenKind kind);
		void ExpectKeyword(const std::string& keyword);

		AST::GraphQLLocation GetLocation(int start) const;
		std::shared_ptr<AST::GraphQLName> GetName();

		std::vector<AST::ASTNode> ManyNode(TokenKind open, AST::ASTNode(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLArgument> ManyArgument(TokenKind open, AST::GraphQLArgument(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLVariableDefinition> ManyVariableDefinition(TokenKind open, AST::GraphQLVariableDefinition(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLOperationTypeDefinition> ManyOperationTypeDefinition(TokenKind open, AST::GraphQLOperationTypeDefinition(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLInputValueDefinition> ManyInputValueDefinition(TokenKind open, AST::GraphQLInputValueDefinition(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLEnumValueDefinition> ManyEnumValueDefinition(TokenKind open, AST::GraphQLEnumValueDefinition(*next)(ParserContext*), TokenKind close);

		std::vector<std::shared_ptr<AST::GraphQLValue>> Any(TokenKind open, std::shared_ptr<AST::GraphQLValue> (*next)(ParserContext*, bool is_constant), bool is_constant, TokenKind close);
		std::vector<AST::GraphQLFieldDefinition> Any(TokenKind open, AST::GraphQLFieldDefinition(*next)(ParserContext*), TokenKind close);
		std::vector<AST::GraphQLInputValueDefinition> Any(TokenKind open, AST::GraphQLInputValueDefinition(*next)(ParserContext*), TokenKind close);

		std::vector<AST::GraphQLArgument> ParseArguments();
		AST::GraphQLArgument ParseArgument();
		std::shared_ptr<AST::GraphQLValue> ExpectColonAndParseValueLiteral(bool is_content);
		std::shared_ptr<AST::GraphQLValue> ParseValueLiteral(bool is_constant);

		std::shared_ptr<AST::GraphQLName> ParseName();
		std::shared_ptr<AST::GraphQLComment> ParseComment();
		std::vector<std::shared_ptr<AST::ASTNode>> ParseDefinitionsIfNotEOF();
		std::shared_ptr<AST::ASTNode> ParseDefinition();
		std::shared_ptr<AST::ASTNode> ParseOperationDefinition();
		AST::OperationType ParseOperationType();
		AST::GraphQLDocument ParseDocument();
		AST::ASTNode ParseSelection();
		AST::GraphQLSelectionSet ParseSelectionSet();

		AST::ASTNode ParseFragment();
		AST::ASTNode CreateGraphQLFragmentSpread(int start);
		AST::ASTNode CreateInlineFragment(int start);
		std::shared_ptr<AST::GraphQLName> ParseFragmentName();
		AST::GraphQLNamedType GetTypeCondition();
		AST::GraphQLNamedType ParseNamedType();

		AST::ASTNode ParseFieldSelection();
		AST::GraphQLFieldSelection CreateFieldSelection(int start, std::shared_ptr<AST::GraphQLName> name, std::shared_ptr<AST::GraphQLName> alias, std::shared_ptr<AST::GraphQLComment> comment);

		std::vector<AST::GraphQLVariableDefinition> ParseVariableDefinitions();
		AST::GraphQLVariableDefinition ParseVariableDefinition();

		std::vector<AST::GraphQLDirective> ParseDirectives();
		AST::GraphQLDirective ParseDirective();

		std::shared_ptr<AST::GraphQLValue> ParseList(bool is_constant);
		std::shared_ptr<AST::GraphQLValue> ParseObject(bool is_constant);
		std::shared_ptr<AST::GraphQLValue> ParseInt(bool is_constant);
		std::shared_ptr<AST::GraphQLValue> ParseFloat(bool is_constant);
		std::shared_ptr<AST::GraphQLValue> ParseString(bool is_constant);
		std::shared_ptr<AST::GraphQLValue> ParseNameValue(bool is_constant);
		std::shared_ptr<AST::GraphQLVariable> ParseVariable();

		std::shared_ptr<AST::GraphQLValue> ParseConstantValue();
		std::shared_ptr<AST::GraphQLValue> ParseValueValue();

		std::vector<AST::GraphQLObjectField> ParseObjectFields(bool is_constant);
		AST::GraphQLObjectField ParseObjectField(bool is_constant);

		std::shared_ptr<AST::GraphQLValue> ParseBooleanValue(Token token);
		std::shared_ptr<AST::GraphQLValue> ParseNullValue(Token token);
		std::shared_ptr<AST::GraphQLValue> ParseEnumValue(Token token);

		AST::GraphQLType AdvanceThroughColonAndParseType();
		AST::GraphQLType ParseType();
		std::shared_ptr<AST::GraphQLValue> SkipEqualsAndParseValueLiteral();

		std::shared_ptr<AST::ASTNode> ParseNamedDefinition();
		std::shared_ptr<AST::GraphQLFragmentDefinition> ParseFragmentDefinition();
		AST::GraphQLNamedType ExpectOnKeywordAndParseNamedType();

		std::shared_ptr<AST::GraphQLSchemaDefinition> ParseSchemaDefinition();
		AST::GraphQLOperationTypeDefinition ParseOperationTypeDefinition();

		std::shared_ptr<AST::GraphQLScalarTypeDefinition> ParseScalarTypeDefinition();

		std::shared_ptr<AST::GraphQLObjectTypeDefinition> ParseObjectTypeDefinition();
		std::vector<AST::GraphQLNamedType> ParseImplementsInterfaces();
		AST::GraphQLFieldDefinition ParseFieldDefinition();
		std::vector<AST::GraphQLInputValueDefinition> ParseArgumentDefs();
		AST::GraphQLInputValueDefinition ParseInputValueDef();
		std::shared_ptr<AST::GraphQLValue> GetDefaultConstantValue();

		std::shared_ptr<AST::GraphQLInterfaceTypeDefinition> ParseInterfaceTypeDefinition();

		std::shared_ptr<AST::GraphQLUnionTypeDefinition> ParseUnionTypeDefinition();
		std::vector<AST::GraphQLNamedType> ParseUnionMembers();

		std::shared_ptr<AST::GraphQLEnumTypeDefinition> ParseEnumTypeDefinition();
		AST::GraphQLEnumValueDefinition ParseEnumValueDefinition();

		std::shared_ptr<AST::GraphQLInputObjectTypeDefinition> ParseInputObjectTypeDefinition();

		std::shared_ptr<AST::GraphQLTypeExtensionDefinition> ParseTypeExtensionDefinition();

		std::shared_ptr<AST::GraphQLDirectiveDefinition> ParseDirectiveDefinition();
		bool ParseRepeatable();
		std::vector<std::shared_ptr<AST::GraphQLName>> ParseDirectiveLocations();

		bool Peek(TokenKind kind);
		bool Skip(TokenKind kind);
	};
}
