include Makefile.properties

all: build run

clean:
	@rm $(EXECUTABLE_NAME)

build:
	@$(CC) $(CC_FLAGS) \
	main.c \
	dynamic-array.c \
	util.c \
	-o $(EXECUTABLE_NAME)

run:
	@./$(EXECUTABLE_NAME)

check_leaks:
	@leaks --atExit -- ./$(EXECUTABLE_NAME)
