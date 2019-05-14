########### Path Configurations ########### 
export SOURCE_DIR   := $(CURDIR)
export BIN          := $(SOURCE_DIR)/bin
export LIB_DIR      := $(SOURCE_DIR)/lib
export DEP          := $(SOURCE_DIR)/dep
export OBJ          := $(SOURCE_DIR)/obj
export OUT_DIR      := $(SOURCE_DIR)/out
export DUMP         := $(BIN) $(DEP) $(LIB_DIR) $(OBJ)
export EXECUTABLE   := $(BIN)/exe
export EXT_LIB_PATH := $(SOURCE_DIR)/external
export EXT_LIBS     := 	# Path of external libs for linking filed in options.mk

########### Compile Flags ########### 
export COMPILE = $(CXX) $$(INCLUDE_DIR) -L $(LIB_DIR)	# $$(INCLUDE_DIR) is passed to sub-make to fill and use

########### Make Flags ########### 
export MAKE_FLAGS :=--no-print-directory 

########### Default Target ###########
all: $(DUMP)

########## Regular Targets ###########
$(DUMP):
	mkdir $@

clean:
	rm -rf $(DUMP)

