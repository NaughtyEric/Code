all:mystdio libmystdio.a main.o myscanf.o myprintf.o
	
mystdio: main.o libmystdio.a
	clang++ -o mystdio main.o -L. -lmystdio -Wall -g -std=c++17
libmystdio.a: myscanf.o myprintf.o
	ar cr libmystdio.a myprintf.o myscanf.o
main.o: main.cpp mystdio.hpp
	clang++ -c main.cpp -Wall -g -std=c++17
myscanf.o: myscanf.cpp mystdio.hpp utilities.hpp
	clang++ -c myscanf.cpp -Wall -g -std=c++17
myprintf.o: myprintf.cpp mystdio.hpp utilities.hpp
	clang++ -c myprintf.cpp -Wall -g -std=c++17
clean:
	rm -rf mystdio *.o *.a *.a
