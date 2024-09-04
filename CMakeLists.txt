cmake_minimum_required(VERSION 3.21)
project(FlexBisonTemplate)

include(FetchContent)

if(MSVC)
    FetchContent_Declare(FlexBison_fetch GIT_REPOSITORY https://github.com/lexxmark/winflexbison.git)
    FetchContent_MakeAvailable(FlexBison_fetch)

    add_executable(flex ALIAS win_flex)
    add_executable(bison ALIAS win_bison)
else()
    # find_program(MAKE_EXECUTABLE NAMES gmake make mingw32-make REQUIRED)
    # find_program(FLEX_EXECUTABLE flex flex++)
    # if(FLEX_EXECUTABLE-NOTFOUND)
    #     set(config_flags)  # parameters desired for ./configure of Autotools

    #     set(FLEX_EXECUTABLE ${CMAKE_INSTALL_FULL_LIBDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}my${CMAKE_STATIC_LIBRARY_SUFFIX})

    #     ExternalProject_Add(flex_fetch
    #         GIT_REPOSITORY https://github.com/westes/flex.git
    #         CONFIGURE_HANDLED_BY_BUILD true
    #         CONFIGURE_COMMAND <SOURCE_DIR>/configure ${config_flags}
    #         BUILD_COMMAND ${MAKE_EXECUTABLE} -j
    #         INSTALL_COMMAND ${MAKE_EXECUTABLE} install
    #         TEST_COMMAND ""
    #         BUILD_BYPRODUCTS ${FLEX_EXECUTABLE}
    #     )
    # endif()
    # find_program(BISON_EXECUTABLE bison)
    # if(FLEX_EXECUTABLE-NOTFOUND)
    #     set(config_flags)  # parameters desired for ./configure of Autotools

    #     set(BISON_EXECUTABLE ${CMAKE_INSTALL_FULL_LIBDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}my${CMAKE_STATIC_LIBRARY_SUFFIX})

    #     ExternalProject_Add(bison_fetch
    #         URL https://ftp.gnu.org/gnu/bison/bison-3.8.2.tar.gz
    #         URL_HASH MD5=1e541a097cda9eca675d29dd2832921f
    #         CONFIGURE_HANDLED_BY_BUILD true
    #         CONFIGURE_COMMAND <SOURCE_DIR>/configure ${config_flags}
    #         BUILD_COMMAND ${MAKE_EXECUTABLE} -j
    #         INSTALL_COMMAND ${MAKE_EXECUTABLE} install
    #         TEST_COMMAND ""
    #         BUILD_BYPRODUCTS ${my_LIBRARY}
    #     )
    # endif()

    # add_executable(flex IMPORTED)
    # set_property(TARGET flex PROPERTY IMPORTED_LOCATION ${FLEX_EXECUTABLE})
    # add_executable(bison IMPORTED)
    # set_property(TARGET bison PROPERTY IMPORTED_LOCATION ${BISON_EXECUTABLE})
endif()

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/gen)

SET(BisonOutput ${CMAKE_SOURCE_DIR}/gen/parser.h)
ADD_CUSTOM_TARGET(
    run_bison
    COMMAND bison
            --output=${BisonOutput}
            ${CMAKE_SOURCE_DIR}/calculator.y
    BYPRODUCTS ${BisonOutput}
)

SET(FlexOutput ${CMAKE_SOURCE_DIR}/gen/scanner.h)
ADD_CUSTOM_TARGET(
    run_flex
    COMMAND flex
            --outfile=${FlexOutput}
            ${CMAKE_SOURCE_DIR}/calculator.l
    BYPRODUCTS ${FlexOutput}
)

add_executable(tst hello.cpp)
add_dependencies(tst run_flex run_bison)