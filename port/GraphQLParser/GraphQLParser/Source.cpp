#include <GraphQLParser/Source.h>
#include <regex>

namespace GraphQLParser {
	Source::Source(const std::string& body) : Source(body, "GraphQL") {
		
	}

	Source::Source(const std::string& body, const std::string& name) : Name(name), Body(monetize_line_breaks(body)) {

	}

	std::string Source::monetize_line_breaks(const std::string& input) const {
		return std::regex_replace(std::regex_replace(input, std::regex("\r\n"), "\n"), std::regex("\r"), "\n");
	}
}
