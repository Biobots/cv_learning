add_requires("glfw", "glew")

target("rt_gpu")
	set_kind("binary")
	add_packages("glew", "glfw")
	add_files("*.cpp")
	add_includedirs("core")