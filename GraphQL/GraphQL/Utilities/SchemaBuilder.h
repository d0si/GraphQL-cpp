#pragma once

#include <string>
#include <GraphQL/Types/ISchema.h>
#include <GraphQLParser/AST/GraphQLDocument.h>

namespace GraphQL {
	namespace Utilities {
		class SchemaBuilder {
		public:
			GraphQL::Types::ISchema Build(std::string type_definitions);

			GraphQLParser::AST::GraphQLDocument Parse(std::string document);

			void Validate(GraphQLParser::AST::GraphQLDocument document);
		};
	}
}
