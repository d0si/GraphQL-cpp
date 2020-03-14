#include <GraphQLParser/AST/GraphQLDirectiveDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLDirectiveDefinition::GraphQLDirectiveDefinition() : GraphQLTypeDefinition(ASTNodeKind::DirectiveDefinition), Repeatable(false) {

		}

		GraphQLDirectiveDefinition::GraphQLDirectiveDefinition(std::shared_ptr<GraphQLName> name, bool repeatable, std::vector<GraphQLInputValueDefinition> arguments, std::vector<std::shared_ptr<GraphQLName>> locations)
			: GraphQLTypeDefinition(ASTNodeKind::DirectiveDefinition, name), Arguments(arguments), Locations(locations), Repeatable(repeatable) {

		}
	}
}
