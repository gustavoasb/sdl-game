#CC specifies which compiler we're using
CC = g++

# Directories
SRC_DIR = src
BUILD_DIR = build

TARGET = game

# Source files
# SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS = $(SRC_DIR)/*.cpp

BIN = $(BUILD_DIR)/$(TARGET)

# INCLUDE_PATHS specifies the additional include paths we'll need
# INCLUDE_PATHS = -IC:\msys64\mingw64\include\SDL2

# LIBRARY_PATHS specifies the additional library paths we'll need
# LIBRARY_PATHS = -LC:\msys64\mingw64\lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# 	-w suppresses all warnings
# 	-Wl,-subsystem,windows gets rid of the console window
# COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS = -g -Wall -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2


#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

.PHONY: all

all, $(BIN): $(SRCS) | $(BUILD_DIR)
	$(CC) $(SRCS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BIN)

$(BUILD_DIR):
	mkdir -p $@

exec: $(BIN)
	$(BIN).exe

clean:
	@$(RM) -rv $(BUILD_DIR)/*