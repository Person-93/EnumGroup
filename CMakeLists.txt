cmake_minimum_required ( VERSION 3.9 )
include ( "helpers.cmake" )

# include hunter
download_and_include ( "https://raw.githubusercontent.com/hunter-packages/gate/master/cmake/HunterGate.cmake"
                       "${CMAKE_CURRENT_BINARY_DIR}/HunterGate.cmake" )
huntergate (
        URL "https://github.com/ruslo/hunter/archive/v0.19.228.tar.gz"
        SHA1 "5f8bde642d44d2ef652c917fa6b36dbc5f693d51"
)

project ( EnumGroup )
set ( CMAKE_CXX_STANDARD 17 )

hunter_add_package ( Boost COMPONENTS test )
find_package ( Boost REQUIRED COMPONENTS unit_test_framework )

hunter_add_package ( Boost )
find_package ( Boost CONFIG REQUIRED )

add_executable ( Tests EnumGroup.h ForEachMacro.h test_entity.h tests.cpp )
target_link_libraries ( Tests Boost::unit_test_framework Boost::boost )
target_compile_definitions ( Tests
                             INTERFACE BOOST_TEST_TOOLS_DEBUGGABLE )