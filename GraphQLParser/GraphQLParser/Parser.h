#pragma once

#include <GraphQLParser/ILexer.h>
#include <GraphQLParser/ISource.h>
#include <GraphQLParser/ParserContext.h>
#include <GraphQLParser/AST/GraphQLDocument.h>

namespace GraphQLParser {
	class Parser {
	private:
		ILexer lexer;

	public:
		Parser(ILexer lexer) : lexer(lexer) {

		}

		AST::GraphQLDocument Parse(ISource source) {
			auto context = ParserContext(source, lexer);

			//// TODO!!!
		}
	};
}
