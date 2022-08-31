#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Pixel.h"
using namespace std;

struct Header
{
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrgin;
	short colorMapLength;
	char colorMapDepth;
	short xOrgin;
	short yOrgin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
	vector<pixel> imageData;
};
