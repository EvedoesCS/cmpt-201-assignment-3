# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -MMD -MP

# Target executable
TARGET := dashboard

# Source and object files
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

# Default target
all: $(TARGET)

# Link all object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Include header dependencies
-include $(DEPS)

# Clean
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

.PHONY: all clean
