.SUFFIXES:
.PHONY: compile test checkstyle clean
.PRECIOUS: %.o

CXX = g++ -g
HEADERS = $(wildcard *.h)
NAME = GameOfLife

all: compile

compile: $(NAME)Main test checkstyle

test: $(NAME)Test
	./$(NAME)Test

checkstyle:
	python3 ../cpplint.py --repository=. *.cpp

clean:
	rm -f *.o
	rm -f *Main
	rm -f *Test
	rm -f core

%Main: %Main.o %.o $(HEADERS)
	$(CXX) -o $(NAME)Main $^ -lncurses

%Test: %Test.o $(NAME).o $(HEADERS)
	$(CXX) -o $@ $^ -lncurses -lgtest -lgtest_main -lpthread

%.o: %.cpp $(HEADERS)
	$(CXX) -c $<