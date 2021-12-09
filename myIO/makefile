CMDS = $("-D LOCAL -Wall -Werror -std=c++17")

main: libmystdio.a main.o
	clang++ -o mystdio main.o -L. -lmystdio -Wl,-rpath=. ${CMDS}
#            -L.当前目录寻找 -l(A)
myprintf.o:
	clang++ myprintf.cpp -c $(CMDS)

myscanf.o:
	clang++ myscanf.cpp -c $(CMDS)

libmystdio.a: myprintf.o myscanf.o
	ar cr libmystdio.a myscanf.o myprintf.o

main.o:
	clang++ main.cpp -c $(CMDS)


clean:
	rm -rf *.o
	rm -rf *.a