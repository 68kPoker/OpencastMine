
#include "OpencastMine.hpp"


int main(void)
{
	const int metal = 200000;
	const int costs[MAX_LEVEL] = { 3000, 6000, 8000, 10000 };
	const double values[MAX_LEVEL][MAX_LEVEL][MAX_LEVEL] = {
		1.5, 1.5, 1.5, 0.75,
		1.5, 2.0, 1.5, 0.75,
		1.0, 1.0, 0.75, 0.5,
		0.75, 0.75, 0.5, 0.25,
		
		4.0, 4.0, 2.0, 0,
		3.0, 3.0, 1.0, 0,
		2.0, 2.0, 0.5, 0,
		0, 0, 0, 0 ,

		12.0, 6.0, 0, 0,
		5.0, 4.0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,

		6.0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	OpencastMine *mine = new OpencastMine(costs, metal, values);
	return(0);


}