#pragma once

#include <string>

namespace GraphQLParser {
	class Source {
	public:
		Source(std::string body);
		Source(std::string body, std::string name);

		std::string Body;
		std::string Name;

	private:
		static std::string monetize_line_breaks(std::string input);
	};
}
