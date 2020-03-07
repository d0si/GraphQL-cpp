#include <GraphQL/Utilities/SchemaBuilder.h>
#include <set>
#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/Source.h>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLTypeExtensionDefinition.h>
#include <GraphQL/Types/Schema.h>

namespace GraphQL {
	namespace Utilities {
		Types::ISchema SchemaBuilder::Build(std::string type_definitions) {
			auto document = Parse(type_definitions);

			Validate(document);

			return BuildSchemaFrom(document);
		}

		GraphQLParser::AST::GraphQLDocument SchemaBuilder::Parse(std::string document) {
			auto parser = GraphQLParser::Parser(GraphQLParser::Lexer());

			return parser.Parse(GraphQLParser::Source(document));
		}

		void SchemaBuilder::Validate(GraphQLParser::AST::GraphQLDocument document) {
			std::set<std::string> definitions;
			std::set<std::string> duplicates;
			
			for (auto def : document.Definitions) {
				if (def->Kind == GraphQLParser::AST::ASTNodeKind::TypeExtensionDefinition) {
					auto definition = static_cast<GraphQLParser::AST::GraphQLTypeExtensionDefinition*>(def);
					auto definition_name = definition->Name.Value;
					
					if (definitions.count(definition_name) > 0) {
						duplicates.insert(definition_name);
					}
					else {
						definitions.insert(definition_name);
					}
				}
			}

			if (duplicates.size() > 0) {
				std::string error_mesasge = "All types within a GraphQL schema must have unique names. Following types were redefined: ";
				for (auto e : duplicates) {
					error_mesasge += e + ", ";
				}
				error_mesasge = error_mesasge.substr(0, error_mesasge.length() - 2);

				throw std::exception(error_mesasge.c_str());
			}
		}

		Types::ISchema SchemaBuilder::BuildSchemaFrom(GraphQLParser::AST::GraphQLDocument document) {
			// TODO: Directives

			auto schema = Types::Schema(/*ServiceProvider*/);

			PreConfigure(schema);

			auto directives = std::vector<Types::DirectiveGraphType>();
			throw std::exception("Not implemented");
		}
	}
}
