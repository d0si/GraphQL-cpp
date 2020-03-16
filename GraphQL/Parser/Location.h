#pragma once

#include <GraphQL/Parser/Source.h>

namespace GraphQL {
	namespace Parser {
		class Location {
		private:
			int column_;
			int line_;

		public:
			Location(const Source& source, int position);

			int get_column() const;
			int get_line() const;
		};
	}
}
