
add_library(yooz_gl STATIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glad/gl.c)

target_include_directories(yooz_gl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glad/)

target_link_libraries(Yooz PUBLIC yooz_gl)

target_sources(Yooz PRIVATE

	"Platform/GL/yzBatcher.GL.cpp"
	"Platform/GL/yzGraphicsDevice.GL.cpp"
	"Platform/GL/yzGraphicsFeatures.GL.cpp"
	"Platform/GL/yzRenderer.GL.cpp"
	"Platform/GL/yzShader.GL.cpp"
	"Platform/GL/yzTexture.GL.cpp")
