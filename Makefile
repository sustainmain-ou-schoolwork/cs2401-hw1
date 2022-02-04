CC = g++
CFLAGS = -g -Wall -std=c++11

a.out: commented_main.o checkbook.o
	$(CC) $(CFLAGS) commented_main.o checkbook.o -o a.out

commented_main.o: commented_main.cc checkbook.o checkbook.h
	$(CC) $(CFLAGS) -c commented_main.cc

checkbook.o: checkbook.cc checkbook.h check.o check.h
	$(CC) $(CFLAGS) -c checkbook.cc

check.o: check.cc check.h date.o date.h
	$(CC) $(CFLAGS) -c check.cc

date.o: date.cc date.h
	$(CC) $(CFLAGS) -c date.cc

clean:
	rm -rf *.o a.out