#pragma once

#include <string>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLName : public ASTNode {
		public:
			GraphQLName();
			GraphQLName(std::string value);

			std::string Value;
		};
	}
}
