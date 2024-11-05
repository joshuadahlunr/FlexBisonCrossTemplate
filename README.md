# Flex & Bison Cross Platform Compilation Scripts

This template provides two scripts: 

1) scripts/flex-bison.cmake
2) scripts/bison-shim.sh.in (linux shim)

Which provide support for fetching (if not already present) and compiling [Flex](https://github.com/westes/flex) and [Bison](https://www.gnu.org/software/bison/) on Windows, Linux, and MacOS.

The [reflex](https://github.com/joshuadahlunr/FlexBisonCrossTemplate/tree/reflex) branch includes a version of the scripts that provides [RE-flex](https://github.com/Genivia/RE-flex) instead of flex.

## Usage

The library is used by including flex-bison.cmake and calling the fetch function:
```cmake
include(scripts/flex-bison.cmake)
fetch_flex_bison()
```

There will then be be `flex` and `bison` executable targets that can be used in cmake custom commands.

Additionally two new functions, which both take create a new target which uses flex/bision respectively to create the given output file whenever the input file changes are provided: 
```cmake
add_flex_target(run_flex ${CMAKE_SOURCE_DIR}/in.l OUTPUT ${CMAKE_SOURCE_DIR}/gen/scanner.h <extra flags here>)

add_bison_target(run_bison ${CMAKE_SOURCE_DIR}/in.y OUTPUT ${CMAKE_SOURCE_DIR}/gen/parser.h <extra flags here>)
```
NOTE: Extra flags can be passed at the end of the function and will be directly appended to the flex/bison call.

## Licenses

The scripts are MIT licensed, Flex and Re-flex are BSD licensed, Bison and the Windows versions of both libraries are GPL-3.0 licensed.


