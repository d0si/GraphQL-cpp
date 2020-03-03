#include <GraphQLParser/AST/GraphQLDirective.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLDirective::GraphQLDirective() : GraphQLDirective(GraphQLName()) {

		}

		GraphQLDirective::GraphQLDirective(GraphQLName name) : GraphQLDirective(name, std::vector<GraphQLArgument>()) {

		}

		GraphQLDirective::GraphQLDirective(GraphQLName name, std::vector<GraphQLArgument> arguments)
			: ASTNode(ASTNodeKind::Directive), Name(name), Arguments(arguments) {

		}
	}
}
