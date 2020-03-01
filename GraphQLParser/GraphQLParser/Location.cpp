#include <GraphQLParser/Location.h>
#include <regex>

namespace GraphQLParser {
	Location::Location(Source source, int position) {
		Line = 1;
		Column = position + 1;

		std::cmatch cm;
		std::regex_match(source.Body.c_str(), cm, std::regex("\r\n|[\n\r]"), std::regex_constants::match_default);
		for (int i = 0; i < cm.size(); ++i) {
			if (i >= position)
				break;

			++Line;
			Column = position + 1 - (i + cm[0].length()); // Not sure if this will work
		}
	}
}
