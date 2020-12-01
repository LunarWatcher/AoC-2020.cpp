env = Environment(CXXFLAGS=["-std=c++17"], CPPPATH = ["src/"])
env.Tool("compilation_db")
env.CompilationDatabase("compile_commands.json")

env.VariantDir("build", "src", duplicate = 0)
env.Program("runner", Glob("build/*.cpp"))
