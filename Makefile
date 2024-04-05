CC = clang
# clang's default dwarf is v5, for valgrind compatibility
CFLAGS = -Wall -Wextra -gdwarf-4 -glldb

TARGET = students_research
SRC_FILES = main.c utils.c 
OBJ_FILES = $(SRC_FILES:.c=.o)

$(TARGET): $(OBJ_FILES)
	@echo "Linking object files"
	$(CC) $^ $(CFLAGS) -o $@

%.o: %.c
	@echo "Compiling object files"
	$(CC) $(CFLAGS) -c $< -o $@

fullclean:
	@echo "Deleting all compiled files."
	rm -f $(OBJ_FILES) $(TARGET)

clean:
	@echo "Removing object files and executable"
	rm -f $(OBJ_FILES) 

run:
	@echo "Running the main executable if exits with default args."
	./$(TARGET) 40 5

valgrind:
	@echo "Memcheck with valgrind"
	valgrind --leak-check=full ./$(TARGET)

debug:
	@echo "debug with lldb"
	lldb ./$(TARGET)
