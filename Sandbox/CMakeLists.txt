add_executable(Sandbox)

target_link_libraries(Sandbox PRIVATE Yooz)

target_include_directories(Sandbox PRIVATE "/")

target_sources(Sandbox PRIVATE "Sandbox.cpp")
