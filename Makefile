####################################################################################################
# Config

NAME = on_time_calc

CC = gcc
CFLAGS = -Wall

SRCS = ./src/*.c

####################################################################################################

all:
	$(CC) $(CFLAGS) $(SRCS) -o ./bin/$(NAME)

clean:
	$(RM) ./bin/out

run:
	./bin/$(NAME) ./data/test_file.txt ./data/out_file.txt

cppcheck:
	cppcheck --enable=all ./src/

test:
	$(CC) -ggdb -pthread $(CFLAGS)  ./src/file_parser.c ./src/cluster.c ./tests/*.c -lcheck_pic -lrt -lm -lsubunit -o ./bin/test && ./bin/test

memtest:
	valgrind --tool=memcheck --leak-check=full ./bin/$(NAME) 
