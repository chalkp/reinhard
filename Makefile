TARGET = bin/reinhard
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/*.cpp, obj/%.o, $(SRC))

INCLUDE_IMGUI = -Iinclude/imgui -Iinclude/imgui/backends
INCLUDE = -Iinclude $(INCLUDE_IMGUI)

CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

default: $(TARGET)

setup:
	mkdir bin obj
	git clone --recursive https://github.com/ocornut/imgui.git -b docking include/imgui

clean:
	rm -f bin/*
	rm -f obj/*.o

$(TARGET): $(OBJ)
	g++ -o $@ $? $(INCLUDE) $(LDFLAGS)

obj/%.o: src/%.cpp
	g++ $(CFLAGS) -c $< -o $@ $(INCLUDE) $(LDFLAGS)

lazy:
	make clean
	make
	$(TARGET)

run:
	$(TARGET)
