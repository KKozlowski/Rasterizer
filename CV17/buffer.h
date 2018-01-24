#pragma once

#include "Color.h"
#include "opencv2/imgproc.hpp"

struct Buffer
{
	int width, height;

	Color* diffuse;
	float* depth;

	float calculationsTime = 0;

	void Clear();
	void ClearColor();
	void ClearDepth();

	void Init(int width, int height);

	void Write(int x, int y, Color diffuse, float depth);

	void SaveToTga();

	void WriteToMat(cv::Mat &m, bool timestamp = true);
};