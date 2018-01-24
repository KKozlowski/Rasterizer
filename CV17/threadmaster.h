#pragma once
#include "Float4.h"
#include "Mesh.h"
#include "Rasterizer.h"
#include <queue>
#include <thread>
#include <mutex>
#include <ctime>

struct render_data
{
	std::vector<Mesh> objects;
	std::vector<Light*> lights;
	cv::Mat m;
	bool picked = false;
	bool finished = false;
	time_t creationTime;
	
};

class ThreadMaster
{
public:
	ThreadMaster(int width, int height, int threads, float targetRenderTime = 0.f);
	bool Stopped();
	void Update();

	std::vector<render_data*> queue;
	std::mutex qMutex;
	int width, height;
	float targetRenderTime = 0;

	void Join();
private:
	bool shouldStop = false;
	std::vector<std::thread> threads;
	clock_t beginTime;
	time_t lastDisplayTime;
	int threadCount;

	render_data *generateNewRenderData();

	bool printToTga = false;

	Rasterizer *singleThreadRasterizer;

	int index = 0;

	std::vector<Float4> rs;

	void printStatsToMat(render_data *rd);
};
