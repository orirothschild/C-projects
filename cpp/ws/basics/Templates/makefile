CC = g++
CCFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g
SHARED_OBJ_NAME = statistician
LFLAGS = -I./../../ -I../../../include

.PHONY: all
all: statistician.so

statistician.o: statistician.cpp statistician.hpp
			$(CC) $(CCFLAGS) -c -fPIC $(LFLAGS) $< -o $@

statistician.so : statistician.o
			$(CC) $(CCFLAGS) -shared $< -o $@

.PHONY : clean
clean:
	rm -f *.o *.so