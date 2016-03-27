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

	void Path::append(int step, float edge_value)
	{
		this->path.push_back(step);
		this->edge_values.push_back(edge_value);
	}

	void Path::reverse()
	{
		std::reverse(this->path.begin(), this->path.end());
	}

	std::vector<int> Path::get_path()
	{
		return this->path;
	}

	std::vector<std::vector<int> > Path::get_path(int threshold)
	{
		std::vector<std::vector<int> > path;
		int row = 0;
		for(std::vector<int>::iterator col = this->path.begin(); col != this->path.end(); ++col, row++)
		{
			if (*col >= threshold)
			{
				path.back().push_back(row);
				path.back().push_back(*col);
			}
		}
		return path;
	}

	int Path::size()
	{
		return this->path.size();
	}

	int Path::get_element(int i)
	{
		if (i >= 0)
		{
			return this->path[i];
		}
		else
		{
			//i = -1 * i -1;
			//return *(this->path.rbegin() + i);
			return this->path[this->path.size() + i];
		}
	}

	void Path::print()
	{
		this->print(true);
	}

	void Path::write_path(std::string save_path)
	{
		std::ofstream f(save_path.c_str());
		for(unsigned int i = 0; i < path.size(); i++)
		{
			f << this->path.at(i) << '\n';
		}
	}

	void Path::write_path(std::string save_path, int threshold)
	{
		std::ofstream f(save_path.c_str());
		std::vector<std::vector<int> > path(this->get_path(threshold));
		for(unsigned int i = 0; i < path.size(); i++)
		{
			f << path.at(i).at(0) << ' ' << path.at(i).at(0) << '\n';
		}
	}

	void Path::print(bool print_hidden_rows)
	{

		for(std::vector<int>::iterator col = this->path.begin(); col != this->path.end(); ++col)
		{
			std::cout<<*col<<" ";
		}
	}

} /* namespace dynamic_shortest_path */
