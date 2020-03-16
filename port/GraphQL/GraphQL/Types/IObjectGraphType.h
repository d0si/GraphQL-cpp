#pragma once

#include <GraphQL/Types/IComplexGraphType.h>
#include <GraphQL/Types/IComplexGraphType.h>

namespace GraphQL {
	namespace Types {
		class IObjectGraphType : IComplexGraphType {
		public:
			bool (*IsTypeOf)(void* /*object*/);

			void AddResolvedInterface(IInterfaceGraphType graph_type);
		};
	}
}
