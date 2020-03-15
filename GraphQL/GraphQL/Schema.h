#pragma once

#include <string>
#include <GraphQLParser/AST/GraphQLDocument.h>

namespace GraphQL {
	class Schema {
	private:
		GraphQLParser::AST::GraphQLDocument document_;

	public:
		void parse_definitions(std::string definitions);

	private:
		void validate();

	public:
		static Schema from_definitions(std::string definitions);
	};
}