@echo off
setlocal enabledelayedexpansion
set target=debug

for %%a in (%cd%) do set "project_name=%%~na"

echo %project_name%

if "%1" == "release" (
    set target="release"
)

if "%1" == "clean" goto :clean_obj

if %target% == "release" (
    set target_options=/D_RELEASE /O2 /Ot
) else (
    set new_project_name=%project_name%_%target%
    set project_name=%new_project_name%
    set target_options=/D_DEBUG /Zi /Od 
)

set source_dir=..\..\src
set include_dir=..\..\etc\include
set library_dir=..\..\etc\lib\win32
set module_dir=..\..\etc\modules
set binary_dir=bin
set obj_dir_name=_intermediate
set obj_dir=%binary_dir%\%obj_dir_name%

if exist %obj_dir% (
    goto :obj_dir_exists
) else (
    goto :create_obj_dir
)

:create_obj_dir
pushd %binary_dir%
    mkdir %obj_dir_name%
popd
goto :obj_dir_exists

:obj_dir_exists
if not defined DevEnvDir (
    call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
)
pushd %obj_dir%
    set cpp_files=%source_dir%\main.cpp %module_dir%\imgui\imgui.cpp %module_dir%\imgui\imgui_demo.cpp %module_dir%\imgui\imgui_draw.cpp %module_dir%\imgui\imgui_widgets.cpp %module_dir%\imgui\examples\imgui_impl_glfw.cpp %module_dir%\imgui\examples\imgui_impl_opengl3.cpp
    cl /cgthreads8 /nologo %target_options% /I%include_dir% /I%module_dir% /I%module_dir%\imgui /Tp %cpp_files% /Tc %source_dir%\gl3w.c /link /SUBSYSTEM:WINDOWS /ENTRY:"mainCRTStartup" /OUT:..\%project_name%.exe opengl32.lib gdi32.lib User32.lib shell32.lib %library_dir%\glfw3.lib
    if exist ..\%project_name%.ilk (
        del ..\%project_name%.ilk
    )
popd
goto :EOF

:clean_obj
if exist %obj_dir% (
    rmdir /Q /S %obj_dir%
)
goto :EOF