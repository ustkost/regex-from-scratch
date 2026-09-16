# https://makefiletutorial.com/#makefile-cookbook

TARGET_EXEC := regex
BUILD_DIR := ./build
SRC_DIRS := ./src ./test
INC_DIRS := ./src ./test

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CC := gcc
CFLAGS := -Wall -g # -fsanitize=address
# LDFLAGS := -fsanitize=address
CPPFLAGS := $(addprefix -I,$(INC_DIR)) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
