#include <GraphQLParser/AST/GraphQLVariable.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLVariable::GraphQLVariable(std::shared_ptr<GraphQLName> name)
			: GraphQLValue(ASTNodeKind::Variable), Name(name) {

		}
	}
}
