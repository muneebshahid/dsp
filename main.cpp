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
	Dsp path(3, .05, 4, lines[0].size());
	for(std::vector<int>::size_type i = 0; i != lines.size(); i++)
	{
		path.forward(lines[i]);
		path.print();
		std::cout<<"\n----------\n";
	}
	Path shortest_path = path.backward();
	shortest_path.print();
	return 0;
}


//.8 .9 .9 .6 .5 .5 .3 .2 .1
//.1 .3 .7 .8 .9 .7 .7 .5 .3
//.5 .5 .6 .7 .9 .8 .7 .5 .5
//.3 .4 .5 .5 .7 .9 .7 .1 .3
//.5 .4 .5 .6 .8 .7 .9 .1 .2
//.3 .4 .6 .7 .8 .9 .6 .6 .5
//.3 .6 .7 .5 .7 .8 .8 .7 .3
//.1 .3 .2 .2 .4 .7 .9 .8 .7
//.9 .8 .7 .2 .3 .2 .1 .1 .1
//.9 .8 .7 .7 .2 .2 .2 .1 .1
//.9 .9 .7 .6 .3 .2 .2 .2 .1
