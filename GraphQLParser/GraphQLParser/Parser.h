#pragma once

#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/Source.h>
#include <GraphQLParser/AST/GraphQLDocument.h>

namespace GraphQLParser {
	class Parser {
	private:
		Lexer lexer;

	public:
		Parser();
		Parser(Lexer lexer);

		AST::GraphQLDocument Parse(const Source& source) const;
	};
}
