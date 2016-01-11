/*
 * Path.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: Muneeb
 */

#include "Path.h"

namespace dynamic_shortest_path
{

	Path::Path()
	{
		// TODO Auto-generated constructor stub

	}

	Path::~Path()
	{
		// TODO Auto-generated destructor stub
	}

	void Path::append(float step)
	{
		this->path.push_back(step);
	}

	std::vector<float> Path::get_path()
	{
		std::vector<float> path_rev = this->path;
		std::reverse(path_rev.begin(), path_rev.end());
		return path_rev;
	}

	void Path::print()
	{
		std::vector<float> path = this->get_path();
		for (std::vector<float>::iterator it = path.begin(); it != path.end(); ++it)
		{
			std::cout<<*it<<" \n";
		}
	}

} /* namespace dynamic_shortest_path */
