#include <GraphQLParser/AST/GraphQLObjectField.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLObjectField::GraphQLObjectField() : ASTNode(ASTNodeKind::ObjectField) {

		}

		GraphQLObjectField::GraphQLObjectField(GraphQLName name, GraphQLValue* value) : ASTNode(ASTNodeKind::ObjectField), Name(name), Value(value) {

		}
	}
}
