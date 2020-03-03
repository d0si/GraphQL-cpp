#include <GraphQLParser/ParserContext.h>
#include <GraphQLParser/Exceptions/GraphQLSyntaxErrorException.h>
#include <GraphQLParser/AST/GraphQLOperationDefinition.h>
#include <GraphQLParser/AST/GraphQLFragmentSpread.h>
#include <GraphQLParser/AST/GraphQLInlineFragment.h>
#include <GraphQLParser/AST/GraphQLListValue.h>
#include <GraphQLParser/AST/GraphQLObjectValue.h>
#include <GraphQLParser/AST/GraphQLScalarValue.h>
#include <GraphQLParser/AST/GraphQLListType.h>
#include <GraphQLParser/AST/GraphQLNonNullType.h>

namespace GraphQLParser {
	ParserContext::ParserContext(Source source, Lexer lexer) : source(source), lexer(lexer), current_token(lexer.Lex(source)) {

	}

	AST::GraphQLDocument ParserContext::Parse() {
		return ParseDocument();
	}

	AST::GraphQLComment ParserContext::GetComment() {
		AST::GraphQLComment comment;

		if (!comments.empty()) {
			comment = comments.top();
			comments.pop();
		}

		return comment;
	}

	void ParserContext::Advance() {
		current_token = lexer.Lex(source, current_token.End);
	}

	AST::GraphQLDocument ParserContext::CreateDocument(int start, std::vector<AST::ASTNode> definitions) {
		AST::GraphQLDocument document;

		document.Location.Start = start;
		document.Location.End = current_token.End;
		document.Definitions = definitions;

		return document;
	}

