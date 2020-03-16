#pragma once

#include <memory>
#include <GraphQLParser/AST/Enums.h>
#include <GraphQLParser/AST/GraphQLLocation.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLComment;

		class ASTNode {
		private:
			//GraphQLLocation location_;

		public:
			ASTNode();
			ASTNode(ASTNodeKind kind);
			ASTNode(ASTNodeKind kind, const GraphQLLocation& location);
			ASTNode(ASTNodeKind kind, const GraphQLLocation& location, std::shared_ptr<GraphQLComment> comment);
			~ASTNode();

			ASTNodeKind Kind;
			GraphQLLocation Location;
			std::shared_ptr<GraphQLComment> Comment;

			const GraphQLLocation& get_location() const { return Location; }
		};
	}
}
