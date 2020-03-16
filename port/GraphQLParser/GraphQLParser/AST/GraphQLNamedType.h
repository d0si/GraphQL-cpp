#pragma once

#include <string>
#include <GraphQLParser/AST/GraphQLType.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLNamedType : public GraphQLType {
		public:
			GraphQLNamedType();
			GraphQLNamedType(std::shared_ptr<GraphQLName> name);

			std::shared_ptr<GraphQLName> Name;

			std::string to_string() const;
		};
	}
}
