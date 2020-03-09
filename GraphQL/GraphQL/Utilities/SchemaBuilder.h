#pragma once

#include <string>
#include <GraphQL/Types/ISchema.h>
#include <GraphQLParser/AST/GraphQLDocument.h>
#include <GraphQL/Types/IObjectGraphType.h>

namespace GraphQL {
	namespace Utilities {
		class SchemaBuilder {
		public:
			GraphQL::Types::ISchema* Build(std::string type_definitions);

		private:
			GraphQLParser::AST::GraphQLDocument Parse(std::string document);

			void Validate(GraphQLParser::AST::GraphQLDocument document);

			Types::ISchema* BuildSchemaFrom(GraphQLParser::AST::GraphQLDocument document);

			void PreConfigure(Types::ISchema* schema);


			Types::IObjectGraphType* ToObjectGraphType(GraphQLObjectTypeDefinition ast_type, bool is_extension_type = false);
		};
	}
}
