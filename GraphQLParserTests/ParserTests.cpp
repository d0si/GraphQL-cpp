#include "pch.h"
#include "CppUnitTest.h"
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/AST/GraphQLOperationDefinition.h>
#include <GraphQLParser/AST/GraphQLComment.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GraphQLParser;

namespace GraphQLParserTests
{
	TEST_CLASS(ParserTests)
	{
	public:

		TEST_METHOD(Comments_on_SelectionSet_Should_Read_Correctly)
		{
			Lexer lexer;
			Parser parser(lexer);
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
			AST::ASTNode* definition = document.Definitions[0];
			AST::GraphQLOperationDefinition* def = static_cast<AST::GraphQLOperationDefinition*>(definition);
			Assert::IsTrue(def->SelectionSet.Selections.size() == 3);
			Assert::IsTrue(def->SelectionSet.Selections[0].Comment != nullptr);
			Assert::AreEqual(def->SelectionSet.Selections[0].Comment->Text, std::string(" a comment below query"));
			Assert::IsTrue(def->SelectionSet.Selections[1].Comment == nullptr);
			Assert::IsTrue(def->SelectionSet.Selections[2].Comment != nullptr);
			Assert::AreEqual(def->SelectionSet.Selections[2].Comment->Text, std::string("second comment"));
		}
	};
}
