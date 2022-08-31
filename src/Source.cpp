#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Header.h"
using namespace std;

//******************USE FOWARD SLASHES******************//

void readFiles(vector<Header>& imageFiles, vector<string>& filepath)
{
	for (int i = 0; i < filepath.size(); i++)
	{
		ifstream infile(filepath[i], ios_base::binary);
		//ifstream infile("car.tga", ios_base::binary);
		Header image;
		short h, w;

		infile.read(&image.idLength, sizeof(image.idLength));
		infile.read(&image.colorMapType, sizeof(image.colorMapType));
		infile.read(&image.dataTypeCode, sizeof(image.dataTypeCode));
		infile.read((char*)&image.colorMapOrgin, sizeof(image.colorMapOrgin));
		infile.read((char*)&image.colorMapLength, sizeof(image.colorMapLength));
		infile.read(&image.colorMapDepth, sizeof(image.colorMapDepth));
		infile.read((char*)&image.xOrgin, sizeof(image.xOrgin));
		infile.read((char*)&image.yOrgin, sizeof(image.yOrgin));
		infile.read((char*)&image.width, sizeof(image.width));
		w = image.width;
		infile.read((char*)&image.height, sizeof(image.height));
		h = image.height;
		infile.read(&image.bitsPerPixel, sizeof(image.bitsPerPixel));
		infile.read(&image.imageDescriptor, sizeof(image.imageDescriptor));

		//cout << w << endl << h << endl;

		for (short row = (h - 1); row >= 0; row--)
		{
			//cout << row << endl;
			for (short col = 0; col < w; col++)
			{
				//cout << col << endl;
				pixel p;
				infile.read((char*)&p.blue, sizeof(p.blue));
				infile.read((char*)&p.green, sizeof(p.green));
				infile.read((char*)&p.red, sizeof(p.red));
				image.imageData.push_back(p);
			}
		}
		imageFiles.push_back(image);
		infile.close();
	}
}

void writeFile(Header& image, const string& fileName)
{
	ofstream outFile(fileName, ios_base::binary);
	short w, h;

	outFile.write((char*)&image.idLength, sizeof(image.idLength));
	outFile.write((char*)&image.colorMapType, sizeof(image.colorMapType));
	outFile.write((char*)&image.dataTypeCode, sizeof(image.dataTypeCode));
	outFile.write((char*)&image.colorMapOrgin, sizeof(image.colorMapOrgin));
	outFile.write((char*)&image.colorMapLength, sizeof(image.colorMapLength));
	outFile.write((char*)&image.colorMapDepth, sizeof(image.colorMapDepth));
	outFile.write((char*)&image.xOrgin, sizeof(image.xOrgin));
	outFile.write((char*)&image.yOrgin, sizeof(image.yOrgin));
	outFile.write((char*)&image.width, sizeof(image.width));
	outFile.write((char*)&image.height, sizeof(image.height));
	outFile.write((char*)&image.bitsPerPixel, sizeof(image.bitsPerPixel));
	outFile.write((char*)&image.imageDescriptor, sizeof(image.imageDescriptor));

	for (unsigned int i = 0; i < image.imageData.size(); i++)
	{
		outFile.write((char*)&image.imageData[i].blue, sizeof(image.imageData[i].blue));
		outFile.write((char*)&image.imageData[i].green, sizeof(image.imageData[i].green));
		outFile.write((char*)&image.imageData[i].red, sizeof(image.imageData[i].red));
	}
	outFile.close();
}

