#include <GraphQLParser/AST/GraphQLEnumTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLEnumTypeDefinition::GraphQLEnumTypeDefinition() : GraphQLTypeDefinition(ASTNodeKind::EnumTypeDefinition) {

		}

		GraphQLEnumTypeDefinition::GraphQLEnumTypeDefinition(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives, std::vector<GraphQLEnumValueDefinition> values)
			: GraphQLTypeDefinition(ASTNodeKind::EnumTypeDefinition, name), Directives(directives), Values(values) {

		}
	}
}
