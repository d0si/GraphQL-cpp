#pragma once

#include <string>

namespace GraphQLParser {
	class Source {
	public:
		Source(const std::string& body);
		Source(const std::string& body, const std::string& name);

		std::string Body;
		std::string Name;

	private:
		std::string monetize_line_breaks(const std::string& input) const;
	};
}
