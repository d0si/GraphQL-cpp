#include <GraphQL/Types/Schema.h>
#include <GraphQL/Utilities/SchemaBuilder.h>

namespace GraphQL {
	namespace Types {
		ISchema Schema::For(std::string type_definitions) {
			auto builder = Utilities::SchemaBuilder();

			return builder.Build(type_definitions);
		}
	}
}
