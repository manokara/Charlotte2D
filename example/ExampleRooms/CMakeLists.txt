add_executable(ExampleRooms "ExampleRooms.cpp")
target_include_directories(ExampleRooms PUBLIC "../../source")

find_package(SFML 2 REQUIRED network audio graphics window system)
target_link_libraries(ExampleRooms charlotte)
target_link_libraries(ExampleRooms ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
