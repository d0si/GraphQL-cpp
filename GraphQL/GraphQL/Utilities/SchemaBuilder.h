#pragma once

#include <string>
#include <GraphQL/Types/Schema.h>
#include <GraphQLParser/AST/GraphQLDocument.h>

namespace GraphQL {
	namespace Utilities {
		class SchemaBuilder {
		public:
			Types::ISchema Build(std::string type_definitions);

			GraphQLParser::AST::GraphQLDocument Parse(std::string document);
		};
	}
}
