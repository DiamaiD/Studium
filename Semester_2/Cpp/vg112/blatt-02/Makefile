.SUFFIXES:
all: clean compile test checkstyle

compile: ApproximateEulersNumberMain

test: ApproximateEulersNumberTest
	./ApproximateEulersNumberTest

ApproximateEulersNumberMain: ApproximateEulersNumberMain.o  ApproximateEulersNumber.o
	g++ -o  ApproximateEulersNumberMain ApproximateEulersNumberMain.o ApproximateEulersNumber.o

ApproximateEulersNumberTest: ApproximateEulersNumberTest.cpp ApproximateEulersNumber.o ApproximateEulersNumberTest.o
	g++ -o ApproximateEulersNumberTest ApproximateEulersNumberTest.o ApproximateEulersNumber.o -lgtest -lpthread

ApproximateEulersNumberTest.o: ApproximateEulersNumberTest.cpp
	g++ -c ApproximateEulersNumberTest.cpp

ApproximateEulersNumberMain.o: ApproximateEulersNumberMain.cpp
	g++ -c ApproximateEulersNumberMain.cpp

ApproximateEulersNumber.o: ApproximateEulersNumber.cpp ApproximateEulersNumber.h
	g++ -c ApproximateEulersNumber.cpp

checkstyle:
	python3 ../cpplint.py --repository=. *.cpp *.h

clean:
	rm -f ApproximateEulersNumberMain
	rm -f ApproximateEulersNumberTest
	rm -f *.o