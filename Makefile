TARGET = build/reinhard
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/obj/%.o, $(SRC))

CFLAGS = -std=c17 -O3
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

install:
	wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.268-jammy.list https://packages.lunarg.com/vulkan/1.3.268/lunarg-vulkan-1.3.268-jammy.list
	sudo apt update
	sudo apt install vulkan-sdk libglfw3 libglfw3-dev

setup:
	mkdir build build/obj build/shaders

lazy:
	make clean
	make
	make compile_shaders

run:
	$(TARGET)
