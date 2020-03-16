#include <GraphQLParser/AST/GraphQLUnionTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLUnionTypeDefinition::GraphQLUnionTypeDefinition(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives, std::vector<GraphQLNamedType> types)
			: GraphQLTypeDefinition(ASTNodeKind::UnionTypeDefinition, name), Directives(directives), Types(types) {

		}
	}
}
