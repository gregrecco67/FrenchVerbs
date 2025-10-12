cmake_minimum_required(VERSION 3.28)

# run "emcmake cmake -B web-build"
# then "cmake --build web-build --config Release"

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "Build for 10.14")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (APPLE AND NOT EMSCRIPTEN)
  enable_language(OBJC)
  enable_language(OBJCXX)
endif ()
if (MSVC)
  add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:/Zc:__cplusplus>
  )
endif()

set(PROJECT_NAME "FrenchVerbs")
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX C)

# assuming visage has been added as a submodule
add_subdirectory(libs/visage)

file(GLOB_RECURSE FONT_TTF_FILES fonts/*.ttf)
add_embedded_resources(EmbeddedFontResources "example_fonts.h" "resources::fonts" "${FONT_TTF_FILES}")
file(GLOB_RECURSE IMAGE_FILES images/*.png)
add_embedded_resources(EmbeddedImageResources "example_images.h" "resources::images" "${IMAGE_FILES}")

#find_library(SQL sqlite3 HINTS ENV "/Users/grecco/dev/sqlite3/ext/wasm/bld")
FetchContent_Declare(
    SQLite3
    URL https://www.sqlite.org/2025/sqlite-amalgamation-3500100.zip
    URL_HASH
        SHA3_256=65e5176c171aff92ff31f3ab4d431a879d648de93f139816f9331a7074859092
)

FetchContent_MakeAvailable(sqlite3)

add_library(sqlite3)
target_sources(sqlite3 PRIVATE
    ${sqlite3_SOURCE_DIR}/sqlite3.c
    ${sqlite3_SOURCE_DIR}/sqlite3.h
    ${sqlite3_SOURCE_DIR}/sqlite3ext.h
)

target_include_directories(sqlite3 PUBLIC ${sqlite3_SOURCE_DIR})
target_compile_options(sqlite3 PRIVATE -g3)

### Compile options ###
# refer to https://www.sqlite.org/compile.html
# target_compile_definitions(sqlite3 PUBLIC)

# Use the same name as the FindSQLite3 script of CMake uses
add_library(SQLite::SQLite3 ALIAS sqlite3)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/App.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
include_directories(PUBLIC libs/visage libs/unibetacode src)

if (EMSCRIPTEN)
    MESSAGE(STATUS "Building for WebAssembly")    
    target_link_options(${PROJECT_NAME}
      PRIVATE
      --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/minshell.html
      -sGL_ENABLE_GET_PROC_ADDRESS
      -sALLOW_MEMORY_GROWTH=1
      --bind
      -s STACK_SIZE=32MB
      "-sEXPORTED_FUNCTIONS=['_main', '_pasteCallback']"
      "-sEXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'UTF8ToString']"
  )

  set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX ".html"
    OUTPUT_NAME "index"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/builds/${EXAMPLE}"
  )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
  visage
  EmbeddedFontResources
  EmbeddedImageResources
  sqlite3 # ${SQL} 
)
