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

macro ( download_and_include SRC )
    get_filename_component ( download_and_include_FILE_NAME ${SRC} NAME )
    string ( CONCAT download_and_include_DEST ${CMAKE_CURRENT_BINARY_DIR}/downloaded-cmake-modules/ ${download_and_include_FILE_NAME} )
    if ( NOT EXISTS ${download_and_include_DEST} )
        message ( STATUS " Downloading cmake module from ${SRC}" )
        file ( DOWNLOAD "${SRC}" "${download_and_include_DEST}" )
    else ()
        message ( STATUS "Using cmake module downloaded from ${SRC}" )
    endif ()
    if ( NOT EXISTS ${download_and_include_DEST} )
        message ( FATAL_ERROR "File ${DEST} is missing" )
    endif ()
    include ( ${download_and_include_DEST} )
endmacro ()

macro ( start_hunter )
    download_and_include ( "https://raw.githubusercontent.com/hunter-packages/gate/master/cmake/HunterGate.cmake" )
    huntergate (
            URL "https://github.com/ruslo/hunter/archive/v0.20.14.tar.gz"
            SHA1 "18cdbf5c47abdda437c73bf5437b7c3c65afe47c "
    )
endmacro ()