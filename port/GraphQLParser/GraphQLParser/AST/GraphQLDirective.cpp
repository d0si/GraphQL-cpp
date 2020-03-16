#include <GraphQLParser/AST/GraphQLDirective.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLDirective::GraphQLDirective() : ASTNode(ASTNodeKind::Directive) {

		}

		GraphQLDirective::GraphQLDirective(std::shared_ptr<GraphQLName> name) : GraphQLDirective(name, std::vector<GraphQLArgument>()) {

		}

		GraphQLDirective::GraphQLDirective(std::shared_ptr<GraphQLName> name, std::vector<GraphQLArgument> arguments)
			: ASTNode(ASTNodeKind::Directive), Name(name), Arguments(arguments) {

		}
	}
}
