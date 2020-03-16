#include <GraphQL/Types/DirectiveGraphType.h>

namespace GraphQL {
	namespace Types {
		DirectiveGraphType::DirectiveGraphType(std::string name, std::vector<DirectiveLocation> locations)
			: Name(name), Locations(locations) {
			if (Locations.size() == 0) {
				throw std::exception("Argument Exception: Directive must have locations");
			}
		}
	}
}
