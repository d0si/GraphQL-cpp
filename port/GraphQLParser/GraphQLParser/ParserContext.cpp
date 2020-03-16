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
	ParserContext::ParserContext(const Source& source, Lexer lexer) : source(source), lexer(lexer), current_token(lexer.Lex(source)) {

	}

	AST::GraphQLDocument ParserContext::Parse() {
		return ParseDocument();
	}

	std::shared_ptr<AST::GraphQLComment> ParserContext::GetComment() {
		if (!comments.empty()) {
			std::shared_ptr<AST::GraphQLComment> comment = comments.top();
			comments.pop();

			return comment;
		}

		return nullptr;
	}

	void ParserContext::Advance() {
		current_token = lexer.Lex(source, current_token.End);
	}

	AST::GraphQLDocument ParserContext::CreateDocument(int start, std::vector<std::shared_ptr<AST::ASTNode>> definitions) const {
		AST::GraphQLDocument document(definitions);

		document.Location.Start = start;
		document.Location.End = current_token.End;

		return document;
	}

	std::shared_ptr<AST::ASTNode> ParserContext::CreateOperationDefinition(int start) {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();

		std::shared_ptr<AST::GraphQLOperationDefinition> definition =
			std::make_shared<AST::GraphQLOperationDefinition>(AST::OperationType::Query, ParseSelectionSet());
		definition->Comment = comment;
		definition->Location = GetLocation(start);

		return definition;
	}

	std::shared_ptr<AST::ASTNode> ParserContext::CreateOperationDefinition(int start, AST::OperationType operation, std::shared_ptr<AST::GraphQLName> name) {
		auto comment = GetComment();
		auto definitions = ParseVariableDefinitions();
		auto directives = ParseDirectives();
		auto selection_set = ParseSelectionSet();

		std::shared_ptr<AST::GraphQLOperationDefinition> definition = std::make_shared<AST::GraphQLOperationDefinition>(
			operation,
			name,
			definitions,
			directives,
			selection_set
		);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

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

	void ParserContext::ExpectKeyword(const std::string& keyword) {
		Token token = current_token;

		if (token.Kind == TokenKind::NAME && keyword == token.Value) {
			Advance();

			return;
		}

		throw Exceptions::GraphQLSyntaxErrorException("Expected \"" + keyword + "\", found Name \"" + token.Value + "\"", source, current_token.Start);
	}

	AST::GraphQLLocation ParserContext::GetLocation(int start) const {
		return AST::GraphQLLocation(start, current_token.End);
	}

	std::shared_ptr<AST::GraphQLName> ParserContext::GetName() {
		return Peek(TokenKind::NAME) ? ParseName() : nullptr;
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

	std::vector<std::shared_ptr<AST::GraphQLValue>> ParserContext::Any(TokenKind open, std::shared_ptr<AST::GraphQLValue> (*next)(ParserContext*, bool is_constant), bool is_constant, TokenKind close) {
		Expect(open);

		ParseComment();

		std::vector<std::shared_ptr<AST::GraphQLValue>> nodes;

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
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		auto name = ParseName();
		auto value_literal = ExpectColonAndParseValueLiteral(false);

		AST::GraphQLArgument argument(name, value_literal);
		argument.Comment = comment;
		argument.Location = GetLocation(start);

		return argument;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ExpectColonAndParseValueLiteral(bool is_constant) {
		Expect(TokenKind::COLON);

		return ParseValueLiteral(is_constant);
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseValueLiteral(bool is_constant) {
		std::shared_ptr<AST::GraphQLValue> value = nullptr;

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

	std::shared_ptr<AST::GraphQLName> ParserContext::ParseName() {
		int start = current_token.Start;
		std::string value = current_token.Value;

		Expect(TokenKind::NAME);

		std::shared_ptr<AST::GraphQLName> name = std::make_shared<AST::GraphQLName>(value);
		name->Location = GetLocation(start);

		return name;
	}

	std::shared_ptr<AST::GraphQLComment> ParserContext::ParseComment() {
		if (!Peek(TokenKind::COMMENT)) {
			return nullptr;
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
			text = text.substr(0, text.length() - 1);
		}

		std::shared_ptr<AST::GraphQLComment> comment = std::make_shared<AST::GraphQLComment>(text);
		comment->Location.Start = start;
		comment->Location.End = end;

		comments.push(comment);

		return comment;
	}

	std::vector<std::shared_ptr<AST::ASTNode>> ParserContext::ParseDefinitionsIfNotEOF() {
		std::vector<std::shared_ptr<AST::ASTNode>> result;

		if (current_token.Kind != TokenKind::EOF_) {
			do {
				result.push_back(ParseDefinition());
			} while (!Skip(TokenKind::EOF_));
		}

		return result;
	}

	std::shared_ptr<AST::ASTNode> ParserContext::ParseDefinition() {
		ParseComment();

		if (Peek(TokenKind::BRACE_L)) {
			return ParseOperationDefinition();
		}

		if (Peek(TokenKind::NAME)) {
			std::shared_ptr<AST::ASTNode> definition = ParseNamedDefinition();

			if (definition != nullptr) {
				return definition;
			}
		}

		throw Exceptions::GraphQLSyntaxErrorException("Unexpected " + current_token.to_string(), source, current_token.Start);
	}

	std::shared_ptr<AST::ASTNode> ParserContext::ParseOperationDefinition() {
		int start = current_token.Start;

		if (Peek(TokenKind::BRACE_L)) {
			return CreateOperationDefinition(start);
		}

		auto operation_type = ParseOperationType();
		auto name = GetName();

		return CreateOperationDefinition(start, operation_type, name);
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
		std::vector<std::shared_ptr<AST::ASTNode>> definitions = ParseDefinitionsIfNotEOF();

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
		auto name = ParseFragmentName();
		auto directives = ParseDirectives();

		AST::GraphQLFragmentSpread fragment(name, directives);
		fragment.Location = GetLocation(start);

		return fragment;
	}

	AST::ASTNode ParserContext::CreateInlineFragment(int start) {
		auto type_condition = GetTypeCondition();
		auto directives = ParseDirectives();
		auto selection_set = ParseSelectionSet();

		AST::GraphQLInlineFragment fragment(
			type_condition,
			directives,
			selection_set
		);
		fragment.Location = GetLocation(start);

		return fragment;
	}

	std::shared_ptr<AST::GraphQLName> ParserContext::ParseFragmentName() {
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
		auto name = ParseName();

		AST::GraphQLNamedType type(name);
		type.Location = GetLocation(start);

		return type;
	}

	AST::ASTNode ParserContext::ParseFieldSelection() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		std::shared_ptr<AST::GraphQLName> name_or_alias = ParseName();
		std::shared_ptr<AST::GraphQLName> name;
		std::shared_ptr<AST::GraphQLName> alias;

		if (Skip(TokenKind::COLON)) {
			name = ParseName();
			alias = name_or_alias;
		}
		else {
			name = name_or_alias;
		}

		return CreateFieldSelection(start, name, alias, comment);
	}

	AST::GraphQLFieldSelection ParserContext::CreateFieldSelection(
		int start,
		std::shared_ptr<AST::GraphQLName> name,
		std::shared_ptr<AST::GraphQLName> alias,
		std::shared_ptr<AST::GraphQLComment> comment
	) {
		auto arguments = ParseArguments();
		auto directives = ParseDirectives();
		auto selection_set = Peek(TokenKind::BRACE_L) ? ParseSelectionSet() : AST::GraphQLSelectionSet();

		AST::GraphQLFieldSelection field_selection(
			alias,
			name,
			arguments,
			directives,
			selection_set
		);

		field_selection.Comment = comment;
		field_selection.Location = GetLocation(start);

		return field_selection;
	}

	AST::GraphQLSelectionSet ParserContext::ParseSelectionSet() {
		int start = current_token.Start;

		AST::GraphQLSelectionSet selection_set(
			ManyNode(TokenKind::BRACE_L, [](ParserContext* context) -> AST::ASTNode {
				return context->ParseSelection();
				},
				TokenKind::BRACE_R));
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
		auto variable = ParseVariable();
		auto type = AdvanceThroughColonAndParseType();
		auto value_literal = SkipEqualsAndParseValueLiteral();

		AST::GraphQLVariableDefinition definition(
			variable,
			type,
			value_literal
		);
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
		auto name = ParseName();
		auto arguments = ParseArguments();

		AST::GraphQLDirective directive(name, arguments);
		directive.Location = GetLocation(start);

		return directive;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseList(bool is_constant) {
		int start = current_token.Start;

		std::shared_ptr<AST::GraphQLListValue> list = std::make_shared<AST::GraphQLListValue>(
			AST::ASTNodeKind::ListValue,
			Any(TokenKind::BRACKET_L, [](ParserContext* context, bool is_constant) -> std::shared_ptr<AST::GraphQLValue> {
				if (is_constant) {
					return context->ParseConstantValue();
				}
				else {
					return context->ParseValueValue();
				}
				}, is_constant, TokenKind::BRACKET_R)
		);
		list->Location = GetLocation(start);
		list->AstValue = source.Body.substr(start, current_token.End - start - 1);

		return list;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseObject(bool is_constant) {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;

		std::vector<AST::GraphQLObjectField> fields = ParseObjectFields(is_constant);
		AST::GraphQLLocation location = GetLocation(start);

		std::shared_ptr<AST::GraphQLObjectValue> value = std::make_shared<AST::GraphQLObjectValue>(fields);
		value->Location = location;
		value->Comment = comment;

		return value;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseInt(bool is_constant) {
		Token token = current_token;
		Advance();

		std::shared_ptr<AST::GraphQLScalarValue> value = std::make_shared<AST::GraphQLScalarValue>(AST::ASTNodeKind::IntValue, token.Value);
		value->Location = GetLocation(token.Start);

		return value;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseFloat(bool is_constant) {
		Token token = current_token;

		Advance();

		std::shared_ptr<AST::GraphQLScalarValue> value = std::make_shared<AST::GraphQLScalarValue>(AST::ASTNodeKind::FloatValue, token.Value);
		value->Location = GetLocation(token.Start);

		return value;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseString(bool is_constant) {
		Token token = current_token;

		Advance();

		std::shared_ptr<AST::GraphQLScalarValue> value = std::make_shared<AST::GraphQLScalarValue>(AST::ASTNodeKind::StringValue, token.Value);
		value->Location = GetLocation(token.Start);

		return value;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseNameValue(bool is_constant) {
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

	std::shared_ptr<AST::GraphQLVariable> ParserContext::ParseVariable() {
		int start = current_token.Start;
		Expect(TokenKind::DOLLAR);
		auto name = GetName();

		std::shared_ptr<AST::GraphQLVariable> variable = std::make_shared<AST::GraphQLVariable>(name);
		variable->Location = GetLocation(start);

		return variable;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseConstantValue() {
		return ParseValueLiteral(true);
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseValueValue() {
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
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		auto name = ParseName();
		auto value_literal = ExpectColonAndParseValueLiteral(is_constant);

		AST::GraphQLObjectField field(name, value_literal);
		field.Comment = comment;
		field.Location = GetLocation(start);

		return field;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseBooleanValue(Token token) {
		Advance();

		std::shared_ptr<AST::GraphQLScalarValue> value = std::make_shared<AST::GraphQLScalarValue>(AST::ASTNodeKind::BooleanValue, token.Value);
		value->Location = GetLocation(token.Start);

		return value;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseNullValue(Token token) {
		Advance();

		std::shared_ptr<AST::GraphQLScalarValue> value = std::make_shared<AST::GraphQLScalarValue>(AST::ASTNodeKind::NullValue, "");
		value->Location = GetLocation(token.Start);

		return value;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::ParseEnumValue(Token token) {
		Advance();

		std::shared_ptr<AST::GraphQLScalarValue> value = std::make_shared<AST::GraphQLScalarValue>(AST::ASTNodeKind::EnumValue, token.Value);
		value->Location = GetLocation(token.Start);

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
			AST::GraphQLNonNullType nn_type(type);
			nn_type.Location = GetLocation(start);

			return nn_type;
		}

		return type;
	}
	
	std::shared_ptr<AST::GraphQLValue> ParserContext::SkipEqualsAndParseValueLiteral() {
		return Skip(TokenKind::EQUALS) ? ParseValueLiteral(true) : nullptr;
	}

	std::shared_ptr<AST::ASTNode> ParserContext::ParseNamedDefinition() {
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
			return nullptr;
		}
	}

	std::shared_ptr<AST::GraphQLFragmentDefinition> ParserContext::ParseFragmentDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;

		ExpectKeyword("fragment");

		auto name = ParseFragmentName();
		auto named_type = ExpectOnKeywordAndParseNamedType();
		auto directives = ParseDirectives();
		auto selection_set = ParseSelectionSet();

		std::shared_ptr<AST::GraphQLFragmentDefinition> definition = std::make_shared<AST::GraphQLFragmentDefinition>(
			name,
			named_type,
			directives,
			selection_set
		);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLNamedType ParserContext::ExpectOnKeywordAndParseNamedType() {
		ExpectKeyword("on");

		return ParseNamedType();
	}

	std::shared_ptr<AST::GraphQLSchemaDefinition> ParserContext::ParseSchemaDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;

		ExpectKeyword("schema");

		std::vector<AST::GraphQLDirective> directives = ParseDirectives();
		auto operation_types = ManyOperationTypeDefinition(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLOperationTypeDefinition {
			return context->ParseOperationTypeDefinition();
			}, TokenKind::BRACE_R);

		std::shared_ptr<AST::GraphQLSchemaDefinition> definition = std::make_shared<AST::GraphQLSchemaDefinition>(directives, operation_types);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLOperationTypeDefinition ParserContext::ParseOperationTypeDefinition() {
		int start = current_token.Start;
		AST::OperationType operation = ParseOperationType();

		Expect(TokenKind::COLON);
		AST::GraphQLNamedType type = ParseNamedType();

		AST::GraphQLOperationTypeDefinition definition(operation, type);
		definition.Location = GetLocation(start);

		return definition;
	}

	std::shared_ptr<AST::GraphQLScalarTypeDefinition> ParserContext::ParseScalarTypeDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;

		ExpectKeyword("scalar");
		auto name = ParseName();
		std::vector<AST::GraphQLDirective> directives = ParseDirectives();

		std::shared_ptr<AST::GraphQLScalarTypeDefinition> definition = std::make_shared<AST::GraphQLScalarTypeDefinition>(name, directives);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

		return definition;
	}

	std::shared_ptr<AST::GraphQLObjectTypeDefinition> ParserContext::ParseObjectTypeDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();

		int start = current_token.Start;
		ExpectKeyword("type");
		auto name = ParseName();
		auto implements_interfaces = ParseImplementsInterfaces();
		auto directives = ParseDirectives();
		auto fields = Any(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLFieldDefinition {
			return context->ParseFieldDefinition();
			}, TokenKind::BRACE_R);

		std::shared_ptr<AST::GraphQLObjectTypeDefinition> definition = std::make_shared<AST::GraphQLObjectTypeDefinition>(
			name,
			implements_interfaces,
			directives,
			fields
		);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

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
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		auto name = ParseName();
		std::vector<AST::GraphQLInputValueDefinition> args = ParseArgumentDefs();
		Expect(TokenKind::COLON);
		auto type = ParseType();
		auto directives = ParseDirectives();

		AST::GraphQLFieldDefinition definition(
			name,
			args,
			type,
			directives
		);
		definition.Comment = comment;
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
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		auto name = ParseName();
		Expect(TokenKind::COLON);
		auto type = ParseType();
		auto default_constant_value = GetDefaultConstantValue();
		auto directives = ParseDirectives();

		AST::GraphQLInputValueDefinition definition(
			name,
			type,
			default_constant_value,
			directives
		);
		definition.Comment = comment;
		definition.Location = GetLocation(start);

		return definition;
	}

	std::shared_ptr<AST::GraphQLValue> ParserContext::GetDefaultConstantValue() {
		std::shared_ptr<AST::GraphQLValue> default_value = nullptr;

		if (Skip(TokenKind::EQUALS)) {
			default_value = ParseConstantValue();
		}

		return default_value;
	}

	std::shared_ptr<AST::GraphQLInterfaceTypeDefinition> ParserContext::ParseInterfaceTypeDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("interface");
		auto name = ParseName();
		auto directives = ParseDirectives();
		auto fields = Any(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLFieldDefinition {
			return context->ParseFieldDefinition();
			}, TokenKind::BRACE_R);

		std::shared_ptr<AST::GraphQLInterfaceTypeDefinition> definition = std::make_shared<AST::GraphQLInterfaceTypeDefinition>(
			name,
			directives,
			fields
		);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

		return definition;
	}

	std::shared_ptr<AST::GraphQLUnionTypeDefinition> ParserContext::ParseUnionTypeDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("union");

		auto name = ParseName();
		std::vector<AST::GraphQLDirective> directives = ParseDirectives();
		Expect(TokenKind::EQUALS);
		std::vector<AST::GraphQLNamedType> types = ParseUnionMembers();

		std::shared_ptr<AST::GraphQLUnionTypeDefinition> definition = std::make_shared<AST::GraphQLUnionTypeDefinition>(name, directives, types);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

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

	std::shared_ptr<AST::GraphQLEnumTypeDefinition> ParserContext::ParseEnumTypeDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("enum");
		auto name = ParseName();
		auto directives = ParseDirectives();
		auto values = ManyEnumValueDefinition(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLEnumValueDefinition {
			return context->ParseEnumValueDefinition();
			}, TokenKind::BRACE_R);

		std::shared_ptr<AST::GraphQLEnumTypeDefinition> definition = std::make_shared<AST::GraphQLEnumTypeDefinition>(
			name,
			directives,
			values
		);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

		return definition;
	}

	AST::GraphQLEnumValueDefinition ParserContext::ParseEnumValueDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		auto name = ParseName();
		auto directives = ParseDirectives();

		AST::GraphQLEnumValueDefinition definition(name, directives);
		definition.Comment = comment;
		definition.Location = GetLocation(start);

		return definition;
	}

	std::shared_ptr<AST::GraphQLInputObjectTypeDefinition> ParserContext::ParseInputObjectTypeDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("input");
		auto name = ParseName();
		auto directives = ParseDirectives();
		auto fields = Any(TokenKind::BRACE_L, [](ParserContext* context) -> AST::GraphQLInputValueDefinition {
			return context->ParseInputValueDef();
			}, TokenKind::BRACE_R);

		std::shared_ptr<AST::GraphQLInputObjectTypeDefinition> definition = std::make_shared<AST::GraphQLInputObjectTypeDefinition>(
			name,
			directives,
			fields
		);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

		return definition;
	}

	std::shared_ptr<AST::GraphQLTypeExtensionDefinition> ParserContext::ParseTypeExtensionDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("extend");
		std::shared_ptr<AST::GraphQLObjectTypeDefinition> type_definition = ParseObjectTypeDefinition();

		std::shared_ptr<AST::GraphQLTypeExtensionDefinition> definition = std::make_shared<AST::GraphQLTypeExtensionDefinition>(type_definition->Name, type_definition);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

		return definition;
	}

	std::shared_ptr<AST::GraphQLDirectiveDefinition> ParserContext::ParseDirectiveDefinition() {
		std::shared_ptr<AST::GraphQLComment> comment = GetComment();
		int start = current_token.Start;
		ExpectKeyword("directive");
		Expect(TokenKind::AT);
		auto name = ParseName();
		std::vector<AST::GraphQLInputValueDefinition> args = ParseArgumentDefs();
		bool repeatable = ParseRepeatable();

		ExpectKeyword("on");
		auto locations = ParseDirectiveLocations();

		std::shared_ptr<AST::GraphQLDirectiveDefinition> definition = std::make_shared<AST::GraphQLDirectiveDefinition>(name, repeatable, args, locations);
		definition->Comment = comment;
		definition->Location = GetLocation(start);

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

	std::vector<std::shared_ptr<AST::GraphQLName>> ParserContext::ParseDirectiveLocations() {
		std::vector<std::shared_ptr<AST::GraphQLName>> locations;

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
