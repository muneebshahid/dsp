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
	std::ifstream scores("src/scores.txt");
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
	int num_hypothesis = 2;
	int hypothesis_distance = 2;
	int num_connections = 3;
	Dsp dsp(num_hypothesis, hypothesis_distance, num_connections, lines[0].size());
	std::clock_t start;
	double duration;
	std::cout<<"starting..."<<std::endl;
	std::cout.flush();
	start = std::clock();
	for(std::vector<int>::size_type i = 0; i != lines.size(); i++)
	{
		dsp.update_graph(lines[i]);
	}
	std::vector<Path> paths = dsp.get_paths();
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout<<"duration: "<< duration <<std::endl;
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		stringstream ss;
		ss << i;
		string str = ss.str();
		std::string save_path = str + ".txt";
		paths.at(i).write_path(save_path, .5);
	}
	return 0;
}
