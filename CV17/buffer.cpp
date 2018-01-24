#include "Buffer.h"
#include <fstream>
#include <iostream>

void Buffer::Clear()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			diffuse[(width*y) + x] = Color(0, 0, 0, 0);
			depth[(width*y) + x] = 1.0f;
		}
	}
}

void Buffer::ClearColor()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			diffuse[(width*y) + x] = Color(0, 0, 0, 0);
		}
	}

}

void Buffer::ClearDepth()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			depth[(width*y) + x] = 1.0f;
		}
	}
}

void Buffer::Init(int width, int height) {
	this->width = width;
	this->height = height;

	diffuse = new Color[width*height];
	depth = new float[width*height];
	Clear();
}

void Buffer::Write(int x, int y, Color diffuse, float depth) {
	this->diffuse[(width*y) + x] = diffuse;
	this->depth[(width*y) + x] = depth;
}

void Buffer::SaveToTga()
{
	unsigned char header[18] = { 0 };

	header[2] = 2;
	header[12] = width & 0xFF;
	header[13] = (width >> 8) & 0xFF;
	header[14] = height & 0xFF;
	header[15] = (height >> 8) & 0xFF;
	header[16] = 32;

	std::ofstream colorFile("render.tga", std::ios::binary); // open files
	std::ofstream depthFile("renderDepth.tga", std::ios::binary); // for writing

	if (!colorFile) return;

	colorFile.write((const char*)&header, 18); // write header
	depthFile.write((const char*)&header, 18); // to files

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Color diffuseColor = this->diffuse[(width*y) + x];         // color data extraction in 0xAARRGGBB format
			unsigned int dint = 255 - (255 * depth[(width*y) + x]);    // depth float to unsigned int cast
			unsigned int depth = dint + (dint << 8) + (dint << 16) + (255 << 24); // depth unsigned int to 0xAARRGGBB construction
			unsigned int argb = diffuseColor.ToUInt32();
			colorFile.write((const char*)&argb, sizeof(unsigned int)); // write color to file
			depthFile.write((const char*)&depth, sizeof(unsigned int)); // write depth to file
		}
	}
	colorFile.close();
	std::cout << "calculations time: " << calculationsTime << "ms\n";
}


#include "opencv2/highgui.hpp"
using namespace cv;
void Buffer::WriteToMat(Mat &m, bool timestamp)
{
	m = Mat::zeros(height, width, CV_8UC3);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Vec3b ref = m.at<Vec3b>(Point(x, (height-y-1)));

			Color diffuseColor = this->diffuse[(width*y) + x];    
			ref[2] =diffuseColor.i_R();
			ref[1] =diffuseColor.i_G();
			ref[0] =diffuseColor.i_B();
			m.at<Vec3b>(Point(x, (height - y-1))) = ref;
		}
	}

	std::stringstream ss;
	ss << "time: " << calculationsTime << " ms (" << (1000/calculationsTime) << "fps)";
	if (timestamp)
		putText(m, ss.str(), Point(10, 20), CV_FONT_HERSHEY_PLAIN, 0.7, Scalar(255,255,255,255), 1);

}
