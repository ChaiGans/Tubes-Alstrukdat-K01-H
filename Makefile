# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g

# Source files
SRC = main.c \
      ./FolderADT/data.c \
      ./FolderADT/wordmachine.c \
      ./FolderADT/charmachine.c \
      ./FolderADT/matrix.c \
      ./FolderADT/listpengguna.c \
      ./FolderADT/profile.c \
      ./FolderADT/listkicau.c \
      ./features/user.c \
      ./features/draf.c \
      ./FolderADT/stackdraf.c \
      ./FolderADT/time.c \
      ./FolderADT/datetime.c \
      ./FolderADT/treebalasan.c

# Object files (automatically generated from source files)
OBJ = $(SRC:.c=.o)

# Executable name
EXECUTABLE = main

# Default target: build the executable
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJ)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Compilation completed. Executable: $(EXECUTABLE)"

# Rule to build object files from source files
%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$< compiled."

# Clean up object files and the executable
clean:
	@del /Q *.o $(EXECUTABLE)
	@del /Q FolderADT\*.o
	@del /Q features\*.o
	@echo "Cleanup completed."


# Phony target to prevent conflicts with files of the same name
.PHONY: all clean
