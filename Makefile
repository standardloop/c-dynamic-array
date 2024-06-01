include Makefile.properties

all: build run

clean:
	rm main

build:
	@$(CC) $(CC_FLAGS) \
	main.c \
	dynamic-array.c \
	-o main

run:
	@./main
