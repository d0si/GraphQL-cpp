#include <GraphQLParser/ParserContext.h>
#include <GraphQLParser/Exceptions/GraphQLSyntaxErrorException.h>
#include <GraphQLParser/AST/GraphQLOperationDefinition.h>
#include <GraphQLParser/AST/GraphQLFragmentSpread.h>
#include <GraphQLParser/AST/GraphQLInlineFragment.h>

namespace GraphQLParser {
	ParserContext::ParserContext(Source source, Lexer lexer) : source(source), lexer(lexer), current_token(Token(TokenKind::UNKNOWN, "", 0, 0)) {
		// comments = null;

		current_token = lexer.Lex(source);
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
		definition.Comment = comment;
		definition.Operation = AST::OperationType::Query;
		definition.SelectionSet = ParseSelectionSet();
		definition.Location = GetLocation(start);

		return definition;
	}

	AST::ASTNode ParserContext::CreateOperationDefinition(int start, AST::OperationType operation, AST::GraphQLName name) {
		AST::GraphQLComment comment = GetComment();

		AST::GraphQLOperationDefinition definition;
		definition.Comment = comment;
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

	AST::GraphQLLocation ParserContext::GetLocation(int start) {
		return AST::GraphQLLocation(start, current_token.End);
	}

	AST::GraphQLName ParserContext::GetName() {
		return Peek(TokenKind::NAME) ? ParseName() : AST::GraphQLName();
	}

	std::vector<AST::ASTNode> ParserContext::ManyNode(TokenKind open, std::vector<AST::ASTNode>(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		auto nodes = next(this);

		while (!Skip(close)) {
			auto nodes1 = next(this);
			for (auto node : nodes1) {
				nodes.push_back(node);
			}
		}

		return nodes;
	}

	std::vector<AST::GraphQLArgument> ParserContext::ManyArgument(TokenKind open, std::vector<AST::GraphQLArgument>(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		auto nodes = next(this);

		while (!Skip(close)) {
			auto nodes1 = next(this);
			for (auto node : nodes1) {
				nodes.push_back(node);
			}
		}

		return nodes;
	}


	std::vector<AST::GraphQLVariableDefinition> ParserContext::ManyVariableDefinition(TokenKind open, std::vector<AST::GraphQLVariableDefinition>(*next)(ParserContext*), TokenKind close) {
		Expect(open);

		ParseComment();

		auto nodes = next(this);

		while (!Skip(close)) {
			auto nodes1 = next(this);
			for (auto node : nodes1) {
				nodes.push_back(node);
			}
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

		AST::GraphQLArgument argument;
		argument.Comment = comment;
		argument.Name = ParseName();
		argument.Value = ExpectColonAndParseValueLiteral(false);
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
			return AST::GraphQLComment("");
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

		field_selection.Comment = comment;
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
			context->ParseSelection();
			},
			TokenKind::BRACE_R);
		selection_set.Location = GetLocation(start);

		return selection_set;
	}

	std::vector<AST::GraphQLVariableDefinition> ParserContext::ParseVariableDefinitions() {
		return Peek(TokenKind::PAREN_L) ?
			ManyVariableDefinition(TokenKind::PAREN_L, [](ParserContext* context) {
			context->ParseVariableDefinition()
				}, TokenKind::PAREN_R)
			: std::vector<AST::GraphQLVariableDefinition>();
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
		
		AST::GraphQLDirective directive;
		directive.Name = ParseName();
		directive.Arguments = ParseArguments();
		directive.Location = GetLocation(start);

		return directive;
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
