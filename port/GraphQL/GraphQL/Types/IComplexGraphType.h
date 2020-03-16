#pragma once

#include <vector>
#include <string>
#include <GraphQL/Types/IGraphType.h>

namespace GraphQL {
	namespace Types {
		class IComplexGraphType : public IGraphType {
			std::vector<FieldType> Fields;

			FieldType AddField(FieldType field_type);

			bool HasField(std::string name);

			FieldType GetField(std::string name);
		};
	}
}
