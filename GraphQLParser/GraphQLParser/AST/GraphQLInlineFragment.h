#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLSelectionSet.h>
#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLInlineFragment : public ASTNode {
		public:
			std::vector<GraphQLDirective> Directives;

			ASTNodeKind Kind = ASTNodeKind::InlineFragment;

			GraphQLSelectionSet SelectionSet;

			GraphQLNamedType TypeCondition;
		};
	}
}
