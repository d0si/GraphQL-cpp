#include <GraphQLParser/Source.h>
#include <regex>

namespace GraphQLParser {
	Source::Source(std::string body) : Source(body, "GraphQL") {
		
	}

	Source::Source(std::string body, std::string name) : Name(name), Body(monetize_line_breaks(body)) {

	}

	std::string Source::monetize_line_breaks(std::string input) {
		return std::regex_replace(std::regex_replace(input, std::regex("\r\n"), "\n"), std::regex("\r"), "\n");
	}
}
