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
      ./FolderADT/treebalasan.c \
      ./features/balasan.c \
      ./features/utas.c \
      ./FolderADT/listutas.c \
      ./features/kicauan.c \
      ./FolderADT/grafpertemanan.c \
      ./FolderADT/prioqueuechar.c \
      ./features/teman.c \
      ./features/save_load.c

# Drivers source files
DRIVERS = ./FolderADT/grafpertemanandriver.c \
          ./FolderADT/listkicaudriver.c \
          ./FolderADT/datetimedriver.c \
          ./FolderADT/listpenggunadriver.c \
          ./FolderADT/prioqueuechardriver.c \
          ./FolderADT/stackdrafdriver.c \
          ./FolderADT/treebalasandriver.c \
          ./FolderADT/listutasdriver.c \
          

# Object files (automatically generated from source files)
OBJ = $(SRC:.c=.o)
DRIVER_EXES = $(DRIVERS:.c=)

# Executable name
EXECUTABLE = main

# Default target: build the main executable and all drivers
all: $(EXECUTABLE) drivers

# Rule to build the main executable
$(EXECUTABLE): $(OBJ)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Compilation completed. Executable: $(EXECUTABLE)"

# Rule to build all drivers
drivers: $(DRIVER_EXES)

# Rule to build each driver executable
$(DRIVER_EXES): % : %.o $(filter-out main.o, $(OBJ))
	@echo "Compiling driver $@..."
	@$(CC) $(CFLAGS) -o ./$(notdir $@) $^
	@echo "Driver $@ compiled."

# Rule to build driver object files
$(DRIVERS:.c=.o): %.o : %.c
	@echo "Compiling driver object file $@..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Driver object file $@ compiled."

# Rule to build object files from source files
%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$< compiled."

# Clean up object files and the executable
clean:
	@rm -f *.o $(EXECUTABLE) $(DRIVER_EXES)
	@rm -f FolderADT/*.o
	@rm -f features/*.o
	@echo "Cleanup completed."

# Phony targets
.PHONY: all clean drivers
