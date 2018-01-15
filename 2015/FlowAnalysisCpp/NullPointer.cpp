#include "Point.hpp"

#include <cstdlib>

int main(int argc, char* argv[])
{
	Point* point = 0;
	if (argc > 3) {
		point = new Point(atoi(argv[1]), atoi(argv[2]));
	}
	point->reflectAcrossX();
	
	return 0;
}
