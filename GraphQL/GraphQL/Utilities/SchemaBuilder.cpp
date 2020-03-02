#include <GraphQL/Utilities/SchemaBuilder.h>
#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/Source.h>

namespace GraphQL {
	namespace Utilities {
		Types::ISchema SchemaBuilder::Build(std::string type_definitions) {
			auto document = Parse(type_definitions);
			/*Validate(document);

			return BuildSchemaFrom(document);*/
		}

		GraphQLParser::AST::GraphQLDocument SchemaBuilder::Parse(std::string document) {
			auto lexer = GraphQLParser::Lexer();
			auto parser = GraphQLParser::Parser(lexer);

			return parser.Parse(GraphQLParser::Source(document));
		}
	}
}