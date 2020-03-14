#include <GraphQLParser/Parser.h>
#include <GraphQLParser/ParserContext.h>

namespace GraphQLParser {
	Parser::Parser() : Parser(Lexer()){

	}

	Parser::Parser(Lexer lexer) : lexer(lexer) {

	}

	AST::GraphQLDocument Parser::Parse(const Source& source) const {
		ParserContext context = ParserContext(source, lexer);

		return context.Parse();
	}
}
