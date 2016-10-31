/*
 * main.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: Muneeb
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Dsp.h"
#include "Path.h"
#include <cstdio>
#include <ctime>
#include <string>

using namespace std;
using namespace dynamic_shortest_path;

std::vector<std::vector<float> > read_graph()
{
	std::ifstream scores("datasets/newcollege/normalized_scores.txt");
	std::string line;
	std::vector<std::vector<float> > lines;
	while (std::getline(scores, line))
	{
		lines.push_back(std::vector<float>());
		std::stringstream split(line);

		float value;
		while (split >> value)
		{
			lines.back().push_back(value);
		}
	}
	return lines;
}

int main()
{
	std::vector<std::vector<float> > lines = read_graph();
	int num_hypothesis = 1;
	int hypothesis_distance = 50;
	int num_connections = 3;
	const unsigned int recalculation_threshold = 0;
	Dsp dsp(num_hypothesis, hypothesis_distance, num_connections, lines[0].size(), recalculation_threshold);
	std::clock_t start;
	double duration;
	std::cout<<"starting..."<<std::endl;
	std::cout.flush();
	start = std::clock();
	for(std::vector<int>::size_type i = 0; i != lines.size(); i++)
	{
		std::cout<<"Processing: " << i << " out of " << lines.size() << std::endl;
		dsp.update_graph(lines[i]);
	}
	std::vector<Path> paths = dsp.get_paths();
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout<<"duration: "<< duration <<std::endl;
	float threshold_min = 0.53;
	float threshold_max = 3.6;
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		stringstream ss;
		ss << i;
		string str = ss.str();
		float curr_threshold = threshold_min;
		while (curr_threshold < threshold_max)
		{
			stringstream tt;
			tt << curr_threshold;
			std::string save_path = str + "_" + tt.str() + ".txt";
			paths.at(i).write_path(save_path, curr_threshold);
			curr_threshold += .4;
		}
	}
	return 0;
}
