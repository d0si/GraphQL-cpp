#pragma once

#include <string>

namespace GraphQL {
	namespace Types {
		class INamedType {
		private:
			std::string name;

		public:

			void set_name(const std::string& name);
			std::string get_name() const;
		};
	}
}
