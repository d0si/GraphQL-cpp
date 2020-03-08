#pragma once

namespace GraphQL {
	namespace Types {
		enum class DirectiveLocation {
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
	}
}
