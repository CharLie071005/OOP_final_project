if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(ERROR "GCC >= 4.8 required - detected ${CMAKE_CXX_COMPILER_VERSION} not supported")
    endif ()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # TODO: verify this
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 2.9)
        message(ERROR "Clang >= 2.9 required - detected ${CMAKE_CXX_COMPILER_VERSION} not supported")
    endif ()
elseif(MSVC)
    if (MSVC_VERSION VERSION_LESS 1800)
        message(ERROR "Visual Studio >= 2013 (1800) required - detected ${MSVC_VERSION} not supported")
    endif ()
endif()
