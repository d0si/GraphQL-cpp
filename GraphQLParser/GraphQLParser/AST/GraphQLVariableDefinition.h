#pragma once

#include <memory>
#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLSelectionSet.h>
#include <GraphQLParser/AST/GraphQLType.h>
#include <GraphQLParser/AST/GraphQLVariable.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLVariableDefinition : public ASTNode {
		public:
			GraphQLVariableDefinition(std::shared_ptr<GraphQLVariable> variable, GraphQLType type, std::shared_ptr<GraphQLValue> default_value);

			std::shared_ptr<GraphQLVariable> Variable;

			GraphQLType Type;
			
			std::shared_ptr<GraphQLValue> DefaultValue;
		};
	}
}
