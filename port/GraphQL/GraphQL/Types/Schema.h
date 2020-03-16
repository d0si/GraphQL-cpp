#pragma once

#include <string>
#include <GraphQL/Types/ISchema.h>

namespace GraphQL {
	namespace Types {
		class Schema : public ISchema {
		public:
			Schema();
			//Schema(/*serviceprovider*/);


			static ISchema* For(std::string type_definitions);


			//void Initialize();

		
		private:
			//IGraphType FindType(std::string name);
		};
	}
}
