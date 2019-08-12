@echo off

set target=debug

for %%a in (%cd%) do set "project_name=%%~na"

set source_dir=..\..\src
set include_dir=..\..\etc\include
set library_dir=..\..\etc\lib\win32
set library_src_dir=..\..\etc\lib\src
set module_dir=..\..\etc\modules
set binary_dir=bin
set obj_dir_name=_intermediate
set obj_dir=%binary_dir%\%obj_dir_name%

if "%1" == "release" (
    set target="release"
)

if "%1" == "clean" (
    if exist %obj_dir% (
        echo Cleaning Project: %project_name%
        rmdir /Q /S %obj_dir%
    )
    call :CHECK_FAIL
    goto :EOF
)

if %target% == "release" (
    set target_options=/D_RELEASE /O2 /Ot
) else (
    set project_name=%project_name%_%target%
    set target_options=/D_DEBUG /Zi /Od 
)

if not exist %obj_dir% (
    call :CREATE_OBJ_DIR
)

if not defined DevEnvDir (
    call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
)

echo Building Project: %project_name%
pushd %obj_dir%
    set cpp_files=%source_dir%\main.cpp %module_dir%\imgui\imgui.cpp %module_dir%\imgui\imgui_demo.cpp %module_dir%\imgui\imgui_draw.cpp %module_dir%\imgui\imgui_widgets.cpp %module_dir%\imgui\examples\imgui_impl_glfw.cpp %module_dir%\imgui\examples\imgui_impl_opengl3.cpp
    cl /cgthreads8 /nologo %target_options% /I%include_dir% /I%module_dir% /I%module_dir%\imgui /Tp %cpp_files% /Tc %library_src_dir%\gl3w.c /link /SUBSYSTEM:WINDOWS /ENTRY:"mainCRTStartup" /OUT:..\%project_name%.exe opengl32.lib gdi32.lib User32.lib shell32.lib %library_dir%\glfw3.lib
    if exist ..\%project_name%.ilk (
        del ..\%project_name%.ilk
    )
popd
call :CHECK_FAIL

:: ---- Function Section Begin
goto :EOF

:CHECK_FAIL
if NOT ["%errorlevel%"]==["0"] (
    pause
    exit /b %errorlevel%
)
exit /b 0

:CREATE_OBJ_DIR
pushd %binary_dir%
    echo Creating Directory: %obj_dir_name%
    mkdir %obj_dir_name%
    call :CHECK_FAIL
popd
exit /b 0

:: ---- Function Section End