#pragma once

namespace GraphQLParser {
	namespace AST {
		class GraphQLLocation {
		public:
			GraphQLLocation(int start, int end) : End(end), Start(start) {
				
			}

			int End;
			int Start;
		};
	}
}
