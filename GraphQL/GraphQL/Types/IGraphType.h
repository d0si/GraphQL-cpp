#pragma once

#include <string>
#include <GraphQL/Types/INamedType.h>

namespace GraphQL {
	namespace Types {
		class IGraphType : public INamedType {
		private:
			std::string description;
			std::string deprecation_reason;
			
		public:

			virtual std::string collect_types(TypeCollectionContext context) = 0;
		};
	}
}
