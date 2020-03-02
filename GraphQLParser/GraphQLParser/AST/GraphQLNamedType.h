#pragma once

#include <string>
#include <GraphQLParser/AST/GraphQLType.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLNamedType : public GraphQLType {
		public:
			ASTNodeKind Kind = ASTNodeKind::NamedType;

			GraphQLName Name;

			std::string to_string();
		};
	}
}
