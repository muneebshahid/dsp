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

#include "Dsp.h"
#include "Path.h"

using namespace std;
using namespace dynamic_shortest_path;

std::vector<std::vector<float> > read_graph()
{
	std::ifstream scores("C:\\Users\\Muneeb\\workspace\\dsp\\src\\scores.txt");
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
	Dsp path(3, .05, 3, lines[0].size());
	for(std::vector<int>::size_type i = 0; i != lines.size(); i++)
	{
		path.forward(lines[i]);
		path.print();
		std::cout<<"\n----------\n";
	}
	Path shortest_path = path.backward(2);
	shortest_path.print(false);
	return 0;
}
