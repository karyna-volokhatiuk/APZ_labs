# - Find LibHttpServer

if(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)
    set(LIBHTTPSERVER_FOUND TRUE)

else(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)
    find_path(LIBHTTPSERVER_INCLUDE_DIRS httpserverpp
            /usr/include
            /usr/include/httpserver
            /usr/local/include/
            /usr/local/include/httpserver
            )

    find_library(LIBHTTPSERVER_LIBRARIES NAMES httpserver
            PATHS
            /usr/lib
            /usr/local/lib
            /opt/local/lib
            )

    if(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)
        set(LIBHTTPSERVER_FOUND TRUE)
        message(STATUS "Found libhttpserver: ${LIBHTTPSERVER_INCLUDE_DIRS}, ${LIBHTTPSERVER_LIBRARIES}")
    else(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)
        set(LIBHTTPSERVER_FOUND FALSE)
        message(STATUS "libhttpserver not found.")
    endif(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)

    mark_as_advanced(LIBHTTPSERVER_INCLUDE_DIRS LIBHTTPSERVER_LIBRARIES)

endif(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)