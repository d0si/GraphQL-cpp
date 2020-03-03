#include <GraphQLParser/AST/GraphQLTypeExtensionDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLTypeExtensionDefinition::GraphQLTypeExtensionDefinition(GraphQLName name, GraphQLObjectTypeDefinition* definition)
			: GraphQLTypeDefinition(ASTNodeKind::TypeExtensionDefinition, name), Definition(definition) {

		}
	}
}
