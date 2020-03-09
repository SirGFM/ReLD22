
# To find every .c file in src:
#   FILES := $(call rwildcard, src/, *.c)
# To find all the .c and .h files in src:
#   FILES := $(call rwildcard, src/, *.c *.h)
rwildcard=$(foreach d,$(wildcard $1*), \
    $(call rwildcard,$d/,$2) \
    $(filter $(subst *,%,$2),$d))

# For example
CSRC := $(call rwildcard, src, *.c)
CXXSRC := $(call rwildcard, src, *.cpp)
OBJS := $(CSRC:src/%.c=obj/%.o) $(CXXSRC:src/%.cpp=obj/%.o)

.SECONDARY: $(OBJS)
.PHONY: linux clean

myCFLAGS := $(CFLAGS) $(CXXFLAGS)
myCFLAGS := $(myCFLAGS) -I ./src -I ./src/core
myLDFLAGS := $(LDFLAGS)
myLDLIBS := $(LDLIBS)
myLDLIBS := $(myLDLIBS) -lGLEW -lGLU -lGL
# iirc, Windows also requires -lSDLmain
myLDLIBS := $(myLDLIBS) -lSDL

GAME := ReLoneliness

linux: bin/linux/$(GAME).app

%.app: $(OBJS) | %.mkdir
	$(CXX) $(myCFLAGS) -o $@ $^ $(myLDFLAGS) $(myLDLIBS)

obj/%.o: src/%.cpp
	$(CXX) $(myCFLAGS) -o $@ -c $<
obj/%.o: src/%.c
	$(CXX) $(myCFLAGS) -o $@ -c $<

-include $(OBJS:%.o=%.mkdir)
%.mkdir:
	@ mkdir -p $(@D)
	@ touch $@

clean:
	rm -rf ./bin/ ./obj/
