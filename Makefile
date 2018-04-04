all:
	gcc -Wall  ./src/*.c -o ./bin/out

clean:
	$(RM) ./bin/out

run:
	./bin/out ./data/test_file.txt ./data/out_file.txt

cppcheck:
	cppcheck --enable=all ./src/

test:
	gcc ./src/file_parser.c ./tests/*.c -pthread -lcheck_pic -pthread -lrt -lm -lsubunit -o ./bin/test; ./bin/test

memtest:
	valgrind --tool=memcheck --leak-check=full ./bin/out 
