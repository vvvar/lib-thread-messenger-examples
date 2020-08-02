cmake_minimum_required(VERSION 3.17)

project(lib-thread-messenger-examples)

add_executable(${PROJECT_NAME}
	main.cpp
)

add_subdirectory(libs)

set_target_properties(lib-thread-messenger-examples
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set_target_properties(lib-thread-messenger-examples PROPERTIES
        MACOSX_BUNDLE ON
        MACOSX_BUNDLE_BUNDLE_NAME "lib-thread-messenger examples application"
        MACOSX_BUNDLE_BUNDLE_IDENTIFIER "lib.thread.messenger.examples"
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/MacOSXBundleInfo.plist.in
    )
endif()