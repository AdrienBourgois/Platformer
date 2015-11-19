TARGET = openGl 

SRC = 	main.cpp\
		Device.cpp\
		TxtLogger.cpp\
		Window.cpp\
		Shaders.cpp\
		Driver.cpp\
		SceneManager.cpp\
		SceneNode.cpp\
		CameraSceneNode.cpp\
		MeshSceneNode.cpp\
		maths/Utility.cpp\
		maths/Matrix.cpp\
		maths/Vector.cpp\
		Mesh.cpp\
		Texture.cpp\
		imgui.cpp\
		imgui_demo.cpp\
		imgui_draw.cpp\
		imgui_impl.cpp\
		GUI_DebugWindow.cpp\
		GUI_OpenFile.cpp\
		FileUtility.cpp\
		Material.cpp\
		GUI_EditMaterialWindow.cpp\
		GUI_ChangeTextureGroupWindow.cpp\
		SaveToJson.cpp\
		GUI_EditShader.cpp\
		GUI_Window.cpp\
		LoadFromJson.cpp\
		Screenshot.cpp\

LIBS = SDL2 GL GLEW SDL2_image

BIN_DIR = bin/
OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/ usr/include/SDL2/ 

OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRC))
DEPENDENCIES = $(OBJ:.o=.d)
ARBO = $(sort $(dir $(DEPENDENCIES) $(OBJ_DIR)))
INCLUDES = $(addprefix -I,$(INC_DIR))
LIBRARIES = $(addprefix -l,$(LIBS))
CXXFLAGS = -MMD -W -Wall -Werror
LDFLAGS = -W -Wall -Werror
CXX = g++ -std=c++14

.PHONY: all clean fclean re debug release

release: CXXFLAGS += -O3
release: LDFLAGS += -O3
release: all

debug: CXXFLAGS += -O0 -g3
debug: LDFLAGS += -O0 -g3
debug: all

all: $(TARGET)

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
	$(RM) $(TARGET)

re: fclean release

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDES)
