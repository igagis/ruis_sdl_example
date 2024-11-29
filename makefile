include prorab.mk

this_name := sdl2_example

$(eval $(call prorab-config, config))

this_srcs := $(call prorab-src-dir, src)

ifeq ($(os),windows)
    
# else ifeq ($(os),macosx)
#     this_ldlibs += `pkg-config --libs sdl2 glew` -framework OpenGL # -framework Cocoa
else ifeq ($(os),linux)
    this_ldlibs += -lGLEW
    this_ldlibs += -lGL
    this_ldlibs += -lSDL2
endif

this_ldlibs += -l utki
this_ldlibs += -l papki
this_ldlibs += -l ruis
this_ldlibs += -l ruis-render-opengl

$(eval $(prorab-build-app))
