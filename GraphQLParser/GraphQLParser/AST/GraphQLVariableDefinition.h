#pragma once

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
			GraphQLVariableDefinition(GraphQLVariable variable, GraphQLType type, GraphQLValue default_value);

			GraphQLVariable Variable;

			GraphQLType Type;
			
			GraphQLValue DefaultValue;
		};
	}
}
