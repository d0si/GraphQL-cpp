#pragma once

#include <memory>
#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLObjectField: public ASTNode {
		public:
			GraphQLObjectField();
			GraphQLObjectField(std::shared_ptr<GraphQLName> name, std::shared_ptr<GraphQLValue> value);

			std::shared_ptr<GraphQLName> Name;

			std::shared_ptr<GraphQLValue> Value;
		};
	}
}
