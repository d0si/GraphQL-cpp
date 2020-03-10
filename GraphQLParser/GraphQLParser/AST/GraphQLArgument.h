#pragma once

#include <memory>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLArgument : public ASTNode {
		public:
			GraphQLArgument();
			GraphQLArgument(GraphQLName name, std::shared_ptr<GraphQLValue> value);

			GraphQLName Name;

			std::shared_ptr<GraphQLValue> Value;
		};
	}
}
