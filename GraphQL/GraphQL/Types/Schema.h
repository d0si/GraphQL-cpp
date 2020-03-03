#pragma once

#include <string>
#include <GraphQL/Types/ISchema.h>

namespace GraphQL {
	namespace Types {
		class Schema : public ISchema {
		public:
			static ISchema For(std::string type_definitions);
		};
	}
}
