#include <GraphQLParser/AST/GraphQLTypeExtensionDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLTypeExtensionDefinition::GraphQLTypeExtensionDefinition(GraphQLName name, std::shared_ptr<GraphQLObjectTypeDefinition> definition)
			: GraphQLTypeDefinition(ASTNodeKind::TypeExtensionDefinition, name), Definition(definition) {

		}
	}
}
