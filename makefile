TARGET = plateformer 

SRC = 	main.cpp\
		device.cpp\
		txtLogger.cpp\
		window.cpp\
		shaders.cpp\
		driver.cpp\
		sceneManager.cpp\
		sceneNode.cpp\
		cameraSceneNode.cpp\
		meshSceneNode.cpp\
		maths/utility.cpp\
		maths/matrix.cpp\
		maths/vector.cpp\
		maths/polyhedron.cpp\
		maths/collider.cpp\
		maths/colliderManager.cpp\
		mesh.cpp\
		texture.cpp\
		imgui.cpp\
		imgui_demo.cpp\
		imgui_draw.cpp\
		imgui_impl.cpp\
		guiDebugWindow.cpp\
		guiOpenFile.cpp\
		fileUtility.cpp\
		material.cpp\
		guiEditMaterialWindow.cpp\
		guiChangeTextureGroupWindow.cpp\
		saveToJson.cpp\
		guiEditShader.cpp\
		guiWindow.cpp\
		loadFromJson.cpp\
		screenshot.cpp\

LIBS = SDL2 GL GLEW SDL2_image

MODE = release
BIN_DIR = bin/$(MODE)/

OBJ_DIR = obj/$(MODE)/

SRC_DIR = src/

INC_DIR = include/ usr/include/SDL2/ 

OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRC))

DEPENDENCIES = $(OBJ:.o=.d)

ARBO = $(sort $(dir $(DEPENDENCIES) $(OBJ_DIR)))

INCLUDES = $(addprefix -I,$(INC_DIR))
LIBRARIES = $(addprefix -l,$(LIBS))
CXXFLAGS = -MMD -W -Wall -Werror
CPPFLAGS =
LDFLAGS = -W -Wall -Werror
CXX = g++ -std=c++14

.PHONY: all clean fclean re debug release

all: $(MODE)

release: CXXFLAGS += -O3
release: LDFLAGS += -O3
release: $(TARGET)

debug: CXXFLAGS += -O0 -g3
debug: LDFLAGS += -O0 -g3
debug: CPPFLAGS += -D_DEBUG
debug: $(TARGET)

master: CXXFLAGS += -O3
master: LDFLAGS += -O3
master: CPPFLAGS += -D_DEBUG
master: $(TARGET)

$(TARGET): $(BIN_DIR)$(TARGET) | $(ARBO)

$(BIN_DIR)$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LIBRARIES)

$(OBJ): | $(ARBO)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(ARBO):
	mkdir -p $@

-include $(DEPENDENCIES)

clean:
	$(RM) $(OBJ)
	$(RM) $(DEPENDENCIES)
	$(RM) -r $(ARBO)
	$(RM) .*.swp
	$(RM) logs/*
	$(RM) assets/json/*

fclean: clean
	$(RM) $(BIN_DIR)$(TARGET)
	$(RM) -r $(BIN_DIR)

re: fclean all

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $< $(INCLUDES)
