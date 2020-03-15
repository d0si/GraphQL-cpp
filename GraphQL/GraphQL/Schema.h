#pragma once

#include <string>

namespace GraphQL {
	class Schema {

	public:
		static void parse(std::string definitions);
	};
}