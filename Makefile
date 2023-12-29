TARGET = build/reinhard
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/obj/%.o, $(SRC))

CFLAGS = -std=c17 -O3 -Wall -Werror -Wpedantic
INCLUDE = -Iinclude
LIBS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

default: $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $@ $? $(LIBS) $(CFLAGS)

build/obj/%.o: src/%.c
	gcc -c -o $@ $< $(INCLUDE) $(LIBS) $(CFLAGS)


# compile shaders

VERTS = $(wildcard shaders/*.vert)
FRAGS = $(wildcard shaders/*.frag)
SHADER_TARGET = $(patsubst shaders/%.vert, build/shaders/%.vert.spv, $(VERTS)) $(patsubst shaders/%.frag, build/shaders/%.frag.spv, $(FRAGS))

compile_shaders: $(SHADER_TARGET)

build/shaders/%.vert.spv: shaders/%.vert
	glslc $? -o $@

build/shaders/%.frag.spv: shaders/%.frag
	glslc $? -o $@


# chalk is a lazy wittwle guvy uwu

clean:
	rm -r build/*
	mkdir build/obj build/shaders

setup:
	mkdir build build/obj build/shaders

lazy:
	make clean
	make
	make compile_shaders

run:
	$(TARGET)
