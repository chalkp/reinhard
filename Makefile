# SPDX-License-Identifier: MIT

TARGET = build/reinhard
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/obj/%.o, $(SRC))

CC = gcc
CFLAGS = -std=c17 -O2 -Wall -Wextra -Wpedantic -Werror
INCLUDE = -Iinclude
LIBS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

.PHONY: default all clean install setup lazy run

default: all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $? $(LIBS) $(CFLAGS)

build/obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(INCLUDE) $(LIBS) $(CFLAGS)


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
	rm -rf build
	mkdir build build/obj build/shaders

install:
	wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.268-jammy.list https://packages.lunarg.com/vulkan/1.3.268/lunarg-vulkan-1.3.268-jammy.list
	sudo apt update
	sudo apt install gcc make libc6 libx11-dev vulkan-sdk libglfw3 libglfw3-dev libxi-dev libxxf86vm-dev
	sudo apt upgrade

setup:
	mkdir build build/obj build/shaders

lazy: clean all compile_shaders


run: $(TARGET)
	./$(TARGET)
