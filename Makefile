target=debug
company_name = "YourCompanyName"
project_name = $(shell basename $(CURDIR))
source_dir=src
module_dir=etc/modules
include_dir=etc/include
library_dir=etc/lib/darwin
library_src_dir=etc/lib/src
binary_dir=bin
obj_dir_name=_intermediate
obj_dir=$(binary_dir)/$(obj_dir_name)
debug_flags=" -O0 -g -D_DEBUG"
release_flags=" -O2 -s -DNDEBUG -D_RELEASE"
target_compiler_options=$(debug_flags)

EXE = ""
SOURCES = $(source_dir)/main.cpp $(source_dir)/Utility.cpp $(source_dir)/GLTexture.cpp $(source_dir)/GUI.cpp
SOURCES += $(module_dir)/imgui/examples/imgui_impl_glfw.cpp $(module_dir)/imgui/examples/imgui_impl_opengl3.cpp
SOURCES += $(module_dir)/imgui/imgui.cpp $(module_dir)/imgui/imgui_demo.cpp $(module_dir)/imgui/imgui_draw.cpp $(module_dir)/imgui/imgui_widgets.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
OUTOBJS =  $(addprefix $(obj_dir)/,$(OBJS))
UNAME_S := $(shell uname -s)

CXXFLAGS = -I./$(module_dir)/imgui/examples -I$(module_dir)/imgui -I$(module_dir)
CXXFLAGS += -Wall -Wformat -std=c++11 -stdlib=libc++
LIBS =

##---------------------------------------------------------------------
## OPENGL LOADER
##---------------------------------------------------------------------

## Using OpenGL loader: gl3w [default]
SOURCES += $(library_src_dir)/gl3w.c
CXXFLAGS += -I$(include_dir)

## Using OpenGL loader: glew
## (This assumes a system-wide installation)
# CXXFLAGS = -lGLEW -DIMGUI_IMPL_OPENGL_LOADER_GLEW

## Using OpenGL loader: glad
## (You'll also need to change the rule at line ~77 of this Makefile to compile/link glad.c/.o)
# SOURCES += ../libs/glad/src/glad.c
# CXXFLAGS = -I../libs/glad/include -DIMGUI_IMPL_OPENGL_LOADER_GLAD

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
	EXE = $(project_name)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L$(library_dir) -L/usr/local/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include
	CFLAGS += -I$(include_dir)

	EXE = $(binary_dir)/$(project_name).app/Contents/MacOS/$(project_name)
build: osx
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)

	EXE = $(project_name)
endif

##---------------------------------------------------------------------
.PHONY: all
.PHONY: build
.PHONY: clean
.PHONY: osx
.PHONY: run

all: build
	

build:
	@echo Building Project: $(EXE) $(ECHO_MESSAGE)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SOURCES) $(LIBS)

clean:
	#rm -f $(OUTOBJS)
	@echo Cleaning Project: $(EXE) $(ECHO_MESSAGE)

osx:
	mkdir -p "./$(binary_dir)/$(project_name).app"/Contents/{MacOS,Resources}/
	rm -f "./$(binary_dir)/$(project_name).app/Contents/Info.plist"
	/usr/libexec/PlistBuddy -c "add CFBundleIconFile string $(project_name).icns" "./$(binary_dir)/$(project_name).app/Contents/Info.plist"
	/usr/libexec/PlistBuddy -c "add CFBundleExecutable string $(project_name)" "./$(binary_dir)/$(project_name).app/Contents/Info.plist"
	/usr/libexec/PlistBuddy -c "add CFBundleIdenfier string com.$(company_name).$(project_name)" "./$(binary_dir)/$(project_name).app/Contents/Info.plist"
	/usr/libexec/PlistBuddy -c "add CFBundleInfoDictionaryVersion string 6.0" "./$(binary_dir)/$(project_name).app/Contents/Info.plist"
	/usr/libexec/PlistBuddy -c "add CFBundleName string $(project_name)" "./$(binary_dir)/$(project_name).app/Contents/Info.plist"
	/usr/libexec/PlistBuddy -c "add CFBundlePackageType string APPL" "./$(binary_dir)/$(project_name).app/Contents/Info.plist"
	cp ./$(binary_dir)/IconAtlas.tga "./$(binary_dir)/$(project_name).app/Contents/Resources/IconAtlas.tga"

run: build
	$(EXE)