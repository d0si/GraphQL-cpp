#pragma once

namespace GraphQL {
	namespace Types {
		class IObjectGraphType {
		public:
			bool (*IsTypeOf)(void* /*object*/);

			void AddResolvedInterface(IInterfaceGraphType graph_type);
		};
	}
}
