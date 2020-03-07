#pragma once

namespace GraphQL {
	namespace Types {
		enum DirectiveLocation {
			Query,
			Mutation,
			Subscription,
			Field,
			FragmentDescription,
			FragmentSpread,
			InlineFragment,

			Schema,
			Scalar,
			Object,
			FieldDefinition,
			ArgumentDefinition,
			Interface,
			Union,
			Enum,
			EnumValue,
			InputObject,
			InputFieldDefinition
		};

		class DirectiveGraphType {
		public:

		};
	}
}
