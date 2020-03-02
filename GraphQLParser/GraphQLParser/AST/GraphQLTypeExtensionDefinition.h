#pragma once

#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLObjectTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLTypeExtensionDefinition : public GraphQLTypeDefinition {
		public:
			ASTNodeKind Kind = ASTNodeKind::TypeExtensionDefinition;

			GraphQLObjectTypeDefinition Definition;
		};
	}
}
