#pragma once

#include <string>

namespace GraphQL {
    namespace Parser {
        class Source {
        public:
            const std::string body;
            const std::string name;

            Source(const std::string& body);
            Source(const std::string& body, const std::string& name);

        private:
            std::string monetize_line_breaks(const std::string& input) const;
        };
    }
}
