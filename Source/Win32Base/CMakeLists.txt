# CMakeLists configuration for the AgWin32Base library

set(WIN32_INCLUDE_DIR "${AG_INCLUDE_DIR}/Ag/Win32Base")

# Define the library.
ag_add_library(Win32Base    FOLDER      Win32
                            SOURCES     PreCompiledHeader.hpp
                                        Tools.cpp
                                        ${WIN32_INCLUDE_DIR}/Tools.hpp
                                        KernelTools.cpp
                                        ${WIN32_INCLUDE_DIR}/KernelTools.hpp
                                        InternalTools.cpp
                                        InternalTools.hpp
                                        ComTools.cpp
                                        ${WIN32_INCLUDE_DIR}/ComTools.hpp
                                        Message.cpp
                                        ${WIN32_INCLUDE_DIR}/Message.hpp
                                        MessageTarget.cpp
                                        ${WIN32_INCLUDE_DIR}/MessageTarget.hpp
                                        MessageMap.cpp
                                        ${WIN32_INCLUDE_DIR}/MessageMap.hpp
                                        Dispatcher.cpp
                                        ${WIN32_INCLUDE_DIR}/Dispatcher.hpp
                                        Bitmap.cpp
                                        ${WIN32_INCLUDE_DIR}/Bitmap.hpp
                                        Brush.cpp
                                        ${WIN32_INCLUDE_DIR}/Brush.hpp
                                        Font.cpp
                                        ${WIN32_INCLUDE_DIR}/Font.hpp
                                        Pen.cpp
                                        ${WIN32_INCLUDE_DIR}/Pen.hpp
                                        DeviceContext.cpp
                                        ${WIN32_INCLUDE_DIR}/DeviceContext.hpp
                                        GdiResource.cpp
                                        ${WIN32_INCLUDE_DIR}/GdiResource.hpp
                                        GdiResourceFactory.cpp
                                        ${WIN32_INCLUDE_DIR}/GdiResourceFactory.hpp
                                        GdiResourceCache.cpp
                                        ${WIN32_INCLUDE_DIR}/GdiResourceCache.hpp
                                        BaseWindow.cpp
                                        ${WIN32_INCLUDE_DIR}/BaseWindow.hpp
                                        Ctrl.cpp
                                        ${WIN32_INCLUDE_DIR}/Ctrl.hpp
                                        Window.cpp
                                        ${WIN32_INCLUDE_DIR}/Window.hpp
                                        CustomCtrl.cpp
                                        ${WIN32_INCLUDE_DIR}/CustomCtrl.hpp
                                        CustomWindow.cpp
                                        ${WIN32_INCLUDE_DIR}/CustomWindow.hpp
                                        Dialog.cpp
                                        ${WIN32_INCLUDE_DIR}/Dialog.hpp
                                        GuiApp.cpp
                                        ${WIN32_INCLUDE_DIR}/GuiApp.hpp
                                        MessageBox.cpp
                                        ${WIN32_INCLUDE_DIR}/MessageBox.hpp
                                        CtrlArranger.cpp
                                        ${WIN32_INCLUDE_DIR}/CtrlArranger.hpp
                                        ${WIN32_INCLUDE_DIR}/Win32API.hpp
                            HEADERS     ${AG_INCLUDE_DIR}/Ag/Win32Base.hpp
                            PUBLIC_LIBS AgCore)


target_precompile_headers(Win32Base PRIVATE [["PreCompiledHeader.hpp"]])
target_include_directories(Win32Base PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

source_group(Misc FILES     ${AG_INCLUDE_DIR}/Ag/Win32Base.hpp
                            KernelTools.cpp
                            ${WIN32_INCLUDE_DIR}/KernelTools.hpp
                            Tools.cpp
                            ${WIN32_INCLUDE_DIR}/Tools.hpp
                            InternalTools.cpp
                            InternalTools.hpp
                            ComTools.cpp
                            ${WIN32_INCLUDE_DIR}/ComTools.hpp
                            ${WIN32_INCLUDE_DIR}/Win32API.hpp)

source_group(Messages FILES Message.cpp
                            ${WIN32_INCLUDE_DIR}/Message.hpp
                            MessageTarget.cpp
                            ${WIN32_INCLUDE_DIR}/MessageTarget.hpp
                            MessageMap.cpp
                            ${WIN32_INCLUDE_DIR}/MessageMap.hpp
                            Dispatcher.cpp
                            ${WIN32_INCLUDE_DIR}/Dispatcher.hpp
                            GuiApp.cpp
                            ${WIN32_INCLUDE_DIR}/GuiApp.hpp)

source_group(GDI FILES      Bitmap.cpp
                            ${WIN32_INCLUDE_DIR}/Bitmap.hpp
                            Brush.cpp
                            ${WIN32_INCLUDE_DIR}/Brush.hpp
                            Font.cpp
                            ${WIN32_INCLUDE_DIR}/Font.hpp
                            Pen.cpp
                            ${WIN32_INCLUDE_DIR}/Pen.hpp
                            DeviceContext.cpp
                            ${WIN32_INCLUDE_DIR}/DeviceContext.hpp
                            GdiResource.cpp
                            ${WIN32_INCLUDE_DIR}/GdiResource.hpp
                            GdiResourceFactory.cpp
                            ${WIN32_INCLUDE_DIR}/GdiResourceFactory.hpp
                            GdiResourceCache.cpp
                            ${WIN32_INCLUDE_DIR}/GdiResourceCache.hpp)

source_group(Windows FILES  BaseWindow.cpp
                            ${WIN32_INCLUDE_DIR}/BaseWindow.hpp
                            Ctrl.cpp
                            ${WIN32_INCLUDE_DIR}/Ctrl.hpp
                            Window.cpp
                            ${WIN32_INCLUDE_DIR}/Window.hpp
                            CustomCtrl.cpp
                            ${WIN32_INCLUDE_DIR}/CustomCtrl.hpp
                            CustomWindow.cpp
                            ${WIN32_INCLUDE_DIR}/CustomWindow.hpp
                            Dialog.cpp
                            ${WIN32_INCLUDE_DIR}/Dialog.hpp
                            MessageBox.cpp
                            ${WIN32_INCLUDE_DIR}/MessageBox.hpp
                            CtrlArranger.cpp
                            ${WIN32_INCLUDE_DIR}/CtrlArranger.hpp)