	AST::ASTNode ParserContext::CreateOperationDefinition(int start) {
		AST::GraphQLComment comment = GetComment();

		AST::GraphQLOperationDefinition definition;
		definition.set_comment(comment);
		definition.Operation = AST::OperationType::Query;
		definition.SelectionSet = ParseSelectionSet();
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::ASTNode ParserContext::CreateOperationDefinition(int start, AST::OperationType operation, AST::GraphQLName name) {
		AST::GraphQLComment comment = GetComment();

		AST::GraphQLOperationDefinition definition;
		definition.set_comment(comment);
		definition.Operation = operation;
		definition.Name = name;
		definition.VariableDefinitions = ParseVariableDefinitions();
		definition.Directives = ParseDirectives();
		definition.SelectionSet = ParseSelectionSet();
		definition.Location = GetLocation(start);

		return definition;
	}

	void ParserContext::Expect(TokenKind kind) {
		if (current_token.Kind == kind) {
			Advance();
		}
		else {
			throw Exceptions::GraphQLSyntaxErrorException(
				"Expected " + Token::get_token_kind_description(kind) + ", found " +
				Token::get_token_kind_description(current_token.Kind), source, current_token.Start);
		}
	}

	void ParserContext::ExpectKeyword(std::string keyword) {
		Token token = current_token;

		if (token.Kind == TokenKind::NAME && keyword == token.Value) {
			Advance();

			return;
		}

		throw Exceptions::GraphQLSyntaxErrorException("Expected \"" + keyword + "\", found Name \"" + token.Value + "\"", source, current_token.Start);
	}

	AST::GraphQLLocation ParserContext::GetLocation(int start) {
		return AST::GraphQLLocation(start, current_token.End);
	}

	AST::GraphQLName ParserContext::GetName() {
		return Peek(TokenKind::NAME) ? ParseName() : AST::GraphQLName();
	}

	std::vector<AST::ASTNode> ParserContext::ManyNode(TokenKind open, AST::ASTNode(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::ASTNode> nodes;

		nodes.push_back(next(this));

		while (!Skip(close)) {
			nodes.push_back(next(this));
		}

		return nodes;
	}

	std::vector<AST::GraphQLArgument> ParserContext::ManyArgument(TokenKind open, AST::GraphQLArgument(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::GraphQLArgument> nodes;

		nodes.push_back(next(this));

		while (!Skip(close)) {
			nodes.push_back(next(this));
		}

		return nodes;
	}

	std::vector<AST::GraphQLVariableDefinition> ParserContext::ManyVariableDefinition(TokenKind open, AST::GraphQLVariableDefinition(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::GraphQLVariableDefinition> nodes;

		nodes.push_back(next(this));

		while (!Skip(close)) {
			nodes.push_back(next(this));
		}

		return nodes;
	}

	std::vector<AST::GraphQLOperationTypeDefinition> ParserContext::ManyOperationTypeDefinition(TokenKind open, AST::GraphQLOperationTypeDefinition(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::GraphQLOperationTypeDefinition> nodes;

		nodes.push_back(next(this));

		while (!Skip(close)) {
			nodes.push_back(next(this));
		}

		return nodes;
	}

	std::vector<AST::GraphQLInputValueDefinition> ParserContext::ManyInputValueDefinition(TokenKind open, AST::GraphQLInputValueDefinition(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::GraphQLInputValueDefinition> nodes;

		nodes.push_back(next(this));

		while (!Skip(close)) {
			nodes.push_back(next(this));
		}

		return nodes;
	}

	std::vector<AST::GraphQLEnumValueDefinition> ParserContext::ManyEnumValueDefinition(TokenKind open, AST::GraphQLEnumValueDefinition(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::GraphQLEnumValueDefinition> nodes;

		nodes.push_back(next(this));

		while (!Skip(close)) {
			nodes.push_back(next(this));
		}

		return nodes;
	}

	std::vector<AST::GraphQLValue> ParserContext::Any(TokenKind open, AST::GraphQLValue(*next)(ParserContext*, bool is_constant), bool is_constant, TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::GraphQLValue> nodes;

		while (!Skip(close)) {
			nodes.push_back(next(this, is_constant));
		}

		return nodes;
	}

	std::vector<AST::GraphQLFieldDefinition> ParserContext::Any(TokenKind open, AST::GraphQLFieldDefinition(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::GraphQLFieldDefinition> nodes;

		while (!Skip(close)) {
			nodes.push_back(next(this));
		}

		return nodes;
	}

	std::vector<AST::GraphQLInputValueDefinition> ParserContext::Any(TokenKind open, AST::GraphQLInputValueDefinition(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<AST::GraphQLInputValueDefinition> nodes;

		while (!Skip(close)) {
			nodes.push_back(next(this));
		}

		return nodes;
	}

	std::vector<AST::GraphQLArgument> ParserContext::ParseArguments() {
		return Peek(TokenKind::PAREN_L) ?
			ManyArgument(TokenKind::PAREN_L, [](ParserContext* context) -> AST::GraphQLArgument {
			return context->ParseArgument();
				},
				TokenKind::PAREN_R)
			: std::vector<AST::GraphQLArgument>();
	}

	AST::GraphQLArgument ParserContext::ParseArgument() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;

		AST::GraphQLArgument argument(ParseName(), ExpectColonAndParseValueLiteral(false));
		argument.set_comment(comment);
		argument.Location = GetLocation(start);

		return argument;
	}

	AST::GraphQLValue ParserContext::ExpectColonAndParseValueLiteral(bool is_constant) {
		Expect(TokenKind::COLON);

		return ParseValueLiteral(is_constant);
	}

	AST::GraphQLValue ParserContext::ParseValueLiteral(bool is_constant) {
		AST::GraphQLValue value;

		switch (current_token.Kind) {
		case TokenKind::BRACKET_L:
			value = ParseList(is_constant);
			break;
		case TokenKind::BRACE_L:
			value = ParseObject(is_constant);
			break;
		case TokenKind::INT:
			value = ParseInt(is_constant);
			break;
		case TokenKind::FLOAT:
			value = ParseFloat(is_constant);
			break;
		case TokenKind::STRING:
			value = ParseString(is_constant);
			break;
		case TokenKind::NAME:
			value = ParseNameValue(is_constant);
			break;
		case TokenKind::DOLLAR:
			if (!is_constant) {
				value = ParseVariable();
			}
			break;
		default:
			throw Exceptions::GraphQLSyntaxErrorException("Unexpected " + current_token.to_string(), source, current_token.Start);
		}

		return value;
	}

	AST::GraphQLName ParserContext::ParseName() {
		int start = current_token.Start;
		std::string value = current_token.Value;

		Expect(TokenKind::NAME);

		AST::GraphQLName name;
		name.Location = GetLocation(start);
		name.Value = value;

		return name;
	}

	AST::GraphQLComment ParserContext::ParseComment() {
		if (!Peek(TokenKind::COMMENT)) {
			return AST::GraphQLComment();
		}

		std::string text;
		int start = current_token.Start;
		int end;

		do {
			text += current_token.Value + "\n";
			end = current_token.End;
			Advance();
		} while (current_token.Kind == TokenKind::COMMENT);

		if (text.length() > 0) {
			text = text.substr(0, text.length() - 2);
		}

		AST::GraphQLComment comment(text);
		comment.Location.Start = start;
		comment.Location.End = end;

		comments.push(comment);

		return comment;
	}

	std::vector<AST::ASTNode> ParserContext::ParseDefinitionsIfNotEOF() {
		std::vector<AST::ASTNode> result;

		if (current_token.Kind != TokenKind::EOF_) {
			do {
				result.push_back(ParseDefinition());
			} while (!Skip(TokenKind::EOF_));
		}

		return result;
	}

	AST::ASTNode ParserContext::ParseDefinition() {
		ParseComment();

		if (Peek(TokenKind::BRACE_L)) {
			return ParseOperationDefinition();
		}

		if (Peek(TokenKind::NAME)) {
			AST::ASTNode definition = ParseNamedDefinition();

			// TODO: Check if definition is null and do not return in such case
			return definition;
		}

		throw Exceptions::GraphQLSyntaxErrorException("Unexpected " + current_token.to_string(), source, current_token.Start);
	}

	AST::ASTNode ParserContext::ParseOperationDefinition() {
		int start = current_token.Start;

		if (Peek(TokenKind::BRACE_L)) {
			return CreateOperationDefinition(start);
		}

		return CreateOperationDefinition(start, ParseOperationType(), GetName());
	}

	AST::OperationType ParserContext::ParseOperationType() {
		Token token = current_token;
		Expect(TokenKind::NAME);

		if (token.Value == "mutation") {
			return AST::OperationType::Mutation;
		}
		else if (token.Value == "subscription") {
			return AST::OperationType::Subscription;
		}
		else {
			return AST::OperationType::Query;
		}
	}

	AST::GraphQLDocument ParserContext::ParseDocument() {
		int start = current_token.Start;
		auto definitions = ParseDefinitionsIfNotEOF();

		return CreateDocument(start, definitions);
	}

	AST::ASTNode ParserContext::ParseSelection() {
		return Peek(TokenKind::SPREAD) ? ParseFragment() : ParseFieldSelection();
	}

	AST::ASTNode ParserContext::ParseFragment() {
		int start = current_token.Start;
		Expect(TokenKind::SPREAD);

		if (Peek(TokenKind::NAME) && !(current_token.Value == "on")) {
			return CreateGraphQLFragmentSpread(start);
		}

		return CreateInlineFragment(start);
	}

	AST::ASTNode ParserContext::CreateGraphQLFragmentSpread(int start) {
		AST::GraphQLFragmentSpread fragment;

		fragment.Name = ParseFragmentName();
		fragment.Directives = ParseDirectives();
		fragment.Location = GetLocation(start);

		return fragment;
	}

	AST::ASTNode ParserContext::CreateInlineFragment(int start) {
		AST::GraphQLInlineFragment fragment;

		fragment.TypeCondition = GetTypeCondition();
		fragment.Directives = ParseDirectives();
		fragment.SelectionSet = ParseSelectionSet();
		fragment.Location = GetLocation(start);

		return fragment;
	}

	AST::GraphQLName ParserContext::ParseFragmentName() {
		if (current_token.Value == "on") {
			throw Exceptions::GraphQLSyntaxErrorException("Unexpected " + current_token.to_string(), source, current_token.Start);
		}

		return ParseName();
	}

	AST::GraphQLNamedType ParserContext::GetTypeCondition() {
		AST::GraphQLNamedType type_condition;

		if (current_token.Value == "on") {
			Advance();
			type_condition = ParseNamedType();
		}

		return type_condition;
	}

	AST::GraphQLNamedType ParserContext::ParseNamedType() {
		int start = current_token.Start;

		AST::GraphQLNamedType type;
		type.Name = ParseName();
		type.Location = GetLocation(start);

		return type;
	}

	AST::ASTNode ParserContext::ParseFieldSelection() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		AST::GraphQLName name_or_alias = ParseName();
		AST::GraphQLName name;
		AST::GraphQLName alias;

		if (Skip(TokenKind::COLON)) {
			name = ParseName();
			alias = name_or_alias;
		}
		else {
			name = name_or_alias;
		}

		return CreateFieldSelection(start, name, alias, comment);
	}

	AST::GraphQLFieldSelection ParserContext::CreateFieldSelection(int start, AST::GraphQLName name, AST::GraphQLName alias, AST::GraphQLComment comment) {
		AST::GraphQLFieldSelection field_selection;

		field_selection.set_comment(comment);
		field_selection.Alias = alias;
		field_selection.Name = name;
		field_selection.Arguments = ParseArguments();
		field_selection.Directives = ParseDirectives();
		field_selection.SelectionSet = Peek(TokenKind::BRACE_L) ? ParseSelectionSet() : AST::GraphQLSelectionSet();
		field_selection.Location = GetLocation(start);

		return field_selection;
	}

	AST::GraphQLSelectionSet ParserContext::ParseSelectionSet() {
		int start = current_token.Start;

		AST::GraphQLSelectionSet selection_set;
		selection_set.Selections = ManyNode(TokenKind::BRACE_L, [](ParserContext* context) -> AST::ASTNode {
			return context->ParseSelection();
			},
			TokenKind::BRACE_R);
		selection_set.Location = GetLocation(start);

		return selection_set;
	}

	std::vector<AST::GraphQLVariableDefinition> ParserContext::ParseVariableDefinitions() {
		return Peek(TokenKind::PAREN_L) ?
			ManyVariableDefinition(TokenKind::PAREN_L, [](ParserContext* context) -> AST::GraphQLVariableDefinition {
			return context->ParseVariableDefinition();
				}, TokenKind::PAREN_R)
			: std::vector<AST::GraphQLVariableDefinition>();
	}

	AST::GraphQLVariableDefinition ParserContext::ParseVariableDefinition() {
		int start = current_token.Start;

		AST::GraphQLVariableDefinition definition;
		definition.Variable = ParseVariable();
		definition.Type = AdvanceThroughColonAndParseType();
		definition.DefaultValue = SkipEqualsAndParseValueLiteral();
		definition.Location = GetLocation(start);

		return definition;
	}

	std::vector<AST::GraphQLDirective> ParserContext::ParseDirectives() {
		std::vector<AST::GraphQLDirective> directives;

		while (Peek(TokenKind::AT)) {
			directives.push_back(ParseDirective());
		}

		return directives;
	}

	AST::GraphQLDirective ParserContext::ParseDirective() {
		int start = current_token.Start;
		Expect(TokenKind::AT);

		AST::GraphQLDirective directive(ParseName(), ParseArguments());
		directive.Location = GetLocation(start);

		return directive;
	}

	AST::GraphQLValue ParserContext::ParseList(bool is_constant) {
		int start = current_token.Start;

		AST::GraphQLListValue list;
		list.Kind = AST::ASTNodeKind::ListValue;
		list.Values = Any(TokenKind::BRACKET_L, [](ParserContext* context, bool is_constant) -> AST::GraphQLValue {
			if (is_constant) {
				return context->ParseConstantValue();
			}
			else {
				return context->ParseValueValue();
			}
			}, is_constant, TokenKind::BRACKET_R);
		list.Location = GetLocation(start);
		list.AstValue = source.Body.substr(start, current_token.End - start - 1);

		return list;
	}

	AST::GraphQLValue ParserContext::ParseObject(bool is_constant) {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;

		AST::GraphQLObjectValue value;
		value.set_comment(comment);
		value.Fields = ParseObjectFields(is_constant);
		value.Location = GetLocation(start);

		return value;
	}

	AST::GraphQLValue ParserContext::ParseInt(bool is_constant) {
		Token token = current_token;
		Advance();

		AST::GraphQLScalarValue value;
		value.Kind = AST::ASTNodeKind::IntValue;
		value.Value = token.Value;
		value.Location = GetLocation(token.Start);

		return value;
	}

	AST::GraphQLValue ParserContext::ParseFloat(bool is_constant) {
		Token token = current_token;

		Advance();

		AST::GraphQLScalarValue value;
		value.Kind = AST::ASTNodeKind::FloatValue;
		value.Value = token.Value;
		value.Location = GetLocation(token.Start);

		return value;
	}

	AST::GraphQLValue ParserContext::ParseString(bool is_constant) {
		Token token = current_token;

		Advance();

		AST::GraphQLScalarValue value;
		value.Kind = AST::ASTNodeKind::StringValue;
		value.Value = token.Value;
		value.Location = GetLocation(token.Start);

		return value;
	}

	AST::GraphQLValue ParserContext::ParseNameValue(bool is_constant) {
		Token token = current_token;

		if (token.Value == "true" || token.Value == "false") {
			return ParseBooleanValue(token);
		}
		else if (token.Value.length() > 0) {
			if (token.Value == "null") {
				return ParseNullValue(token);
			}
			else {
				return ParseEnumValue(token);
			}
		}

		throw Exceptions::GraphQLSyntaxErrorException("Unexpected " + current_token.to_string(), source, current_token.Start);
	}

	AST::GraphQLVariable ParserContext::ParseVariable() {
		int start = current_token.Start;
		Expect(TokenKind::DOLLAR);

		AST::GraphQLVariable variable;
		variable.Name = GetName();
		variable.Location = GetLocation(start);

		return variable;
	}

	AST::GraphQLValue ParserContext::ParseConstantValue() {
		return ParseValueLiteral(true);
	}

	AST::GraphQLValue ParserContext::ParseValueValue() {
		return ParseValueLiteral(false);
	}

	std::vector<AST::GraphQLObjectField> ParserContext::ParseObjectFields(bool is_constant) {
		std::vector<AST::GraphQLObjectField> fields;

		Expect(TokenKind::BRACE_L);
		while (!Skip(TokenKind::BRACE_R)) {
			fields.push_back(ParseObjectField(is_constant));
		}

		return fields;
	}

	AST::GraphQLObjectField ParserContext::ParseObjectField(bool is_constant) {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;

		AST::GraphQLObjectField field;
		field.set_comment(comment);
		field.Name = ParseName();
		field.Value = ExpectColonAndParseValueLiteral(is_constant);
		field.Location = GetLocation(start);

		return field;
	}

	AST::GraphQLValue ParserContext::ParseBooleanValue(Token token) {
		Advance();

		AST::GraphQLScalarValue value;
		value.Kind = AST::ASTNodeKind::BooleanValue;
		value.Value = token.Value;
		value.Location = GetLocation(token.Start);

		return value;
	}

	AST::GraphQLValue ParserContext::ParseNullValue(Token token) {
		Advance();

		AST::GraphQLScalarValue value;
		value.Kind = AST::ASTNodeKind::NullValue;
		value.Value = "";
		value.Location = GetLocation(token.Start);

		return value;
	}

	AST::GraphQLValue ParserContext::ParseEnumValue(Token token) {
		Advance();

		AST::GraphQLScalarValue value;
		value.Kind = AST::ASTNodeKind::EnumValue;
		value.Value = token.Value;
		value.Location = GetLocation(token.Start);

		return value;
	}

	AST::GraphQLType ParserContext::AdvanceThroughColonAndParseType() {
		Expect(TokenKind::COLON);
		return ParseType();
	}

	AST::GraphQLType ParserContext::ParseType() {
		AST::GraphQLType type;
		int start = current_token.Start;

		if (Skip(TokenKind::BRACKET_L)) {
			AST::GraphQLType type_1 = ParseType();
			Expect(TokenKind::BRACKET_R);

			type = AST::GraphQLListType(type_1);
			type.Location = GetLocation(start);
		}
		else {
			type = ParseNamedType();
		}

		if (Skip(TokenKind::BANG)) {
			AST::GraphQLNonNullType nn_type;
			nn_type.Type = type;
			nn_type.Location = GetLocation(start);

			return nn_type;
		}

		return type;
	}

	AST::GraphQLValue ParserContext::SkipEqualsAndParseValueLiteral() {
		return Skip(TokenKind::EQUALS) ? ParseValueLiteral(true) : AST::GraphQLValue();
	}

	AST::ASTNode ParserContext::ParseNamedDefinition() {
		std::string value = current_token.Value;

		if (value == "query" || value == "mutation" || value == "subscription") {
			return ParseOperationDefinition();
		}
		else if (value == "fragment") {
			return ParseFragmentDefinition();
		}
		else if (value == "schema") {
			return ParseSchemaDefinition();
		}
		else if (value == "scalar") {
			return ParseScalarTypeDefinition();
		}
		else if (value == "type") {
			return ParseObjectTypeDefinition();
		}
		else if (value == "interface") {
			return ParseInterfaceTypeDefinition();
		}
		else if (value == "union") {
			return ParseUnionTypeDefinition();
		}
		else if (value == "enum") {
			return ParseEnumTypeDefinition();
		}
		else if (value == "input") {
			return ParseInputObjectTypeDefinition();
		}
		else if (value == "extend") {
			return ParseTypeExtensionDefinition();
		}
		else if (value == "directive") {
			return ParseDirectiveDefinition();
		}
		else {
			return AST::ASTNode();
		}
	}

	AST::GraphQLFragmentDefinition ParserContext::ParseFragmentDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;

		ExpectKeyword("fragment");

		AST::GraphQLFragmentDefinition definition;
		definition.set_comment(comment);
		definition.Name = ParseFragmentName();
		definition.TypeCondition = ExpectOnKeywordAndParseNamedType();
		definition.Directives = ParseDirectives();
		definition.SelectionSet = ParseSelectionSet();
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLNamedType ParserContext::ExpectOnKeywordAndParseNamedType() {
		ExpectKeyword("on");

		return ParseNamedType();
	}

	AST::GraphQLSchemaDefinition ParserContext::ParseSchemaDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;

		ExpectKeyword("schema");

		std::vector<AST::GraphQLDirective> directives = ParseDirectives();
		auto operation_types = ManyOperationTypeDefinition(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLOperationTypeDefinition {
			return context->ParseOperationTypeDefinition();
			}, TokenKind::BRACE_R);

		AST::GraphQLSchemaDefinition definition;
		definition.set_comment(comment);
		definition.Directives = directives;
		definition.OperationTypes = operation_types;
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLOperationTypeDefinition ParserContext::ParseOperationTypeDefinition() {
		int start = current_token.Start;
		AST::OperationType operation = ParseOperationType();

		Expect(TokenKind::COLON);
		AST::GraphQLNamedType type = ParseNamedType();

		AST::GraphQLOperationTypeDefinition definition;
		definition.Operation = operation;
		definition.Type = type;
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLScalarTypeDefinition ParserContext::ParseScalarTypeDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;

		ExpectKeyword("scalar");
		AST::GraphQLName name = ParseName();
		std::vector<AST::GraphQLDirective> directives = ParseDirectives();

		AST::GraphQLScalarTypeDefinition definition;
		definition.set_comment(comment);
		definition.Name = name;
		definition.Directives = directives;
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLObjectTypeDefinition ParserContext::ParseObjectTypeDefinition() {
		AST::GraphQLComment comment = GetComment();

		int start = current_token.Start;
		ExpectKeyword("type");

		AST::GraphQLObjectTypeDefinition definition;
		definition.set_comment(comment);
		definition.Name = ParseName();
		definition.Interfaces = ParseImplementsInterfaces();
		definition.Directives = ParseDirectives();
		definition.Fields = Any(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLFieldDefinition {
			return context->ParseFieldDefinition();
			}, TokenKind::BRACE_R);
		definition.Location = GetLocation(start);

		return definition;
	}

	std::vector<AST::GraphQLNamedType> ParserContext::ParseImplementsInterfaces() {
		std::vector<AST::GraphQLNamedType> types;

		if (current_token.Value == "implements") {
			Advance();

			do {
				types.push_back(ParseNamedType());
			} while (Peek(TokenKind::NAME));
		}

		return types;
	}

	AST::GraphQLFieldDefinition ParserContext::ParseFieldDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		AST::GraphQLName name = ParseName();
		std::vector<AST::GraphQLInputValueDefinition> args = ParseArgumentDefs();
		Expect(TokenKind::COLON);

		AST::GraphQLFieldDefinition definition;
		definition.set_comment(comment);
		definition.Name = name;
		definition.Arguments = args;
		definition.Type = ParseType();
		definition.Directives = ParseDirectives();
		definition.Location = GetLocation(start);

		return definition;
	}

	std::vector<AST::GraphQLInputValueDefinition> ParserContext::ParseArgumentDefs() {
		if (Peek(TokenKind::PAREN_L)) {
			return ManyInputValueDefinition(TokenKind::PAREN_L, [](ParserContext* context) -> AST::GraphQLInputValueDefinition {
				return context->ParseInputValueDef();
				}, TokenKind::PAREN_R);
		}

		return std::vector<AST::GraphQLInputValueDefinition>();
	}

	AST::GraphQLInputValueDefinition ParserContext::ParseInputValueDef() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		AST::GraphQLName name = ParseName();
		Expect(TokenKind::COLON);

		AST::GraphQLInputValueDefinition definition;
		definition.set_comment(comment);
		definition.Name = name;
		definition.Type = ParseType();
		definition.DefaultValue = GetDefaultConstantValue();
		definition.Directives = ParseDirectives();
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLValue ParserContext::GetDefaultConstantValue() {
		AST::GraphQLValue default_value;

		if (Skip(TokenKind::EQUALS)) {
			default_value = ParseConstantValue();
		}

		return default_value;
	}

	AST::GraphQLInterfaceTypeDefinition ParserContext::ParseInterfaceTypeDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("interface");

		AST::GraphQLInterfaceTypeDefinition definition;
		definition.set_comment(comment);
		definition.Name = ParseName();
		definition.Directives = ParseDirectives();
		definition.Fields = Any(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLFieldDefinition {
			return context->ParseFieldDefinition();
			}, TokenKind::BRACE_R);
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLUnionTypeDefinition ParserContext::ParseUnionTypeDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("union");

		AST::GraphQLName name = ParseName();
		std::vector<AST::GraphQLDirective> directives = ParseDirectives();
		Expect(TokenKind::EQUALS);
		std::vector<AST::GraphQLNamedType> types = ParseUnionMembers();

		AST::GraphQLUnionTypeDefinition definition;
		definition.set_comment(comment);
		definition.Name = name;
		definition.Directives = directives;
		definition.Types = types;
		definition.Location = GetLocation(start);

		return definition;
	}

	std::vector<AST::GraphQLNamedType> ParserContext::ParseUnionMembers() {
		std::vector<AST::GraphQLNamedType> members;

		Skip(TokenKind::PIPE);

		do {
			members.push_back(ParseNamedType());
		} while (Skip(TokenKind::PIPE));

		return members;
	}

	AST::GraphQLEnumTypeDefinition ParserContext::ParseEnumTypeDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("enum");

		AST::GraphQLEnumTypeDefinition definition;
		definition.set_comment(comment);
		definition.Name = ParseName();
		definition.Directives = ParseDirectives();
		definition.Values = ManyEnumValueDefinition(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLEnumValueDefinition {
			return context->ParseEnumValueDefinition();
			}, TokenKind::BRACE_R);
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLEnumValueDefinition ParserContext::ParseEnumValueDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;

		AST::GraphQLEnumValueDefinition definition;
		definition.set_comment(comment);
		definition.Name = ParseName();
		definition.Directives = ParseDirectives();
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLInputObjectTypeDefinition ParserContext::ParseInputObjectTypeDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("input");

		AST::GraphQLInputObjectTypeDefinition definition;
		definition.set_comment(comment);
		definition.Name = ParseName();
		definition.Directives = ParseDirectives();
		definition.Fields = Any(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLInputValueDefinition {
			return context->ParseInputValueDef();
			}, TokenKind::BRACE_R);
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLTypeExtensionDefinition ParserContext::ParseTypeExtensionDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("extend");
		AST::GraphQLObjectTypeDefinition type_definition = ParseObjectTypeDefinition();

		AST::GraphQLTypeExtensionDefinition definition;
		definition.set_comment(comment);
		definition.Name = definition.Name;
		definition.Definition = type_definition;
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLDirectiveDefinition ParserContext::ParseDirectiveDefinition() {
		AST::GraphQLComment comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("directive");
		Expect(TokenKind::AT);
		AST::GraphQLName name = ParseName();
		std::vector<AST::GraphQLInputValueDefinition> args = ParseArgumentDefs();
		bool repeatable = ParseRepeatable();

		ExpectKeyword("on");
		auto locations = ParseDirectiveLocations();

		AST::GraphQLDirectiveDefinition definition(name, repeatable, args, locations);
		definition.set_comment(comment);
		definition.Location = GetLocation(start);

		return definition;
	}

	bool ParserContext::ParseRepeatable() {
		if (Peek(TokenKind::NAME)) {
			if (current_token.Value == "repeatable") {
				Advance();
				return true;
			}
			else if (current_token.Value == "on") {
				return false;
			}
			else {
				throw Exceptions::GraphQLSyntaxErrorException("Unexpected " + current_token.to_string(), source, current_token.Start);
			}
		}

		return false;
	}

	std::vector<AST::GraphQLName> ParserContext::ParseDirectiveLocations() {
		std::vector<AST::GraphQLName> locations;

		Skip(TokenKind::PIPE);

		do {
			locations.push_back(ParseName());
		} while (Skip(TokenKind::PIPE));

		return locations;
	}

	bool ParserContext::Peek(TokenKind kind) {
		return current_token.Kind == kind;
	}

	bool ParserContext::Skip(TokenKind kind) {
		ParseComment();

		bool is_current_token_matching = current_token.Kind == kind;

		if (is_current_token_matching) {
			Advance();
		}

		return is_current_token_matching;
	}
}
