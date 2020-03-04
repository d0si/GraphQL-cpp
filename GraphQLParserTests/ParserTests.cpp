#include "pch.h"
#include "CppUnitTest.h"
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/AST/GraphQLOperationDefinition.h>
#include <GraphQLParser/AST/GraphQLComment.h>
#include <GraphQLParser/AST/GraphQLEnumTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLInputObjectTypeDefinition.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GraphQLParser;

namespace GraphQLParserTests
{
	TEST_CLASS(ParserTests)
	{
	public:

		TEST_METHOD(Comments_on_SelectionSet_Should_Read_Correctly)
		{
			Parser parser = Parser(Lexer());
			AST::GraphQLDocument document = parser.Parse(Source(R"(
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
			AST::GraphQLOperationDefinition* def = static_cast<AST::GraphQLOperationDefinition*>(document.Definitions[0]);
			Assert::IsTrue(def->SelectionSet.Selections.size() == 3);
			Assert::IsTrue(def->SelectionSet.Selections[0].Comment != nullptr);
			Assert::AreEqual(def->SelectionSet.Selections[0].Comment->Text, std::string(" a comment below query"));
			Assert::IsTrue(def->SelectionSet.Selections[1].Comment == nullptr);
			Assert::IsTrue(def->SelectionSet.Selections[2].Comment != nullptr);
			Assert::AreEqual(def->SelectionSet.Selections[2].Comment->Text, std::string("second comment"));
		}

		TEST_METHOD(Comments_On_Enums_Should_Read_Correctly) {
			Parser parser = Parser(Lexer());
			AST::GraphQLDocument document = parser.Parse(Source(R"(
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
			AST::GraphQLEnumTypeDefinition* d1 = static_cast<AST::GraphQLEnumTypeDefinition*>(document.Definitions[0]);
			Assert::AreEqual(d1->Name.Value, std::string("Animal"));
			Assert::AreEqual(d1->Comment != nullptr ? d1->Comment->Text : "", std::string(" different animals"));
			Assert::IsTrue(d1->Values.size() == 4);
			Assert::AreEqual(d1->Values[0].Name.Value, std::string("Cat"));
			Assert::AreEqual(d1->Values[0].Comment != nullptr ? d1->Values[0].Comment->Text : "", std::string("a cat"));
			Assert::AreEqual(d1->Values[1].Name.Value, std::string("Dog"));
			Assert::AreEqual(d1->Values[2].Name.Value, std::string("Octopus"));
			Assert::IsTrue(d1->Values[2].Comment == nullptr);
			Assert::AreEqual(d1->Values[3].Name.Value, std::string("Bird"));

			AST::GraphQLInputObjectTypeDefinition* d2 = static_cast<AST::GraphQLInputObjectTypeDefinition*>(document.Definitions[1]);
			Assert::AreEqual(d2->Name.Value, std::string("Parameter"));
			Assert::IsTrue(d2->Comment == nullptr);
			Assert::IsTrue(d2->Fields.size() == 1);
			Assert::AreEqual(d2->Fields[0].Comment != nullptr ? d2->Fields[0].Comment->Text : "", std::string("any value"));
		}
	};
}
