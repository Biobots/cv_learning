add_requires("glfw", "glew")

target("gl")
	set_kind("binary")
	add_packages("glew", "glfw")
	add_files("*.cpp")
	if is_plat("windows") then
    	add_cxflags("-MDd")
    	add_ldflags("-nodefaultlib:msvcrt.lib")
	end