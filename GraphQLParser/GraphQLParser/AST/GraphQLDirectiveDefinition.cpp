#include <GraphQLParser/AST/GraphQLDirectiveDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLDirectiveDefinition::GraphQLDirectiveDefinition() : GraphQLTypeDefinition(ASTNodeKind::DirectiveDefinition), Repeatable(false) {

		}

		GraphQLDirectiveDefinition::GraphQLDirectiveDefinition(GraphQLName name, bool repeatable, std::vector<GraphQLInputValueDefinition> arguments, std::vector<GraphQLName> locations)
			: GraphQLTypeDefinition(ASTNodeKind::DirectiveDefinition, name), Arguments(arguments), Locations(locations) {

		}
	}
}
