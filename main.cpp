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

using namespace std;
using namespace dynamic_shortest_path;

std::vector<std::vector<float> > read_graph()
{
	std::ifstream scores("src/normalized_scores.txt");
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
	Dsp dsp(2, 50, 3, lines[0].size());
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
//	dsp.print_edges(0);
//	std::cout<<"\n----------\n";
//	dsp.print_edges(1);
	std::cout<<"\n----------\n";
	paths.at(0).print(false);
	std::cout<<"\n----------\n";
	paths.at(1).print(false);
    std::cout<<"duration: "<< duration <<'\n';
    std::ofstream f("somefile.txt");
    for(int i = 0; i < paths.at(1).get_path().size(); i++)
    {
        f << paths.at(1).get_element(i) << '\n';
    }
	return 0;
}
