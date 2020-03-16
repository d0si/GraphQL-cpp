#include <GraphQLParser/AST/GraphQLEnumValueDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLEnumValueDefinition::GraphQLEnumValueDefinition() : GraphQLTypeDefinition(ASTNodeKind::EnumValueDefinition) {

		}

		GraphQLEnumValueDefinition::GraphQLEnumValueDefinition(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives)
			: GraphQLTypeDefinition(ASTNodeKind::EnumValueDefinition, name), Directives(directives) {

		}
	}
}
