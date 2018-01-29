function ( download_and_include SRC DEST )
    if ( NOT EXISTS ${DEST} )
        message ( STATUS "Downloading ${DEST} from ${SRC}" )
        file ( DOWNLOAD "${SRC}" "${DEST}" )
    else ()
        message ( STATUS "Using downloaded file ${DEST}" )
    endif ()
    if ( NOT EXISTS ${DEST} )
        message ( FATAL_ERROR "File ${DEST} is missing" )
    endif ()
    include ( ${DEST} )
endfunction ()