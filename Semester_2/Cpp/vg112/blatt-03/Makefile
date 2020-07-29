.SUFFIXES:
.PHONY: compile test checkstyle clean

HEADERS = Ball.h
CXX = g++

all: compile test checkstyle

compile: BallMain

checkstyle:
	python3 ../cpplint.py --repository=. *.h *.cpp

test: BallTest
	./BallTest

clean:
	rm -f *.o
	rm -f *Main
	rm -f *Test

BallMain: Ball.o BallMain.o
	$(CXX) -o BallMain BallMain.o Ball.o -lncurses

BallTest: Ball.o BallTest.o
	$(CXX) -o BallTest BallTest.o Ball.o -lgtest -lpthread -lncurses -lgtest_main

%.o: %.cpp $(HEADERS)
	$(CXX) -c $<
