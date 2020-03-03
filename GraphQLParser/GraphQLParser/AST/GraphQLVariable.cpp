#include <GraphQLParser/AST/GraphQLVariable.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLVariable::GraphQLVariable(GraphQLName name)
			: GraphQLValue(ASTNodeKind::Variable), Name(name) {

		}
	}
}
