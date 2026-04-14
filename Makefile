CC = gcc
CFLAGS = -Wall -Werror -Wextra
C_OBJECT_FLAGS = -fno-builtin -c
TARGET = bah-cil

# Directories
BUILD_DIR = build
SOURCE_DIR = src

# Source & Object files directories
SOURCE_C_FILES = $(shell find $(SOURCE_DIR) -name *.c -not -name "main.c") # all C files except "main.c"
SOURCE_OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE_C_FILES))

.PHONY: build clean

build: $(BUILD_DIR)/$(TARGET)
	chmod +x $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SOURCE_OBJECT_FILES)
	$(CC) $(CFLAGS) $(SOURCE_OBJECT_FILES) $(SOURCE_DIR)/main.c -o $(BUILD_DIR)/$(TARGET)

$(SOURCE_OBJECT_FILES): $(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	mkdir -p $(dir $@) && $(CC) $(C_OBJECT_FLAGS) $(patsubst $(BUILD_DIR)/%.o, $(SOURCE_DIR)/%.c, $@) -o $@

clean:
	rm -rf ./build/*
