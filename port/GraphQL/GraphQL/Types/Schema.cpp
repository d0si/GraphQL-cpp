#include <GraphQL/Types/Schema.h>
#include <GraphQL/Utilities/SchemaBuilder.h>

namespace GraphQL {
	namespace Types {
		Schema::Schema() {

		}

		ISchema* Schema::For(std::string type_definitions) {
			auto builder = Utilities::SchemaBuilder();

			return builder.Build(type_definitions);
		}




		/*void Schema::Initialize() {
			FindType("____");
		}*/



		/*IGraphType Schema::FindType(std::string name) {
			
		}*/


	}
}