void test()
{
	vector<string> outputPaths = { "examples/EXAMPLE_part1.tga", "examples/EXAMPLE_part2.tga", "examples/EXAMPLE_part3.tga",
								   "examples/EXAMPLE_part4.tga", "examples/EXAMPLE_part5.tga", "examples/EXAMPLE_part6.tga",
								   "examples/EXAMPLE_part7.tga", "examples/EXAMPLE_part8_b.tga", "examples/EXAMPLE_part8_g.tga",
								   "examples/EXAMPLE_part8_r.tga", "examples/EXAMPLE_part9.tga", "examples/EXAMPLE_part10.tga",
								   "examples/EXAMPLE_extracredit.tga"};
	vector<Header> outputs;
	vector<string> examplesPaths = { "output/part1.tga", "output/part2.tga", "output/part3.tga", "output/part4.tga",
									 "output/part5.tga", "output/part6.tga", "output/part7.tga", "output/part8_b.tga",
									 "output/part8_g.tga", "output/part8_r.tga", "output/part9.tga", "output/part10.tga",
									 "output/extracredit.tga"};
	vector <Header> examples;
	readFiles(outputs, outputPaths);
	readFiles(examples, examplesPaths);
	cout << " \n" << "Tests 8 through 10 correspond to files part8_b, part8_gand part8_r\n" << "Test 13 tests extracredit\n\n";
	for (unsigned int i = 0; i < outputPaths.size(); i++)
	{
		bool pass = 1;
		if (outputs[i].imageData.size() == examples[i].imageData.size())
		{
			for (unsigned int j = 0; j < outputs[i].imageData.size(); j++)
			{
				//cout << outputs[i].imageData[j].blue << " " << examples[i].imageData[j].blue << endl;
				if ((outputs[i].imageData[j].blue != examples[i].imageData[j].blue) || (outputs[i].imageData[j].green != examples[i].imageData[j].green) || (outputs[i].imageData[j].red != examples[i].imageData[j].red))
				{
					pass = 0;
				}
			}
		}
		else
		{
			pass = 0;
		}
		if (pass)
		{
			cout << "Test #" << i + 1 << "...... Passed!" << endl;
		}
		else
		{
			cout << "Test #" << i + 1 << "...... Failed!" << endl;
		}
	}
}

void task1(vector<Header>& images)
{
	Header part1;
	part1 = images[5];
	for (unsigned int i = 0; i < part1.imageData.size(); i++)
	{
		part1.imageData[i].blue = (float)((part1.imageData[i].blue * images[7].imageData[i].blue) / 255.0) + 0.5f;
		part1.imageData[i].green = (float)((part1.imageData[i].green * images[7].imageData[i].green) / 255.0) + 0.5f;
		part1.imageData[i].red = (float)((part1.imageData[i].red * images[7].imageData[i].red) / 255.0) + 0.5f;
	}
	writeFile(part1, "output/part1.tga");
}

void task2(vector<Header>& images)
{
	int b_;
	int g_;
	int r_;
	Header part2;
	part2 = images[6];
	for (unsigned int i = 0; i < part2.imageData.size(); i++)
	{
		b_ = (-(int)part2.imageData[i].blue + (int)images[0].imageData[i].blue);
		if (b_ < 0) { b_ = 0; }
		else if (b_ > 255) { b_ = 255; }
		g_ = (-(int)part2.imageData[i].green + (int)images[0].imageData[i].green);
		if (g_ < 0) { g_ = 0; }
		else if (g_ > 255) { g_ = 255; }
		r_ = (-(int)part2.imageData[i].red + (int)images[0].imageData[i].red);
		if (r_ < 0) { r_ = 0; }
		else if (r_ > 255) { r_ = 255; }
		part2.imageData[i].blue = b_;
		part2.imageData[i].green = g_;
		part2.imageData[i].red = r_;
	}
	writeFile(part2, "output/part2.tga");
}

void task3(vector<Header>& images)
{
	float b;
	float g;
	float r;
	Header part3 = images[9];
	Header temp = images[5];
	for (unsigned int i = 0; i < temp.imageData.size(); i++)
	{
		temp.imageData[i].blue = (float)((temp.imageData[i].blue * images[8].imageData[i].blue) / 255.0) + 0.5f;
		temp.imageData[i].green = (float)((temp.imageData[i].green * images[8].imageData[i].green) / 255.0) + 0.5f;
		temp.imageData[i].red = (float)((temp.imageData[i].red * images[8].imageData[i].red) / 255.0) + 0.5f;
	}
	for (unsigned int i = 0; i < part3.imageData.size(); i++)
	{
		b = 1 - (1 - (float)part3.imageData[i].blue / 255.0) * (1 - (float)temp.imageData[i].blue / 255.0);
		g = 1 - (1 - (float)part3.imageData[i].green / 255.0) * (1 - (float)temp.imageData[i].green / 255.0);
		r = 1 - (1 - (float)part3.imageData[i].red / 255.0) * (1 - (float)temp.imageData[i].red / 255.0);
		part3.imageData[i].blue = (b * 255) + 0.5f;
		part3.imageData[i].green = (g * 255) + 0.5f;
		part3.imageData[i].red = (r * 255) + 0.5f;
	}
	writeFile(part3, "output/part3.tga");
}

