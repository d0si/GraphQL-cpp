#include <GraphQL/Utilities/SchemaBuilder.h>
#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/Source.h>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLTypeExtensionDefinition.h>

namespace GraphQL {
	namespace Utilities {
		Types::ISchema SchemaBuilder::Build(std::string type_definitions) {
			auto document = Parse(type_definitions);

			Validate(document);

			return BuildSchemaFrom(document);
		}

		GraphQLParser::AST::GraphQLDocument SchemaBuilder::Parse(std::string document) {
			auto lexer = GraphQLParser::Lexer();
			auto parser = GraphQLParser::Parser(lexer);

			return parser.Parse(GraphQLParser::Source(document));
		}

		void SchemaBuilder::Validate(GraphQLParser::AST::GraphQLDocument document) {
			std::vector<std::pair<std::string, GraphQLParser::AST::GraphQLTypeDefinition>> definitions_by_name;
			for (auto def : document.Definitions) {
				if (def.Kind == GraphQLParser::AST::ASTNodeKind::TypeExtensionDefinition) {
					GraphQLParser::AST::GraphQLTypeExtensionDefinition definition = ;

					std::pair<std::string, GraphQLParser::AST::GraphQLTypeDefinition> definition_pair;
					definition_pair.first = definition.Name.Value;
					definition_pair.second = definition;
					definitions_by_name.push_back(definition_pair);
				}
			}
		}
	}
}
