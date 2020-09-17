add_library (Speeddemon speeddemon.cpp)

# Make sure the compiler can find include files for our speeddemon library
# when other libraries or executables link to Speeddemon
target_include_directories (Speeddemon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
