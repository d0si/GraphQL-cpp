#include "pch.h"
#include "CppUnitTest.h"
#include <GraphQLParser/Source.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GraphQLParser;

namespace GraphQLParserTests {
	TEST_CLASS(SourceTests) {
	public:
		TEST_METHOD(CreateSourceFromString_BodyEqualsToProvidedSource) {
			auto source = Source("somesrc");

			Assert::AreEqual(std::string("somesrc"), source.Body);
		}

		TEST_METHOD(CreateSourceFromString_SourceNameEqualsToGraphQL) {
			auto source = Source("somesrc");

			Assert::AreEqual(std::string("GraphQL"), source.Name);
		}

		TEST_METHOD(CreateSourceFromStringWithName_SourceNameEqualsToProvidedName) {
			auto source = Source("somesrc", "somename");

			Assert::AreEqual(std::string("somename"), source.Name);
		}
	};
}
