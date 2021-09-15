###############
# 	 Linux   	#
###############

COMPILER = g++

RMDIR = rm -rdf

RM = rm -f

DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@

LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

INC_PATHS = -I$(INC_PATH) $(addprefix -I,$(SDL_INC_PATH))

FLAGS = -std=c++17 -Wall -Wextra -pedantic -Wno-unused-parameter -Werror=init-self

DFLAGS = -ggdb -O0 -DEBUG

RFLAGS = -O3 -mtune=native

INC_PATH = src
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep


CPP_FILES  = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES  = $(wildcard $(INC_PATH)/*.hpp)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.hpp=)))
DEP_FILES  = $(addprefix $(DEP_PATH)/, $(addsuffix .d, $(FILE_NAMES)))
OBJ_FILES  = $(addprefix $(BIN_PATH)/, $(notdir $(CPP_FILES:.cpp=.o)))

EXEC = game

###############
# 	Windows 	#
###############


ifeq ($(OS), Windows_NT)

RMDIR = rd /s /q

rm = del /q

SDL_PATHS = C:/SDL2/x86_64-w64-mingw32 C:/Tools/msys64/mingw64

SDL_INC_PATH += $(addsuffix /include, $(SDL_PATHS))
LINK_PATH = $(addprefix -L, $(addsuffix /lib, $(SDL_PATHS)))
# FLAGS += -mwindows
# DFLAGS += -mconsole
LIBS := -lmingw32 -lSDL2main $(LIBS)

EXEC := build/$(EXEC).exe

else

UNAME_S := $(shell uname -s)


###############
# 	  MAC		  #
###############

ifeq ($(UNAME_S), Darwin)

LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

endif
endif

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/, $(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

.SECONDEXPANSION:
	.include $$(DEP_FILES)

clean:
	-$(RMDIR) $(DEP_PATH)
	-$(RMDIR) $(BIN_PATH)
	-$(RM) $(EXEC)

.PRECIOUS: $(DEP_FILES)
.PHONY: release debug clean folders help

release: FLAGS += $(RFLAGS)
release: $(EXEC)

debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

folders:
ifeq ($(OS), Windows_NT)
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
else 
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif 

print-%: ; @echo $* = $($*)

help:
ifeq ($(OS), Windows_NT)
	@echo.
endif
	@echo Available targets:
	@echo - release: Builds the release version
	@echo - debug: Builds the debug version 
	@echo - clean: Cleans generated files
	@echo - folders: Generates projects directories
	@echo - help: Mostra as tabelas comandos
ifeq ($(OS), Windows_NT)
	@echo.
endif