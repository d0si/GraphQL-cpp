#include <GraphQL/Utilities/SchemaBuilder.h>
#include <set>
#include <GraphQLParser/Lexer1.h>
#include <GraphQLParser/Parser.h>
#include <GraphQLParser/Source.h>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLTypeExtensionDefinition.h>
#include <GraphQLParser/AST/GraphQLSchemaDefinition.h>
#include <GraphQLParser/AST/GraphQLInterfaceTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLEnumTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLUnionTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLInputObjectTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirectiveDefinition.h>
#include <GraphQL/Types/Schema.h>
#include <GraphQL/Types/DirectiveGraphType.h>

namespace AST = GraphQLParser::AST;

namespace GraphQL {
	namespace Utilities {
		Types::ISchema* SchemaBuilder::Build(std::string type_definitions) {
			auto document = Parse(type_definitions);

			Validate(document);

			return BuildSchemaFrom(document);
		}

		GraphQLParser::AST::GraphQLDocument SchemaBuilder::Parse(std::string document) {
			auto parser = GraphQLParser::Parser(GraphQLParser::Lexer());

			return parser.Parse(GraphQLParser::Source(document));
		}

		void SchemaBuilder::Validate(GraphQLParser::AST::GraphQLDocument document) {
			std::set<std::string> definitions;
			std::set<std::string> duplicates;
			
			for (auto def : document.Definitions) {
				if (def->Kind == GraphQLParser::AST::ASTNodeKind::TypeExtensionDefinition) {
					auto definition = static_cast<GraphQLParser::AST::GraphQLTypeExtensionDefinition*>(def);
					auto definition_name = definition->Name.Value;
					
					if (definitions.count(definition_name) > 0) {
						duplicates.insert(definition_name);
					}
					else {
						definitions.insert(definition_name);
					}
				}
			}

			if (duplicates.size() > 0) {
				std::string error_mesasge = "All types within a GraphQL schema must have unique names. Following types were redefined: ";
				for (auto e : duplicates) {
					error_mesasge += e + ", ";
				}
				error_mesasge = error_mesasge.substr(0, error_mesasge.length() - 2);

				throw std::exception(error_mesasge.c_str());
			}
		}

		Types::ISchema* SchemaBuilder::BuildSchemaFrom(GraphQLParser::AST::GraphQLDocument document) {
			// TODO: Directives

			auto schema = new Types::Schema(/*ServiceProvider*/);

			PreConfigure(schema);

			auto directives = std::vector<Types::DirectiveGraphType*>();

			AST::GraphQLSchemaDefinition* schema_def = nullptr;

			for (auto def : document.Definitions) {
				switch (def->Kind) {
				case AST::ASTNodeKind::SchemaDefinition:
					schema_def = static_cast<AST::GraphQLSchemaDefinition*>(def);
					//schema->SetAstType(schema_def);

					VisitNode(schema, [](cdasmklc) {});

					break;
				case AST::ASTNodeKind::ObjectTypeDefinition:
					auto type = ToObjectGraphType(static_cast<AST::GraphQLObjectTypeDefinition*>(def));
					_types[type->Name] = type;

					break;
				case AST::ASTNodeKind::TypeExtensionDefinition:
					auto type = ToObjectGraphType(static_cast<AST::GraphQLTypeExtensionDefinition*>(def)->Definition, true);
					_types[type->Name] = type;

					break;
				case AST::ASTNodeKind::InterfaceTypeDefinition:
					auto type = ToInterfaceType(static_cast<AST::GraphQLInterfaceTypeDefinition*>(def));
					_types[type->Name] = type;

					break;
				case AST::ASTNodeKind::EnumTypeDefinition:
					auto type = ToEnumerationType(static_cast<AST::GraphQLEnumTypeDefinition*>(def));
					_types[type->Name] = type;

					break;
				case AST::ASTNodeKind::UnionTypeDefinition:
					auto type = ToUnionType(static_cast<AST::GraphQLUnionTypeDefinition*>(def));
					_types[type->Name] = type;

					break;
				case AST::ASTNodeKind::InputObjectTypeDefinition:
					auto type = ToInputObjectType(static_cast<AST::GraphQLInputObjectTypeDefinition*>(def));
					_types[type->Name] = type;

					break;
				case AST::ASTNodeKind::DirectiveDefinition:
					auto directive = ToDirective(static_cast<AST::GraphQLDirectiveDefinition*>(def));
					directives.push_back(directive);

					break;
				}
			}

			if (schema_def != nullptr) {
				for (auto operation_type_def : schema_def->OperationTypes) {
					auto type_name = operation_type_def.Type.Name.Value;
					auto type = static_cast<Types::IObjectGraphType*>(GetType(type_name));

					switch (operation_type_def.Operation) {
					case AST::OperationType::Query:
						schema.Query = type;

						break;
					case AST::OperationType::Mutation:
						schema.Mutation = type;

						break;
					case AST::OperationType::Subscription:
						schema.Subscription = type;

						break;
					default:
						throw std::exception("Unknown operation type " + operation_type_def.Operation);
					}
				}
			}
			else {
				schema.Query = static_cast<Types::IObjectGraphType*>(GetType("Query"));
				schema.Mutation = static_cast<Types::IObjectGraphType*>(GetType("Mutation"));
				schema.Subscription = static_cast<Types::IObjectGraphType*>(GetType("Subscription"));
			}

			auto type_list = _types.Values.ToArray();
			type_list.Apply(schema.RegisterType);
			schema.RegisterDirectives(directives);

			return schema;
		}

		void SchemaBuilder::PreConfigure(Types::ISchema* schema) {

		}



	}
}
