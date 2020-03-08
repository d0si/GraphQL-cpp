#pragma once

#include <string>

namespace GraphQL {
	namespace Types {
		class QueryArgument {
		private:
			Type type;

		public:
			QueryArgument(Type type);

			std::string Name;

			std::string Description;

			// TODO: object
			void* DefaultValue;


		private:
			Type CheckType(Type type);


		};
	}
}
