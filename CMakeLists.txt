cmake_minimum_required(VERSION 3.21)

project(
    tetris
    VERSION 1.0.0
    DESCRIPTION "Tetris Game Written C and SDL"
    LANGUAGES C
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Build type not set — defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel"
    )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# find_package(Vulkan REQUIRED)
find_package(SDL3 REQUIRED CONFIG) # modern SDL3 cmake config
if(NOT TARGET SDL3::SDL3)
    # Older SDL3 installs may not ship a cmake config; use pkg-config.
    pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
    add_library(SDL3::SDL3 ALIAS PkgConfig::SDL3)
endif()

find_package(SDL3_image QUIET CONFIG)
if(NOT TARGET SDL3_image::SDL3_image)
    pkg_check_modules(SDL3_image QUIET IMPORTED_TARGET sdl3-image)
    if(NOT SDL3_image_FOUND)
        pkg_check_modules(SDL3_image REQUIRED IMPORTED_TARGET SDL3_image)
    endif()
    add_library(SDL3_image::SDL3_image ALIAS PkgConfig::SDL3_image)
endif()

find_package(SDL3_ttf QUIET CONFIG)
if(NOT TARGET SDL3_ttf::SDL3_ttf)
    pkg_check_modules(SDL3_ttf QUIET IMPORTED_TARGET sdl3-ttf)
    if(NOT SDL3_ttf_FOUND)
        pkg_check_modules(SDL3_ttf REQUIRED IMPORTED_TARGET SDL3_ttf)
    endif()
    add_library(SDL3_ttf::SDL3_ttf ALIAS PkgConfig::SDL3_ttf)
endif()

# set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/third_party/imgui") set(IMGUI_SOURCES
# "${IMGUI_DIR}/imgui.c" "${IMGUI_DIR}/imgui_draw.c"
# "${IMGUI_DIR}/imgui_tables.c" "${IMGUI_DIR}/imgui_widgets.c"
# "${IMGUI_DIR}/backends/imgui_impl_sdl3.c"
# "${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.c" )

# add_library(imgui STATIC ${IMGUI_SOURCES}) target_include_directories(imgui
# PUBLIC "${IMGUI_DIR}" "${IMGUI_DIR}/backends") target_link_libraries(imgui
# PUBLIC SDL3::SDL3) target_compile_features(imgui PRIVATE cxx_std_17)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(tetris ${APP_SOURCES})
target_compile_features(tetris PRIVATE c_std_23)
target_include_directories(tetris PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(
    tetris
    PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf # Vulkan::Vulkan
)

# AssetManager searches several runtime locations first (executable directory,
# parent directory, cwd).  If none of them contain the assets tree — which
# happens when the binary is launched from an arbitrary working directory with
# no deployment step, e.g. directly from an IDE debugger — this definition gives
# it a guaranteed absolute path that always works on the developer's machine.
#
# The value intentionally points at the *source* tree so in-tree development
# (bootstrap.sh → build.sh) works without a cmake --install step. Production
# packages will find the assets via the executable-relative path set up by the
# install(DIRECTORY …) rule below and will never need this fallback.

target_compile_definitions(
    tetris
    PRIVATE LX_ASSET_DIR="${CMAKE_SOURCE_DIR}/assets"
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        tetris
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow

            "$<$<CONFIG:Debug>:-g3>"
            "$<$<CONFIG:Debug>:-O0>"
            "$<$<CONFIG:Debug>:-fsanitize=address,undefined>"
            "$<$<CONFIG:Debug>:-fno-omit-frame-pointer>"

            "$<$<CONFIG:Release>:-O2>"
            "$<$<CONFIG:RelWithDebInfo>:-O2;-g>"
    )

    target_link_options(
        tetris
        PRIVATE
            "$<$<CONFIG:Debug>:-fsanitize=address,undefined>"
    )
endif()

if(MSVC)
    target_compile_options(tetris PRIVATE /W4 /permissive-)
endif()

# set(ASSETS_SRC "${CMAKE_SOURCE_DIR}/assets")

# Copy assets to the build tree so the binary can find them at runtime using the
# executable-relative search path (../assets/ from the binary location).
# add_custom_command( TARGET tetris POST_BUILD # COMMAND "${CMAKE_COMMAND}" -E
# copy_directory "${ASSETS_SRC}" "$<TARGET_FILE_DIR:tetris>/../assets" COMMENT
# "Copying assets to build directory" )

# include(GNUInstallDirs)
#
# install(TARGETS tetris RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
#
# install( DIRECTORY "${ASSETS_SRC}/" DESTINATION
# "${CMAKE_INSTALL_DATADIR}/tetris/assets" )

# Optional: desktop entry and icon (uncomment and adjust when ready)
# install(FILES "packaging/tetris.desktop" DESTINATION
# "${CMAKE_INSTALL_DATADIR}/applications") install(FILES "packaging/tetris.png"
# DESTINATION "${CMAKE_INSTALL_DATADIR}/pixmaps")

message(STATUS "")
message(STATUS "  ┌─────────────────────────────────────────────────────┐")
message(STATUS "  │  tetris ${PROJECT_VERSION} — ${CMAKE_BUILD_TYPE}    │")
message(STATUS "  │                                                     │")
message(
    STATUS
    "  │  Compiler   : ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} │"
)
message(STATUS "  │  Build dir  : ${CMAKE_BINARY_DIR}│  ")
message(STATUS "  │  Install to : ${CMAKE_INSTALL_PREFIX}│  ")
# message( STATUS "  │  Asset root : ${CMAKE_SOURCE_DIR}/assets  (compile-time
# fallback)" )
message(STATUS "  └─────────────────────────────────────────┘")
message(STATUS "")
