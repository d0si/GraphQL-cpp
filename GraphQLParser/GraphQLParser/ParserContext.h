#pragma once

#include <GraphQLParser/ISource.h>
#include <GraphQLParser/ILexer.h>
#include <GraphQLParser/Token.h>

namespace GraphQLParser {
	class ParserContext {
	private:
		ILexer lexer;
		ISource source;
		// Stack<GraphQLComment>? comments;
		Token current_token;

	public:
		ParserContext(ISource source, ILexer lexer) : source(source), lexer(lexer) {
			// comments = null;

			current_token = lexer.Lex(source);
		}
	};
}
