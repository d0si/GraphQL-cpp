#include "pch.h"
#include "CppUnitTest.h"
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/AST/GraphQLOperationDefinition.h>
#include <GraphQLParser/AST/GraphQLComment.h>
#include <GraphQLParser/AST/GraphQLEnumTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLInputObjectTypeDefinition.h>
#include <GraphQLParser/Exceptions/GraphQLSyntaxErrorException.h>
#include <GraphQLParser/AST/GraphQLObjectTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLSchemaDefinition.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GraphQLParser;

namespace GraphQLParserTests {
	TEST_CLASS(ParserTests) {
	public:

		TEST_METHOD(Comments_on_SelectionSet_Should_Read_Correctly) {
			AST::GraphQLDocument document = Parser().Parse(Source(R"(
query {
	# a comment below query
	field1
	field2
	#second comment
	field3
}
)"));

			Assert::IsTrue(document.Definitions.size() == 1);
			Assert::IsTrue(document.Definitions[0]->Kind == AST::ASTNodeKind::OperationDefinition);
			auto def = std::static_pointer_cast<AST::GraphQLOperationDefinition>(document.Definitions[0]);
			Assert::IsTrue(def->SelectionSet.Selections.size() == 3);
			Assert::IsTrue(def->SelectionSet.Selections[0].Comment != nullptr);
			Assert::AreEqual(def->SelectionSet.Selections[0].Comment->Text, std::string(" a comment below query"));
			Assert::IsTrue(def->SelectionSet.Selections[1].Comment == nullptr);
			Assert::IsTrue(def->SelectionSet.Selections[2].Comment != nullptr);
			Assert::AreEqual(def->SelectionSet.Selections[2].Comment->Text, std::string("second comment"));
		}

		TEST_METHOD(Comments_On_Enums_Should_Read_Correctly) {
			AST::GraphQLDocument document = Parser().Parse(Source(R"(
# different animals
enum Animal {
    #a cat
    Cat
    #a dog
    Dog
    Octopus
    #bird is the word
    Bird
}

input Parameter {
	#any value
	Value: String
}

scalar JSON
)"));

			Assert::IsTrue(document.Definitions.size() == 3);
			Assert::IsTrue(document.Definitions[0]->Kind == AST::ASTNodeKind::EnumTypeDefinition);
			auto d1 = std::static_pointer_cast<AST::GraphQLEnumTypeDefinition>(document.Definitions[0]);
			Assert::AreEqual(d1->Name.Value, std::string("Animal"));
			Assert::AreEqual(d1->Comment != nullptr ? d1->Comment->Text : "", std::string(" different animals"));
			Assert::IsTrue(d1->Values.size() == 4);
			Assert::AreEqual(d1->Values[0].Name.Value, std::string("Cat"));
			Assert::AreEqual(d1->Values[0].Comment != nullptr ? d1->Values[0].Comment->Text : "", std::string("a cat"));
			Assert::AreEqual(d1->Values[1].Name.Value, std::string("Dog"));
			Assert::AreEqual(d1->Values[2].Name.Value, std::string("Octopus"));
			Assert::IsTrue(d1->Values[2].Comment == nullptr);
			Assert::AreEqual(d1->Values[3].Name.Value, std::string("Bird"));

			auto d2 = std::static_pointer_cast<AST::GraphQLInputObjectTypeDefinition>(document.Definitions[1]);
			Assert::AreEqual(d2->Name.Value, std::string("Parameter"));
			Assert::IsTrue(d2->Comment == nullptr);
			Assert::IsTrue(d2->Fields.size() == 1);
			Assert::AreEqual(d2->Fields[0].Comment != nullptr ? d2->Fields[0].Comment->Text : "", std::string("any value"));
		}

		TEST_METHOD(Parse_Unicode_Char_At_EOF_Should_Throw) {
			Assert::ExpectException<Exceptions::GraphQLSyntaxErrorException>([]() {
				Parser().Parse(Source("{\"\\ue }"));
			});
		}

		TEST_METHOD(Parse_FieldInput) {
			auto document = ParseGraphQLFieldSource();

			Assert::IsTrue(document.Location.Start == 0);
			Assert::IsTrue(document.Location.End == 9);
			Assert::IsTrue(document.Definitions[0]->Kind == AST::ASTNodeKind::OperationDefinition);
		}

		TEST_METHOD(Parse_FieldInput_NameIsNull) {
			auto document = ParseGraphQLFieldSource();

			Assert::IsTrue(GetSingleOperationDefinition(document)->Name.Value.length() == 0);
		}

		TEST_METHOD(Parse_FieldInput_OperationIsQuery) {
			auto document = ParseGraphQLFieldSource();

			Assert::IsTrue(GetSingleOperationDefinition(document)->Operation == AST::OperationType::Query);
		}

		TEST_METHOD(Parse_FieldInput_ReturnsDocumentNode) {
			auto document = ParseGraphQLFieldSource();

			Assert::IsTrue(document.Kind == AST::ASTNodeKind::Document);
		}

		TEST_METHOD(Parse_FieldInput_SelectionSetContainsSingleFieldSelection) {
			auto document = ParseGraphQLFieldSource();

			Assert::IsTrue(GetSingleSelection(document).Kind == AST::ASTNodeKind::Field);
		}

		TEST_METHOD(Parse_FieldWithOperationTypeAndNameInput_HasCorrectEndLocationAttribute) {
			auto document = ParseGraphQLFieldWithOperationTypeAndNameSource();

			Assert::IsTrue(document.Location.End == 22);
			Assert::IsTrue(document.Location.Start == 0);
			Assert::IsTrue(document.Definitions[0]->Kind == AST::ASTNodeKind::OperationDefinition);
		}

		TEST_METHOD(Parse_FieldWithOperationTypeAndNameInput_NameIsSet) {
			auto document = ParseGraphQLFieldWithOperationTypeAndNameSource();

			Assert::AreEqual(std::string("Foo"), GetSingleOperationDefinition(document)->Name.Value);
		}

		TEST_METHOD(Parse_FieldWithOperationTypeAndNameInput_OperationIsQuery) {
			auto document = ParseGraphQLFieldWithOperationTypeAndNameSource();

			Assert::IsTrue(GetSingleOperationDefinition(document)->Operation == AST::OperationType::Mutation);
		}

		TEST_METHOD(Parse_FieldWithOperationTypeAndNameInput_ReturnsDocumentNode) {
			auto document = ParseGraphQLFieldWithOperationTypeAndNameSource();

			Assert::IsTrue(document.Kind == AST::ASTNodeKind::Document);
		}

		TEST_METHOD(Parse_FieldWithOperationTypeAndNameInput_SelectionSetContainsSingleFieldWithOperationTypeAndNameSelection) {
			auto document = ParseGraphQLFieldWithOperationTypeAndNameSource();

			Assert::IsTrue(GetSingleSelection(document).Kind == AST::ASTNodeKind::Field);
		}

		TEST_METHOD(Parse_KitchenSink_DoesNotThrowError) {
			auto document = Parser().Parse(Source(LoadKitchenSink()));
			
			for (auto def : document.Definitions) {
				if (def->Kind == AST::ASTNodeKind::ObjectTypeDefinition) {
					auto type_def = std::static_pointer_cast<AST::GraphQLObjectTypeDefinition>(def);
					auto field_def = type_def->Fields[2];

					Assert::AreEqual(std::string("Foo"), type_def->Name.Value);
					Assert::AreEqual(std::string("three"), field_def.Name.Value);
					Assert::AreEqual(std::string(" multiline comments\n with very importand description #\n # and symbol # and ##"), field_def.Comment->Text);

					break;
				}
			}

			for (auto def : document.Definitions) {
				if (def->Kind == AST::ASTNodeKind::SchemaDefinition) {
					auto definition = std::static_pointer_cast<AST::GraphQLSchemaDefinition>(def);
					const std::string compare = " Copyright (c) 2015, Facebook, Inc.";

					Assert::IsTrue(definition->Comment != nullptr);
					Assert::IsTrue(definition->Comment->Text.length() > 0);
					Assert::AreEqual(definition->Comment->Text.substr(0, compare.length()), compare);

					break;
				}
			}
		}

		TEST_METHOD(Parse_NullInput_EmptyDocument) {
			auto document = Parser().Parse(Source(""));

			Assert::IsTrue(document.Definitions.size() == 0);
		}

		TEST_METHOD(Parse_VariableInlineValues_DoesNotThrowError) {
			Parser().Parse(Source("{ field(complex: { a: { b: [ $var ] } }) }"));
		}

	private:
		AST::GraphQLDocument ParseGraphQLFieldSource() {
			return Parser().Parse(Source("{ field }"));
		}

		std::shared_ptr<AST::GraphQLOperationDefinition> GetSingleOperationDefinition(AST::GraphQLDocument document) {
			return std::static_pointer_cast<AST::GraphQLOperationDefinition>(document.Definitions[0]);
		}

		AST::ASTNode GetSingleSelection(AST::GraphQLDocument document) {
			return GetSingleOperationDefinition(document)->SelectionSet.Selections[0];
		}

		AST::GraphQLDocument ParseGraphQLFieldWithOperationTypeAndNameSource() {
			return Parser().Parse(Source("mutation Foo { field }"));
		}

		const std::string LoadKitchenSink() {
			return R"(# Copyright (c) 2015, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.

query queryName($foo: ComplexType, $site: Site = MOBILE) {
  whoever123is: node(id: [123, 456]) {
    id ,
    ... on User @defer {
      field2 {
        id ,
        alias: field1(first:10, after:$foo,) @include(if: $foo) {
          id,
          ...frag
        }
      }
    }
    ... @skip(unless: $foo) {
      id
    }
    ... {
      id
    }
  }
}

mutation updateStory {
  like(story: {id: 123, EndDate: null}) {
    story {
      id
    }
  }
}

mutation likeStory {
  like(story: 123) @defer {
    story {
      id
    }
  }
}

subscription StoryLikeSubscription($input: StoryLikeSubscribeInput) {
  storyLikeSubscribe(input: $input) {
    story {
      likers {
        count
      }
      likeSentence {
        text
      }
    }
  }
}

fragment frag on Friend {
  foo(size: $size, bar: $b, obj: {key: "value"})
}

{
  unnamed(truthy: true, falsey: false),
  query
    }

# Copyright (c) 2015, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.

schema {
  query: QueryType
  mutation: MutationType
}

type Foo implements Bar
{
  # comment 1
  one: Type
  # comment 2
  two(argument: InputType!): Type
  # multiline comments
  # with very importand description #
  # # and symbol # and ##
  three(argument: InputType, other: String): Int
  four(argument: String = "string"): String
  five(argument: [String] = ["string", "string"]): String
  six(argument: InputType = { key: "value"}): Type
}

type AnnotatedObject @onObject(arg: "value")
{
    # a comment
    annotatedField(arg: Type = "default" @onArg): Type @onField
}

interface Bar
{
    one: Type
    four(argument: String = "string"): String
}

interface AnnotatedInterface @onInterface {
  annotatedField(arg: Type @onArg): Type @onField
}

union Feed = Story | Article | Advert

union AnnotatedUnion @onUnion = A | B

scalar CustomScalar

scalar AnnotatedScalar @onScalar

enum Site
{
    DESKTOP
  MOBILE
}

enum AnnotatedEnum @onEnum {
  ANNOTATED_VALUE @onEnumValue
  OTHER_VALUE
}

input InputType
{
    key: String!
  answer: Int = 42
}

input AnnotatedInput @onInputObjectType {
  annotatedField: Type @onField
}

extend type Foo {
  seven(argument: [String]): Type
}

extend type Foo @onType { }

type NoFields { }

directive @skip(if: Boolean!) on FIELD | FRAGMENT_SPREAD | INLINE_FRAGMENT

directive @include(if: Boolean!)
  on FIELD
   | FRAGMENT_SPREAD
   | INLINE_FRAGMENT)";
		}
	};
}
