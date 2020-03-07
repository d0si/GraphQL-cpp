#include "pch.h"
#include "CppUnitTest.h"
#include <GraphQL/Types/Schema.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GraphQL;

namespace GraphQLTests {
	namespace Utilities {
		TEST_CLASS(SchemaBuilderTests) {
		public:
			TEST_METHOD(should_set_query_by_name) {
				std::string definitions = R"(
type Query {
	id: String
}
)";

				auto schema = Types::Schema::For(definitions);
				schema.Initialize();

				auto query = schema.Query;
				Assert::IsNotNull(query);
				Assert::AreEqual(std::string("Query"), querty->Name);
				Assert::IsTrue(query->Fields.size() == 1);

				Assert::AreEqual(std::string("id"), query->Fields[0]->Name);
			}
		};
	}
}
