cmake_minimum_required(VERSION 3.14)



project(InstaLike VERSION 0.1 LANGUAGES CXX)

#add_executable(project main.cpp)
# Find Package
set( OpenCV_STATIC OFF )
find_package( OpenCV PATHS ${CMAKE_SOURCE_DIR}/opencv REQUIRED NO_DEFAULT_PATH)


###

###

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")






set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
#add_executable(InstaLike ${OpenCV_LIBS})

set(PROJECT_SOURCES
        main.cpp
        imageprocessor.h imageprocessor.cpp
        Filters/filter.h Filters/filter.cpp
        Filters/filteroriginal.h Filters/filteroriginal.cpp
        Filters/filtergrayscale.h Filters/filtergrayscale.cpp
        Filters/filterblur.h Filters/filterblur.cpp
        jsonates.h jsonates.cpp
        qml.qrc

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(InstaLike
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET InstaLike APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(InstaLike SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(InstaLike
          ${PROJECT_SOURCES}
        )
    endif()
endif()


target_include_directories(InstaLike PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(InstaLike
  PRIVATE ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
#target_link_libraries(InstaLike mat.hpp ${OpenCV_LIBS})
#target_link_libraries(InstaLike opencv2/opencv.hpp ${OpenCV_LIBS})


set_target_properties(InstaLike PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS InstaLike
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(InstaLike)
    qt_finalize_executable(InstaLike)
endif()
