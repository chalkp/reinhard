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

clean:
	rm -r build/*
	mkdir build/obj

setup:
	mkdir build build/obj

lazy:
	make clean
	make

run:
	$(TARGET)
