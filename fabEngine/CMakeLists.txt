# Shader files
FILE(GLOB_RECURSE FabEngine_SHADER_SOURCE shader/*.glsl)
source_group("Shaders" FILES ${FabEngine_SHADER_SOURCE})

FILE(GLOB_RECURSE FabEngine_SOURCE_FILES src/*.cpp)
FILE(GLOB_RECURSE FabEngine_HEADER_FILES inc/*.h)

add_executable(FabEngine ${FabEngine_SOURCE_FILES} ${FabEngine_HEADER_FILES} ${FabEngine_SHADER_SOURCE})

# Find dependencies:
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Opengl REQUIRED)
find_package(glew REQUIRED)
find_package(imgui REQUIRED)

set(FabEngine_DEPENDENCIES 
	glm::glm
	GLEW::GLEW
	imgui::imgui
	OpenGL::GL)

set(FabEngine_INCLUDE_DIR
	"{CMAKE_SOURCE_DIR}/fabEngine/inc")
	
target_include_directories(FabEngine PUBLIC FabEngine_INCLUDE_DIR)

target_link_libraries(FabEngine PRIVATE ${FabEngine_DEPENDENCIES})