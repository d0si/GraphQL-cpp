#include <GraphQLParser/Exceptions/GraphQLSyntaxErrorException.h>
#include <GraphQLParser/Location.h>

namespace GraphQLParser {
	namespace Exceptions {
		GraphQLSyntaxErrorException::GraphQLSyntaxErrorException(std::string description, Source source, int location)	
			: std::exception(ComposeMessage(description, source, location).c_str()) {

		}

		std::string GraphQLSyntaxErrorException::ComposeMessage(std::string description, Source source, int loc) {
			Location location(source, loc);

			return "Syntax Error GraphQL (" + std::to_string(location.Line) + ":" + std::to_string(location.Column) + ") " + description;
		}
	}
}
