CFLAGS = -Wall -Wextra -pedantic-errors -Wno-deprecated -O3 -march=native

lb: lb.cpp util.hpp
	g++ $(CFLAGS) -o lb -Ieigen-3.4.0 lb.cpp

ub: ub.cpp util.hpp
	g++ $(CFLAGS) -o ub -Ieigen-3.4.0 ub.cpp
