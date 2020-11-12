cmake_minimum_required(VERSION 3.15)
project(example C CXX OBJC)

find_package(Corrosion REQUIRED)

set(APP Piet-metal)

set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")

set(APP_STORYBOARD ${CMAKE_CURRENT_SOURCE_DIR}/TestApp/Base.lproj/Main.storyboard)
add_executable(${APP} MACOSX_BUNDLE
    TestApp/main.m
    TestApp/AppDelegate.h
    TestApp/AppDelegate.m
    TestApp/GenTypes.h
    TestApp/PietRender.metal
    TestApp/PietRenderer.h
    TestApp/PietRenderer.m
    TestApp/PietShaderTypes.h
    TestApp/SceneEncoder.h
    TestApp/SceneEncoder.m
    TestApp/ViewController.h
    TestApp/ViewController.m
    ${APP_STORYBOARD}
)

message(${CMAKE_CXX_COMPILER_ID})
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${APP} PRIVATE -fcxx-modules -fmodules)
endif()

# Handle the Storyboard ourselves
if(NOT ${CMAKE_GENERATOR} MATCHES "^Xcode.*")
    # Compile the storyboard file with the ibtool.
    find_program(IBTOOL NAMES ibtool)
    add_custom_command(TARGET ${APP} POST_BUILD
        COMMAND ${IBTOOL} --errors --warnings --notices --output-format human-readable-text
            --compile ${CMAKE_CURRENT_BINARY_DIR}/${APP}.app/Contents/Resources/Main.storyboardc
            ${APP_STORYBOARD}
            COMMENT "Compiling storyboard"
    )
endif()

function(build_metal_shader TARGET SHADER)
    get_filename_component(SHADER_NAME ${SHADER} NAME_WE)
    get_filename_component(SHADER_PATH ${SHADER} ABSOLUTE)
    set(METAL_AIR_FILE "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.air")
    set(METAL_LIB_FILE "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.metallib")
    add_custom_command(OUTPUT ${METAL_LIB_FILE}
        COMMAND xcrun -sdk macosx metal ${SHADER_PATH} -ffast-math -arch air64 -c -o ${METAL_AIR_FILE}
        COMMAND xcrun -sdk macosx metallib -o ${METAL_LIB_FILE} ${METAL_AIR_FILE}
        DEPENDS ${SHADER_PATH}
    )
    add_custom_target(BUILD_METAL_SHADER_${SHADER_NAME} ALL DEPENDS ${METAL_LIB_FILE})

    add_dependencies(${TARGET} BUILD_METAL_SHADER_${SHADER_NAME})
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${METAL_LIB_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${APP}.app/Contents/Resources/default.metallib
    )
endfunction()

# App Info.plist
set(DEVELOPMENT_LANGUAGE OBJC)
set(EXECUTABLE_NAME ${APP})
set(PRODUCT_BUNDLE_IDENTIFIER "xi-editor.piet-metal")
set(PRODUCT_NAME ${APP})
set(MACOSX_DEPLOYMENT_TARGET "macosx")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestApp/Info.plist.in ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)

set_target_properties(${APP} PROPERTIES
    MACOSX_BUNDLE YES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist
    XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
    XCODE_ATTRIBUTE_INFOPLIST_PREPROCESS YES
)

target_include_directories(${APP} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/TestApp
)

build_metal_shader(${APP} TestApp/PietRender.metal)

#rust module import through corrosion
corrosion_import_crate(MANIFEST_PATH Cargo.toml)

target_link_libraries(${APP}
    "-lobjc"
    "-framework Cocoa"
    "-framework Metal"
    "-framework MetalKit"
    "-framework QuartzCore"
    piet_metal
)
