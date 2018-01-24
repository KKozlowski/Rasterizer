#include "ThreadMaster.h"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <ctime>

using namespace std;

void reenderConcurrent(ThreadMaster *t, int id)
{
	Rasterizer r(t->width, t->height);
	int index = 0;
	render_data *current = nullptr;
	while (!t->Stopped())
	{
		t->qMutex.lock();
		for (int i = index; i < t->queue.size(); ++i)
		{
			if (!t->queue[i]->picked)
			{
				current = t->queue[i];
				current->picked = true;
				index = i;
				break;
			}
		}
		t->qMutex.unlock();
		
		if (current != nullptr)
		{
			r.Render(current->objects, current->lights);
			r.buf.WriteToMat(current->m, false);
			current->finished = true;
		}
		current = nullptr;
	}
}

ThreadMaster::ThreadMaster(int width, int height, int threadCount, float targetRenderTime)
	:rs({
		{ 0, 0, 0, 0 },
		{ 0,45,0,0 },
		{ 0,45,0,0 },
		{ 0,45,0,0 },
		{ 0,45,0,0 },
		{ 0,45,0,0 },
		{ 0,45,0,0 }
	})
{
	this->width = width;
	this->height = height;
	this->threadCount = threadCount;
	this->targetRenderTime = targetRenderTime;

	beginTime = std::clock();

	if (threadCount <= 0)
	{
		singleThreadRasterizer = new Rasterizer(width, height);
		if (threadCount < 0)
			printToTga = true;
	} else if (threadCount > 0)
	{
		for (int i = 0; i< threadCount; ++i)
		{
			threads.push_back(thread(reenderConcurrent, this, i));
		}
	}
}

bool ThreadMaster::Stopped()
{
	return shouldStop;
}



void ThreadMaster::Update()
{
	srand(0);
	render_data *rd = nullptr;
	if (threadCount > 0)
	{
		if (queue.size() < index + threadCount*15)
		{
			rd = generateNewRenderData();
		}

		qMutex.lock();
		if (rd != nullptr)
			queue.push_back(rd);

		if (queue[index]->finished && (index <= ((std::clock() - beginTime) / targetRenderTime)))
		{
			auto front = queue[index];
			++index;
			qMutex.unlock();
			printStatsToMat(front);
			if (index == 100)
			{
				auto now = std::clock();
				std::cout << "100. time: " << now - beginTime << "ms, " << 100000.f / (now - beginTime) << " fps" << std::endl;
			}
			cv::imshow("result", front->m);
			lastDisplayTime = std::clock();
			for (Mesh &m : front->objects)
			{
				m.release();
			}
			front->m.release();
			delete front;
		}
		else
		{
			qMutex.unlock();
		}
	} else
	{
		rd = generateNewRenderData();
		singleThreadRasterizer->Render(rd->objects, rd->lights);
		singleThreadRasterizer->buf.WriteToMat(rd->m, false);

		printStatsToMat(rd);
		++index;
		if (index == 100)
		{
			auto now = std::clock();
			std::cout << "100. time: " << now - beginTime << "ms, " << 100000.f / (now - beginTime) << " fps" << std::endl;
		}
		cv::imshow("result", rd->m);
		lastDisplayTime = std::clock();
		if (printToTga)
			singleThreadRasterizer->buf.SaveToTga();
		rd->m.release();
		for (Mesh &m : rd->objects)
		{
			m.release();
		}
	}
	
	auto key = cvWaitKey(1);
	if (key == 27)
		shouldStop = true;
}

void ThreadMaster::Join()
{
	for(thread &t : threads)
	{
		t.join();
	}
}

render_data* ThreadMaster::generateNewRenderData()
{
	render_data *rd = new render_data();
	rs[0] += Float4(0, 1, 0, 0);

	rd->objects.push_back(Mesh::Cube());
	rd->objects[0].Tv = { 0,0,2.f };
	rd->objects[0].Rv = rs[0];
	rd->objects[0].Sv = { 1,2,1 };

	for (int i = 0; i<3; ++i)
	{
		rd->objects.push_back(Mesh::Cube());
		rd->objects[i + 1].Tv = { -2.f,1.5f - i*1.5f,3.f };
		rd->objects[i + 1].Sv = { 0.5f,0.5f,0.5f };
	}
	for (int i = 0; i<3; ++i)
	{
		rd->objects.push_back(Mesh::Cube());
		rd->objects[4 + i].Tv = { 2.f,1.5f - i*1.5f,3.f };
		rd->objects[4 + i].Sv = { 0.5f,0.5f,0.5f };
	}

	for (int i = 1; i<7; ++i)
	{
		rs[i] += {Rasterizer::RandomFloat(0.3f, 0.9f), Rasterizer::RandomFloat(0.3f, 0.9f), Rasterizer::RandomFloat(0.3f, 0.9f)};
		rd->objects[i].Rv = rs[i];
	}

	Light* l1 = new Light(Float4(-7, 0.0, 0.0, 1), LightType::Point);
	l1->ambient = Color(0,0,0,0);
	l1->specular = Color(1, 0.2f, 0.2f, 0.2f);
	l1->diffuse = Color(1, 1, 0, 0); 
	l1->attenuation = 0.1f;
	Light* l2 = new Light(Float4(0.4f, -0.0f, -0.8f, 1), LightType::Spotlight, Float4(0, 0, 1));
	l2->ambient = Color(1, 0.15f, 0.15f, 0.15f);
	l2->specular = Color(1, 1, 1, 1);
	l2->diffuse = Color(1, 0.8f, 0.8f, 0.8f);
	l2->attenuation = 0.0f;
	l2->cutoff = 90;
	l2->spotlightExponent = 10.f;

	rd->lights.push_back(l1);
	rd->lights.push_back(l2);
	rd->creationTime = std::clock();
	return rd;
}

void ThreadMaster::printStatsToMat(render_data* rd)
{
	std::stringstream ss, ss2;
	ss.precision(2);
	ss2.precision(3);
	ss << "calc time: " << std::clock() - rd->creationTime << " ms (" << (1000.f / (std::clock() - rd->creationTime)) << "fps)";
	putText(rd->m, ss.str(), cv::Point(10, 20), CV_FONT_HERSHEY_PLAIN, 0.7, cv::Scalar(255, 255, 255, 255), 1);
	ss2 << "[" << (((float)index * 1000) / (std::clock() - beginTime)) << "fps] display time: " << std::clock() - lastDisplayTime << " ms (" << (1000.f / (std::clock() - lastDisplayTime)) << "fps)";
	putText(rd->m, ss2.str(), cv::Point(10, 34), CV_FONT_HERSHEY_PLAIN, 0.7, cv::Scalar(255, 255, 255, 255), 1);
}
