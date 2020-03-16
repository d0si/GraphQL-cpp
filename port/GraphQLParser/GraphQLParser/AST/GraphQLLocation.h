#pragma once

namespace GraphQLParser {
	namespace AST {
		class GraphQLLocation {
		public:
			GraphQLLocation(int start, int end);

			int End;
			int Start;
		};
	}
}
