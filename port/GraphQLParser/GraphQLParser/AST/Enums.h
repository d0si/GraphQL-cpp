#pragma once

namespace GraphQLParser {
	namespace AST {
        enum class ASTNodeKind {
            Name,
            Document,
            OperationDefinition,
            VariableDefinition,
            Variable,
            SelectionSet,
            Field,
            Argument,
            FragmentSpread,
            InlineFragment,
            FragmentDefinition,
            IntValue,
            FloatValue,
            StringValue,
            BooleanValue,
            EnumValue,
            ListValue,
            ObjectValue,
            ObjectField,
            Directive,
            NamedType,
            ListType,
            NonNullType,
            NullValue,
            SchemaDefinition,
            OperationTypeDefinition,
            ScalarTypeDefinition,
            ObjectTypeDefinition,
            FieldDefinition,
            InputValueDefinition,
            InterfaceTypeDefinition,
            UnionTypeDefinition,
            EnumTypeDefinition,
            EnumValueDefinition,
            InputObjectTypeDefinition,
            TypeExtensionDefinition,
            DirectiveDefinition,
            Comment,
        };

        enum class OperationType {
            Query,
            Mutation,
            Subscription
        };
	}
}
