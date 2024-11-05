# Flex & Bison Cross-Platform Compilation Scripts

This repository provides CMake scripts to simplify the setup and usage of [Flex](https://github.com/westes/flex) and [Bison](https://www.gnu.org/software/bison/) across **Windows, Linux, and macOS**.

It ensures that Flex and Bison are **fetched, built, and available automatically** - so you don't need to worry about manual installation.

For an alternative version that uses [RE-flex](https://github.com/Genivia/RE-flex) instead of Flex, check out the [`reflex` branch](https://github.com/joshuadahlunr/FlexBisonCrossTemplate/tree/reflex).

---

## Features

- ✅ Cross-platform support (Windows, Linux, macOS)
- ✅ Automatic download and compilation if Flex/Bison are missing
- ✅ CMake integration for build pipelines
- ✅ Helper functions to generate sources with Flex/Bison targets
- ✅ Minimal setup - just copy the `scripts` folder into your project

---

## Getting Started

### 1. Copy the Scripts

Copy the `scripts` folder into your project root.

A complete working example is provided in the **root folder** of this repository.

---

### 2. Include the CMake Script

In your `CMakeLists.txt`, include the script and fetch the tools:

```cmake
include(scripts/flex-bison.cmake)
fetch_flex_bison()
```

This creates two executable targets available in CMake:

- flex
- bison

### 3. Add Flex and Bison Targets

Use the provided helper functions to automatically generate source files:

```cmake
add_flex_target(
    run_flex
    ${CMAKE_SOURCE_DIR}/in.l
    OUTPUT ${CMAKE_SOURCE_DIR}/gen/scanner.h
    <extra flags here>
)

add_bison_target(
    run_bison
    ${CMAKE_SOURCE_DIR}/in.y
    OUTPUT ${CMAKE_SOURCE_DIR}/gen/parser.h
    <extra flags here>
)
```

Whenever the .l or .y input files change, the corresponding target regenerates the output automatically.

💡 Tip: You can pass extra flags at the end of the function call. These flags are appended directly to the Flex/Bison command.

## Example Project Structure

```pgsql
project-root/
│
├─ CMakeLists.txt
├─ scripts/ # Copy this folder from the repo
│ ├─ flex-bison.cmake
│ └─ bison-shim.sh.in
├─ in.l # Flex input
├─ in.y # Bison input
└─ gen/ # Generated sources (scanner.h, parser.h, etc. should be added to your .gitignore)
```

For a full working setup, see the example project in this repository's root.

## Troubleshooting

- **Problem:** Flex or Bison not found

**Solution:** Ensure you called fetch_flex_bison() before adding Flex/Bison targets.

- **Problem:** Generated files are not updating

**Solution:** Confirm that the input file path (.l or .y) is correct and included in the target definition.

- **Problem:** Extra flags not applied

**Solution:** Verify they are passed at the end of the add_flex_target / add_bison_target call.

## License

- Scripts: MIT License
- Flex & RE-flex: BSD License
- Bison: GPL-3.0 License
- Windows builds of Flex and Bison: GPL-3.0 License
