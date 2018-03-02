#[[MIT License

Copyright (c) 2018 Michael Tepfer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.]]

cmake_minimum_required ( VERSION 3.9 )
include ( "cmake/helpers.cmake" )

option ( ENUM_GROUP_WITH_TESTS "Make a target to run the tests" ON )

start_hunter ()

project ( EnumGroup VERSION 0.0.1 )
set ( CMAKE_CXX_STANDARD 17 )

if ( ENUM_GROUP_WITH_TESTS )
    hunter_add_package ( Boost COMPONENTS test )
    find_package ( Boost REQUIRED COMPONENTS unit_test_framework )
endif ()

hunter_add_package ( Boost )
find_package ( Boost CONFIG REQUIRED )

add_library ( EnumGroup INTERFACE )
target_include_directories ( EnumGroup INTERFACE
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                             $<INSTALL_INTERFACE:include/EnumGroup>
                             )
target_link_libraries ( EnumGroup INTERFACE Boost::boost )

if ( ENUM_GROUP_WITH_TESTS )
    add_executable ( Tests test/test_entity.h test/tests.cpp )
    target_link_libraries ( Tests Boost::unit_test_framework EnumGroup )
    target_compile_definitions ( Tests INTERFACE BOOST_TEST_TOOLS_DEBUGGABLE )
endif ()

include ( GenerateExportHeader )
install ( TARGETS EnumGroup EXPORT EnumGroupTargets
          RUNTIME DESTINATION bin
          INCLUDES DESTINATION include/EnumGroup/
          )
install ( FILES src/EnumGroup.h src/ForEachMacro.h DESTINATION include/EnumGroup )

include ( CMakePackageConfigHelpers )
write_basic_package_version_file ( "${CMAKE_CURRENT_BINARY_DIR}/EnumGroup/EnumGroupConfigVersion.cmake"
                                   COMPATIBILITY ExactVersion )
export ( EXPORT EnumGroupTargets
         FILE "${CMAKE_CURRENT_BINARY_DIR}/EnumGroup/EnumGroupConfigTargets.cmake"
         NAMESPACE EnumGroup::
         )
configure_file ( cmake/EnumGroupConfig.cmake
                 "${CMAKE_CURRENT_BINARY_DIR}/EnumGroup/EnumGroupConfig.cmake"
                 COPYONLY
                 )

set ( ConfigPackageLocation lib/cmake/EnumGroup )
install ( EXPORT EnumGroupTargets
          FILE
          EnumGroupTargets.cmake
          NAMESPACE
          EnumGroup::
          DESTINATION
          ${ConfigPackageLocation}
          )
install (
        FILES
        cmake/EnumGroupConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/EnumGroup/EnumGroupConfigVersion.cmake"
        DESTINATION
        ${ConfigPackageLocation}
)