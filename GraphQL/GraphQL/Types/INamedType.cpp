#include <GraphQL/Types/INamedType.h>

namespace GraphQL {
	namespace Types {
		void INamedType::set_name(const std::string& name) {
			this->name = name;
		}

		std::string INamedType::get_name() const {
			return this->name;
		}
	}
}
