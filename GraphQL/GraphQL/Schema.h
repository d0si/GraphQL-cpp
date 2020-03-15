#pragma once

#include <string>

namespace GraphQL {
	class Schema {

	public:
		static Schema parse(std::string definitions);
	};
}