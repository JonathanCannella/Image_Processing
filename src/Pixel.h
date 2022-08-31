#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct pixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	pixel()
	{
		blue = 0;
		green = 0;
		red = 0;
	}
};

