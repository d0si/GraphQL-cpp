#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLNamedType::GraphQLNamedType() : GraphQLType(ASTNodeKind::NamedType) {

		}
		
		GraphQLNamedType::GraphQLNamedType(std::shared_ptr<GraphQLName> name) : GraphQLType(ASTNodeKind::NamedType), Name(name) {

		}
		
		std::string GraphQLNamedType::to_string() const {
			return Name->Value;
		}
	}
}
