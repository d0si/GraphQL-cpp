#pragma once

#include <string>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLName : public ASTNode {
		public:
			ASTNodeKind Kind = ASTNodeKind::Name;

			std::string Value;
		};
	}
}
