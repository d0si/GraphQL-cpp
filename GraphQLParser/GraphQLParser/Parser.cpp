#include <GraphQLParser/Parser.h>
#include <GraphQLParser/ParserContext.h>

namespace GraphQLParser {
	Parser::Parser(Lexer lexer) : lexer(lexer) {

	}


	AST::GraphQLDocument Parser::Parse(Source source) {
		auto context = ParserContext(source, lexer);

		return context.Parse();
	}
}
