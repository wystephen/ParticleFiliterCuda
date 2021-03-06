// test_aux_tools.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


namespace plt = matplotlibcpp;


int main()
{
	auto engien = std::default_random_engine();
	auto norm_distrbut = std::normal_distribution<>(0, 1);
	std::vector<double> tmp_array;
	std::vector<double> y;

	for(int i(0);i<100;i++)
	{
		tmp_array.push_back(norm_distrbut(engien));
		y.push_back(sin(tmp_array[i]));
	}
	plt::figure();
	plt::plot(tmp_array, y);
	plt::save("D:\\test.jpg");
	plt::show();

    return 0;
}

