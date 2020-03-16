#pragma once

#include <exception>
#include <string>
#include <GraphQLParser/Source.h>

namespace GraphQLParser {
	namespace Exceptions {
		class GraphQLSyntaxErrorException : public std::exception {
		public:
			GraphQLSyntaxErrorException(std::string description, Source source, int location);

		private:
			std::string ComposeMessage(std::string description, Source source, int loc);
		};
	}
}
