#pragma once

#include <GraphQLParser/Source.h>

namespace GraphQLParser {
	class LexerContext {
	private:
		int current_index;
		const Source source;

	public:
		LexerContext(Source source, int index);
	};
}
