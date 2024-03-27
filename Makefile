# install dependencies
install:
	wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.268-jammy.list https://packages.lunarg.com/vulkan/1.3.268/lunarg-vulkan-1.3.268-jammy.list
	sudo apt update
	sudo apt install gcc make cmake libc6 libx11-dev vulkan-sdk libglfw3 libglfw3-dev libxi-dev libxxf86vm-dev
	sudo apt upgrade


# compile shaders
VERTS = $(wildcard shaders/*.vert)
FRAGS = $(wildcard shaders/*.frag)
SHADER_TARGET = $(patsubst shaders/%.vert, build/shaders/%.vert.spv, $(VERTS)) $(patsubst shaders/%.frag, build/shaders/%.frag.spv, $(FRAGS))

compile_shaders: $(SHADER_TARGET)

build/shaders/%.vert.spv: shaders/%.vert
	glslc $? -o $@

build/shaders/%.frag.spv: shaders/%.frag
	glslc $? -o $@