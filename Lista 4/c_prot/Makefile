CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2 -MMD -MP

BUILD_DIR = build

SRCS = $(wildcard *.c) # Finds all .c files
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS)) # Maps all %.c files to a curresponding %.o file
DEPS = $(patsubst %.c, $(BUILD_DIR)/%.d, $(SRCS)) # Create a list of dependency files that GCC will generate

TARGET = b64

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

# Rule to create the build directory.
$(BUILD_DIR):
	mkdir -p $@

run:
	@./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)

-include $(DEPS)
