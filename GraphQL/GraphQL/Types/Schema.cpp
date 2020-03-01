#include <GraphQL/Types/Schema.h>

namespace GraphQL {
	namespace Types {
		ISchema Schema::For(std::string type_definitions) {
			auto builder = Utilities::SchemaBuilder();

			return builder.Build(type_definitions);
		}
	}

	void run() {
		Types::Schema::For("type Query { hello: String }");
	}
}
