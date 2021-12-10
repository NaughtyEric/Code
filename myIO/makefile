mystdio: main.o libmystdio.so
	clang++ -o mystdio main.o -L. -lmystdio -Wl,-rpath=.
libmystdio.so: myscanf.o myprintf.o
	clang++ -shared -o libmystdio.so myscanf.o myprintf.o
main.o: main.cpp mystdio.hpp
	clang++ -fPIC -c main.cpp
myscanf.o: myscanf.cpp mystdio.hpp utilities.hpp
	clang++ -fPIC -c myscanf.cpp
myprintf.o: myprintf.cpp mystdio.hpp utilities.hpp
	clang++ -fPIC -c myprintf.cpp
clean:
	rm -rf mystdio *.o *.a *.so
