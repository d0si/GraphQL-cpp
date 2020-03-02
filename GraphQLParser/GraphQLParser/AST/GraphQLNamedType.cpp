#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		std::string GraphQLNamedType::to_string() {
			return Name.Value;
		}
	}
}
