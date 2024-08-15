cmake_minimum_required(VERSION 3.5)

project(freeview_wasm VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets openglwidgets opengl)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets openglwidgets opengl)
find_package(VTK
  COMPONENTS
    FiltersSources      # VTK pipeline
    InteractionStyle    # Mouse handling
    RenderingOpenGL2    # For Rendering
    RenderingUI         # For SDL2 Window
)

if (NOT VTK_FOUND)
  message("Skipping example: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif ()

include_directories(Qt .)

set(PROJECT_SOURCES
      main.cpp
      MainWindow.cpp
      MainWindow.h
      MainWindow.ui
      Qt/vtkEventQtSlotConnect.cxx 
      Qt/vtkQtConnection.cxx 
      Qt/QVTKInteractor.cxx 
      Qt/QVTKInteractorAdapter.cxx 
      Qt/QVTKWidget.cxx 
      Qt/QVTKPaintEngine.cxx 
      Qt/QVTKOpenGLNativeWidget.cxx 
      Qt/QVTKOpenGLWidget.cxx 
      Qt/QVTKOpenGLWindow.cxx 
      Qt/QVTKRenderWindowAdapter.cxx
      RenderView.cpp 
      GenericRenderView.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(freeview_wasm
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET freeview_wasm APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(freeview_wasm SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(freeview_wasm
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(freeview_wasm PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::OpenGLWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.freeview_wasm)
endif()
set_target_properties(freeview_wasm PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

vtk_module_autoinit(
  TARGETS  freeview_wasm
  MODULES  ${VTK_LIBRARIES}
)

# -----------------------------------------------------------------------------
# WebAssembly build options
# -----------------------------------------------------------------------------

set(emscripten_compile_options)
list(APPEND emscripten_compile_options
  "-g3"
#  "SHELL:-s USE_PTHREADS=0"
)

set(emscripten_link_options)
list(APPEND emscripten_link_options
  "--bind"
  "-g3"
#  "SHELL:-s EXPORT_NAME=vtkApp"
  "SHELL:-s ALLOW_MEMORY_GROWTH=1"
  "SHELL:-s DEMANGLE_SUPPORT=1"
  "SHELL:-s EMULATE_FUNCTION_POINTER_CASTS=0"
  "SHELL:-s ERROR_ON_UNDEFINED_SYMBOLS=0"
  "SHELL:-s MODULARIZE=1"
#  "SHELL:-s USE_PTHREADS=0"
  "SHELL:-s WASM=1"
)

# -----------------------------------------------------------------------------
# Build options
# -----------------------------------------------------------------------------

target_compile_options(freeview_wasm
  PUBLIC
    ${emscripten_compile_options}
)

target_link_options(freeview_wasm
  PUBLIC
    ${emscripten_link_options}
)

target_link_libraries(freeview_wasm
  PRIVATE
    VTK::FiltersSources
    VTK::InteractionStyle
    VTK::RenderingOpenGL2
    VTK::RenderingUI
)

include(GNUInstallDirs)
install(TARGETS freeview_wasm
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(freeview_wasm)
endif()
