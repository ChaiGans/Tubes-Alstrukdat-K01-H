# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g

# Source files
SRC = main.c \
      ./FolderADT/primitive_data/data.c \
      ./FolderADT/wordmachine/wordmachine.c \
      ./FolderADT/wordmachine/charmachine.c \
      ./FolderADT/matrix/matrix.c \
      ./FolderADT/pengguna/listpengguna.c \
      ./FolderADT/pengguna/profile.c \
      ./FolderADT/kicauan/listkicau.c \
      ./features/user.c \
      ./features/draf.c \
      ./FolderADT/draf/stackdraf.c \
      ./FolderADT/datetime/time.c \
      ./FolderADT/datetime/datetime.c \
      ./FolderADT/balasan/treebalasan.c \
      ./features/balasan.c \
      ./features/utas.c \
      ./FolderADT/utas/listutas.c \
      ./features/kicauan.c \
      ./FolderADT/pertemanan/grafpertemanan.c \
      ./FolderADT/queue/prioqueuechar.c \
      ./features/teman.c \
      ./features/save_load.c

# Drivers source files
DRIVERS = ./FolderADT/pertemanan/grafpertemanandriver.c \
          ./FolderADT/kicauan/listkicaudriver.c \
          ./FolderADT/datetime/datetimedriver.c \
          ./FolderADT/pengguna/listpenggunadriver.c \
          ./FolderADT/queue/prioqueuechardriver.c \
          ./FolderADT/draf/stackdrafdriver.c \
          ./FolderADT/balasan/treebalasandriver.c \
          ./FolderADT/utas/listutasdriver.c \
          ./FolderADT/matrix/matrixdriver.c \
          ./FolderADT/pengguna/profiledriver.c \
          ./FolderADT/wordmachine/wordmachinedriver.c \

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
	@rm -f FolderADT/balasan/*.o
	@rm -f FolderADT/datetime/*.o
	@rm -f FolderADT/draf/*.o
	@rm -f FolderADT/kicauan/*.o
	@rm -f FolderADT/matrix/*.o
	@rm -f FolderADT/pengguna/*.o
	@rm -f FolderADT/pertemanan/*.o
	@rm -f FolderADT/primitive_data/*.o
	@rm -f FolderADT/queue/*.o
	@rm -f FolderADT/wordmachine/*.o
	@rm -f FolderADT/utas/*.o
	@rm -f features/*.o
	@echo "Cleanup completed."

# Phony targets
.PHONY: all clean drivers
