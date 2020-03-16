#include <GraphQL/Parser/Location.h>
#include <regex>

namespace GraphQL {
    namespace Parser {
        Location::Location(const Source& source, int position) {
            line_ = 1;
            column_ = position + 1;

            std::cmatch cm;
            std::regex_match(source.body.c_str(), cm, std::regex("\r\n|[\n\r]"), std::regex_constants::match_default);
            for (int i = 0; i < cm.size(); ++i) {
                if (i >= position)
                    break;

                ++line_;
                column_ = position + 1 - (i + cm[0].length()); // Test this part of code
            }
        }

        int Location::get_column() const {
            return column_;
        }
        
        int Location::get_line() const {
            return line_;
        }
    }
}
