all: clean compile test checkstyle

compile:
	g++ -o ApproximateEulersNumberMain ApproximateEulersNumberMain.cpp
	g++ -o ApproximateEulersNumberTest ApproximateEulersNumberTest.cpp -lgtest -lpthread

test:
	./ApproximateEulersNumberTest

checkstyle:
	python3 ../cpplint.py *.cpp

clean:
	rm -f ApproximateEulersNumberMain
	rm -f ApproximateEulersNumberTest