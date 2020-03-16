#pragma once

#include <vector>
#include <string>
#include <GraphQL/Types/DirectiveLocation.h>
#include <GraphQL/Types/QueryArgument.h>

namespace GraphQL {
	namespace Types {
		class DirectiveGraphType {
		public:
			DirectiveGraphType(std::string name, std::vector<DirectiveLocation> locations);
			
			std::string Name;

			std::string Description;

			// TODO: QueryArguments validation
			std::vector<QueryArgument> Arguments;

			std::vector<DirectiveLocation> Locations;
		};
	}
}
