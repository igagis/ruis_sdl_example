include prorab.mk

this_name := sdl2_example


this_srcs := src/main.cpp


this_cxxflags += -Wall
this_cxxflags += -Wno-comment # no warnings on nested comments
this_cxxflags += -Wno-format
this_cxxflags += -DDEBUG
this_cxxflags += -fstrict-aliasing
this_cxxflags += -g
this_cxxflags += -O2
this_cxxflags += -std=c++14


ifeq ($(debug), true)
    this_cxxflags += -DDEBUG
endif

ifeq ($(prorab_os),windows)
    
else ifeq ($(prorab_os),macosx)
    this_ldlibs += `pkg-config --libs sdl2 glew` -framework OpenGL # -framework Cocoa
else ifeq ($(prorab_os),linux)
    this_ldlibs += -lGLEW -pthread -lGL -lSDL2
endif

this_ldlibs += -lmorda -lmorda-opengl2-ren -lpuu -lpapki -lunikod -lstdc++

this_out_dir := build

$(eval $(prorab-build-app))
