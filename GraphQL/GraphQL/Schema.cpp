#include <GraphQL/Schema.h>
#include <GraphQLParser/Parser.h>

namespace GraphQL {
	Schema Schema::parse(std::string definitions) {
		GraphQLParser::Parser parser;
		GraphQLParser::AST::GraphQLDocument doc = parser.Parse(GraphQLParser::Source(definitions));


	}
}
