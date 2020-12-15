import os

env = Environment(CXXFLAGS=["-std=c++2a", "-O3", "-Wall"], CPPPATH = ["src/"], CXX=os.environ["CXX"], CC=os.environ["CC"])
env.Tool("compilation_db")
env.CompilationDatabase("compile_commands.json")

env.VariantDir("build", "src", duplicate = 0)
env.Program("runner", Glob("build/*.cpp"))
