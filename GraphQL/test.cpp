/*
int main() {
	var schema = Schema.For(@"
		type Query{
			hello: String
		}
		");

	var json = await schema.ExecuteAsync(_ => {
		_.Query = "{ hello }";
		_.Root = new { Hello = "Hello World!" };
	});

	Console.WriteLine(json); // { "data": { "hello": "Hello World!" } }
}
*/