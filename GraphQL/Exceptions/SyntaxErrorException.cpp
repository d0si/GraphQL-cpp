#include <GraphQL/Exceptions/SyntaxErrorException.h>
#include <GraphQL/Parser/Location.h>

namespace GraphQL {
    namespace Exceptions {
        SyntaxErrorException::SyntaxErrorException(std::string description, Parser::Source source, int location)
            : std::exception(compose_message(description, source, location).c_str()) {

        }

        std::string SyntaxErrorException::compose_message(std::string description, Parser::Source source, int loc) const {
            Parser::Location location(source, loc);

            return "Syntax Error GraphQL (" + std::to_string(location.get_line()) + ":" + std::to_string(location.get_column()) + ") " + description;
        }
    }
}
