#pragma once

namespace GraphQL {
	namespace Types {
		class ISchema {
		public:
			bool Initialized = false;

			void Initialize();


			
			/*IFieldNameConverter FieldNameConverter{ get; set; }*/
			IObjectGraphType* Query;
			IObjectGraphType* Mutation;
			IObjectGraphType* Subscription;
			/*IEnumerable<DirectiveGraphType> Directives{ get; set; }
			IEnumerable<IGraphType> AllTypes{ get; }
			IGraphType FindType(string name);
			DirectiveGraphType FindDirective(string name);
			IEnumerable<Type> AdditionalTypes{ get; }
			void RegisterType(IGraphType type);
			void RegisterTypes(params IGraphType[] types);
			void RegisterTypes(params Type[] types);
			void RegisterType<T>() where T : IGraphType;
			void RegisterDirective(DirectiveGraphType directive);
			void RegisterDirectives(params DirectiveGraphType[] directives);
			void RegisterValueConverter(IAstFromValueConverter converter);
			IAstFromValueConverter FindValueConverter(object value, IGraphType type);
			ISchemaFilter Filter{ get; set; }*/
		};
	}
}
