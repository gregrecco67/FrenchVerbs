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


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "IS_LINUX")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "IS_MACOS")
    add_compile_options(-mmacosx-version-min=15.0)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -D_GLIBCXX_USE_CXX11_ABI=1)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "IS_WINDOWS")
endif()

# assuming visage has been added as a submodule
add_subdirectory(libs/visage)

file(GLOB_RECURSE FONT_TTF_FILES fonts/*.ttf)
add_embedded_resources(EmbeddedFontResources "example_fonts.h" "resources::fonts" "${FONT_TTF_FILES}")
file(GLOB_RECURSE IMAGE_FILES images/*.png)
add_embedded_resources(EmbeddedImageResources "example_images.h" "resources::images" "${IMAGE_FILES}")
file(GLOB_RECURSE DB_FILES dbs/*.json)
add_embedded_resources(EmbeddedDbResources "example_dbs.h" "resources::dbs" "${DB_FILES}")

add_subdirectory(libs/SQLiteCpp)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/App.cpp
  src/DbManager.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
include_directories(PUBLIC libs/visage libs/SQLiteCpp src)

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
  EmbeddedDbResources
  SQLiteCpp
  sqlite3 # ${SQL} 
)
