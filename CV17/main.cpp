#include "stdafx.h"
#include "opencv2/highgui.hpp"
#include "ThreadMaster.h"

using namespace std;

int main(int argc, char *argv[])
{
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE);

	ThreadMaster master(600, 600,6, 0.f);
	while (!master.Stopped())
	{
		master.Update();
	}

	master.Join();
    return 0;
}
