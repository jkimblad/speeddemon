# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Provide compile flags to clangd for semantic analysis in YCM
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.16.5)
project (speeddemon)

# Recurse into the "src" subdirectorie. This does not actually cause another
# cmake executable to run. The same process will walk through the project's
# entire directory structure.
add_subdirectory (src)

# Make library installable
set_target_properties(Speeddemon PROPERTIES PUBLIC_HEADER "inc/speeddemon.hpp")
INSTALL(TARGETS Speeddemon
    LIBRARY DESTINATION /usr/local/lib
    PUBLIC_HEADER DESTINATION /usr/local/include
    )

# Use compiler warnings
target_compile_options(Speeddemon PRIVATE -Wall -Wextra -Wpedantic)


