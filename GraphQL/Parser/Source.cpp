#include <GraphQL/Parser/Source.h>
#include <regex>

namespace GraphQL {
    namespace Parser {
        Source::Source(const std::string& body) : Source(body, "GraphQL") {

        }

        Source::Source(const std::string& body, const std::string& name) : body(monetize_line_breaks(body)), name(name) {

        }

        std::string Source::monetize_line_breaks(const std::string& input) const {
            return std::regex_replace(std::regex_replace(input, std::regex("\r\n"), "\n"), std::regex("\r"), "\n");
        }
    }
}
