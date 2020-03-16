#pragma once

#include <memory>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLObjectTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLTypeExtensionDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLTypeExtensionDefinition(std::shared_ptr<GraphQLName> name, std::shared_ptr<GraphQLObjectTypeDefinition> definition);

			std::shared_ptr<GraphQLObjectTypeDefinition> Definition;
		};
	}
}
