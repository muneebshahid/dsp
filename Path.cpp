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
	}

	Path::~Path()
	{
	}

	void Path::append(int step)
	{
		this->path.back().push_back(step);
	}

	void Path::append(std::vector<int> step)
	{
		this->path.push_back(step);
	}

	std::vector<std::vector<int> > Path::get_path()
	{
		std::vector<std::vector<int> > path_rev = this->path;
		std::reverse(path_rev.begin(), path_rev.end());
		return path_rev;
	}

	std::vector<int> Path::get_row(int i)
	{
		if (i > 0)
		{
			return this->path[i];
		}
		else
		{
			return this->path.back();
		}

	}

	void Path::print()
	{
		for(std::vector<std::vector<int> >::reverse_iterator row = this->path.rbegin(); row != this->path.rend(); ++row)
		{
			for(std::vector<int>::iterator col = row->begin(); col != row->end(); ++col)
			{
				std::cout<<*col<<" ";
			}
			std::cout<<std::endl;
		}
	}

} /* namespace dynamic_shortest_path */
