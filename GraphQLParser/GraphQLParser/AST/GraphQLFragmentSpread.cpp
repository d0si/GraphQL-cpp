#include <GraphQLParser/AST/GraphQLFragmentSpread.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLFragmentSpread::GraphQLFragmentSpread() : ASTNode(ASTNodeKind::FragmentSpread) {

		}

		GraphQLFragmentSpread::GraphQLFragmentSpread(GraphQLName name, std::vector<GraphQLDirective> directives)
			: ASTNode(ASTNodeKind::FragmentSpread), Name(name), Directives(directives) {

		}
	}
}
