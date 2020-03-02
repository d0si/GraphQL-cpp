#pragma once

#include <GraphQLParser/AST/GraphQLInlineFragment.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLFragmentDefinition : public GraphQLInlineFragment {
		public:
			ASTNodeKind Kind = ASTNodeKind::FragmentDefinition;

			GraphQLName Name;
		};
	}
}
