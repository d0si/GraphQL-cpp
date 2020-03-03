#include "pch.h"
#include "CppUnitTest.h"
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/AST/GraphQLOperationDefinition.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphQLParserTests
{
	TEST_CLASS(ParserTests)
	{
	public:

		TEST_METHOD(Comments_on_SelectionSet_Should_Read_Correctly)
		{
			GraphQLParser::Lexer lexer;
			GraphQLParser::Parser parser(lexer);
			/*GraphQLParser::AST::GraphQLDocument document = parser.Parse(GraphQLParser::Source(R"(
query {
	# a comment below query
	field1
	field2
	# second comment
	field3
}
)"));*/

			//Assert::IsTrue(document.Definitions.size() == 1);
			//GraphQLParser::AST::GraphQLOperationDefinition def = document.Definitions[0];
		}
	};
}
