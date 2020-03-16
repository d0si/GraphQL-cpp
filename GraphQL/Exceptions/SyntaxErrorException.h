#pragma once

#include <exception>
#include <string>
#include <GraphQL/Parser/Source.h>

namespace GraphQL {
    namespace Exceptions {
        class SyntaxErrorException : public std::exception {
        public:
            SyntaxErrorException(std::string description, Parser::Source source, int location);

        private:
            std::string compose_message(std::string description, Parser::Source source, int loc) const;
        };
    }
}
