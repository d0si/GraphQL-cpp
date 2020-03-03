#pragma once

#include <GraphQLParser/AST/GraphQLInlineFragment.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLFragmentDefinition : public GraphQLInlineFragment {
		public:
			GraphQLFragmentDefinition();
			GraphQLFragmentDefinition(GraphQLName name, GraphQLNamedType type_condition, std::vector<GraphQLDirective> directives, GraphQLSelectionSet selection_set);

			GraphQLName Name;
		};
	}
}
