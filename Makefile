# from Google Gemini

# Compiler
CC = gcc

# Compiler flags:
# -Wall -Wextra = Show all good warnings
# -std=c99      = Use the C99 standard
# -g            = Include debug symbols
CFLAGS = -Wall -Wextra -std=c99 -g

# Executable name
EXE = robot_prog.exe

# Source files
SRCS = main.c robot.c arena.c graphics.c

# Object files (auto-generated from SRCS)
OBJS = $(SRCS:.c=.o)

# --- Targets ---

# Default target (what happens when you just type "make")
all: $(EXE)

# Linking: Create the executable from the object files
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

# Compilation: Create object files from source files
# This is a pattern rule that says how to build any .o from a .c
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# --- Utility Targets ---

# "make run": Compile and run the program
run: $(EXE)
	./$(EXE) | java -jar drawapp-4.5.jar

# "make clean": Remove all compiled files
clean:
	rm -f $(OBJS) $(EXE)

# Phony targets aren't actual files
.PHONY: all run clean