all:mystdio libmystdio.a main.o myscanf.o myprintf.o
	
mystdio: main.o libmystdio.a
	clang++ -o mystdio main.o -L. -lmystdio -g -Wall
libmystdio.a: myscanf.o myprintf.o
	ar cr libmystdio.a myprintf.o myscanf.o
main.o: main.cpp mystdio.hpp
	clang++ -c main.cpp -g -Wall
myscanf.o: myscanf.cpp mystdio.hpp utilities.hpp
	clang++ -c myscanf.cpp -g -Wall
myprintf.o: myprintf.cpp mystdio.hpp utilities.hpp
	clang++ -c myprintf.cpp -g -Wall
clean:
	rm -rf mystdio *.o *.a *.a
