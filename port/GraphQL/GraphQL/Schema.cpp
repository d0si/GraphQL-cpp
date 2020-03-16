#include <GraphQL/Schema.h>
#include <set>
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/AST/GraphQLTypeExtensionDefinition.h>

namespace GraphQL {
	void Schema::parse_definitions(std::string definitions) {
		GraphQLParser::Parser parser;
		document_ = parser.Parse(GraphQLParser::Source(definitions));

		validate();

		// TODO
	}

	void Schema::validate() {
		std::set<std::string> definitions;
		std::set<std::string> duplicates;

		for (auto def : document_.Definitions) {
			if (def->Kind == GraphQLParser::AST::ASTNodeKind::TypeExtensionDefinition) {
				auto definition = std::static_pointer_cast<GraphQLParser::AST::GraphQLTypeExtensionDefinition>(def);
				auto definition_name = definition->Name->Value;

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

	Schema Schema::from_definitions(std::string definitions) {
		Schema schema;
		schema.parse_definitions(definitions);

		return schema;
	}
}
