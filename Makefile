# Makefile for ModulusPlus project

CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -Iinc
LDFLAGS := 

TARGET  := modulus_plus

# Source files
SRCS    := examples/main.c src/modplus.c src/montgomery.c src/uint256.c
# Object files (replace .c with .o)
OBJS    := $(SRCS:.c=.o)


all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Compile step (pattern rule for all .c → .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Optional: add a "run" target for convenience
run: $(TARGET)
	./$(TARGET)
