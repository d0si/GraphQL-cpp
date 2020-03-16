#pragma once

#include <GraphQLParser/Source.h>

namespace GraphQLParser {
	class Location {
	public:
		Location(Source source, int position);

		int Column;
		int Line;
	};
}