void task4(vector<Header>& images)
{
	Header part4 = images[6];
	int b, g, r;
	for (unsigned int i = 0; i < part4.imageData.size(); i++)
	{
		part4.imageData[i].blue = ((part4.imageData[i].blue * images[1].imageData[i].blue) / 255.0) + 0.5f;
		part4.imageData[i].green = ((part4.imageData[i].green * images[1].imageData[i].green) / 255.0) + 0.5f;
		part4.imageData[i].red = ((part4.imageData[i].red * images[1].imageData[i].red) / 255.0) + 0.5f;
	}
	for (unsigned int i = 0; i < part4.imageData.size(); i++)
	{
		b = ((int)part4.imageData[i].blue - (int)images[8].imageData[i].blue);
		if (b < 0) { b = 0; }
		else if (b > 255) { b = 255; }
		g = ((int)part4.imageData[i].green - (int)images[8].imageData[i].green);
		if (g < 0) { g = 0; }
		else if (g > 255) { g = 255; }
		r = ((int)part4.imageData[i].red - (int)images[8].imageData[i].red);
		if (r < 0) { r = 0; }
		else if (r > 255) { r = 255; }
		part4.imageData[i].blue = b;
		part4.imageData[i].green = g;
		part4.imageData[i].red = r;
	}
	writeFile(part4, "output/part4.tga");
}

void task5(vector<Header>& images)
{
	float b;
	float g;
	float r;
	Header part5 = images[5];
	for (unsigned int i = 0; i < part5.imageData.size(); i++)
	{
		if ((images[7].imageData[i].blue) / 255.0 <= 0.5) {
			b = 2.0 * (part5.imageData[i].blue / 255.0) * (images[7].imageData[i].blue / 255.0);
		}
		else {
			b = 1 - 2.0 * (1 - (float)part5.imageData[i].blue / 255.0) * (1 - (float)images[7].imageData[i].blue / 255.0);
		}
		if ((images[7].imageData[i].green) / 255.0 <= 0.5) {
			g = 2 * (part5.imageData[i].green / 255.0) * (images[7].imageData[i].green / 255.0);
		}
		else {
			g = 1 - 2.0 * (1 - (float)part5.imageData[i].green / 255.0) * (1 - (float)images[7].imageData[i].green / 255.0);
		}
		if ((images[7].imageData[i].red) / 255.0 <= 0.5) {
			r = 2.0 * (part5.imageData[i].red / 255.0) * (images[7].imageData[i].red / 255.0);
		}
		else {
			r = 1 - 2.0 * (1 - (float)part5.imageData[i].red / 255.0) * (1 - (float)images[7].imageData[i].red / 255.0);
		}
		part5.imageData[i].blue = (b * 255) + 0.5f;
		part5.imageData[i].green = (g * 255) + 0.5f;
		part5.imageData[i].red = (r * 255) + 0.5f;
	}
	writeFile(part5, "output/part5.tga");
}

void task6(vector<Header>& images)
{
	int g;
	Header part6 = images[0];
	for (unsigned int i = 0; i < part6.imageData.size(); i++)
	{
		g = part6.imageData[i].green + 200;
		if (g > 255) { g = 255; }
		part6.imageData[i].green = g;
	}
	writeFile(part6, "output/part6.tga");
}

void task7(vector<Header>& images)
{
	float r;
	float b;
	Header part7 = images[0];
	for (unsigned int i = 0; i < part7.imageData.size(); i++)
	{
		r = part7.imageData[i].red * 4.0;
		if (r > 255) { r = 255; }
		b = part7.imageData[i].blue * 0.0;
		part7.imageData[i].blue = b;
		part7.imageData[i].red = r;

	}
	writeFile(part7, "output/part7.tga");
}

void task8(vector<Header>& images)
{
	Header part8_b = images[0];
	Header part8_g = images[0];
	Header part8_r = images[0];
	for (unsigned int i = 0; i < part8_b.imageData.size(); i++)
	{
		part8_b.imageData[i].green = part8_b.imageData[i].blue;
		part8_b.imageData[i].red = part8_b.imageData[i].blue;

		part8_g.imageData[i].blue = part8_g.imageData[i].green;
		part8_g.imageData[i].red = part8_g.imageData[i].green;

		part8_r.imageData[i].green = part8_r.imageData[i].red;
		part8_r.imageData[i].blue = part8_r.imageData[i].red;
	}
	writeFile(part8_b, "output/part8_b.tga");
	writeFile(part8_g, "output/part8_g.tga");
	writeFile(part8_r, "output/part8_r.tga");
}

void task9(vector<Header>& images)
{
	Header part9 = images[2];
	Header b = images[2];
	Header g = images[3];
	Header r = images[4];
	for (unsigned int i = 0; i < part9.imageData.size(); i++)
	{
		part9.imageData[i].blue = b.imageData[i].blue;
		part9.imageData[i].green = g.imageData[i].green;
		part9.imageData[i].red = r.imageData[i].red;
	}
	writeFile(part9, "output/part9.tga");
}

void task10(vector<Header>& images)
{
	Header part10 = images[10];
	unsigned int index = part10.imageData.size() - 1;
	for (unsigned int i = 0; i < part10.imageData.size(); i++)
	{
		part10.imageData[i].blue = images[10].imageData[index].blue;
		part10.imageData[i].green = images[10].imageData[index].green;
		part10.imageData[i].red = images[10].imageData[index].red;
		index--;
	}
	writeFile(part10, "output/part10.tga");
}

void extraCredit(vector<Header>& images)
{
	Header ec = images[0];
	Header car = images[0];
	Header circle = images[1];
	Header text = images[9];
	Header pattern = images[7];
	unsigned int carIndex = 0;
	unsigned int cicleIndex = 0;
	unsigned int textIndex = 0;
	unsigned int patternIndex = 0;
	vector<pixel> image;
	ec.height = 1024;
	ec.width = 1024;
	for (int i = 1023; i >= 0; i--) {
		for (int j = 0; j < 1024; j++) {
			pixel p;
			if ((j < 512) && (i >= 512)) {
				p = text.imageData[textIndex];
				textIndex++;
				image.push_back(p);
			}
			else if ((j >= 512) && (i >= 512)) {
				p = pattern.imageData[patternIndex];
				patternIndex++;
				image.push_back(p);
			}
			else if ((j < 512) && (i < 512)) {
				p = car.imageData[carIndex];
				carIndex++;
				image.push_back(p);
			}
			else {
				p = circle.imageData[cicleIndex];
				cicleIndex++;
				image.push_back(p);
			}
		}
	}
	ec.imageData = image;
	writeFile(ec, "output/extracredit.tga");
}

int main()
{
	vector<string> inputPath = { "input/car.tga", "input/circles.tga", "input/layer_blue.tga", 
		"input/layer_green.tga", "input/layer_red.tga", "input/layer1.tga", "input/layer2.tga", 
		"input/pattern1.tga", "input/pattern2.tga", "input/text.tga", "input/text2.tga" };
	vector<Header> images;
	readFiles(images, inputPath);

	//*****Task 1*****//
	task1(images);

	//*****Task 2*****//
	task2(images);

	//*****Task 3*****//
	task3(images);

	//*****Task 4*****//
	task4(images);

	//*****Task 5*****//
	task5(images);

	//*****Task 6*****//
	task6(images);

	//*****Task 7*****//
	task7(images);

	//*****Task 8*****//
	task8(images);

	//*****Task 9*****//
	task9(images);

	//*****Task 10*****//
	task10(images);

	//*****Extra Credit*****//
	extraCredit(images);

	test();
	return 0;
}
