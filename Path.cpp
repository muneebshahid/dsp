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

	void Path::append(std::vector<int> step)
	{
		this->append(step, false);
	}

	void Path::append(std::vector<int> step, bool is_hidden)
	{
		this->path.push_back(step);
		this->hidden_rows.push_back(is_hidden);
	}

	std::vector<std::vector<int> > Path::get_path()
	{
		std::vector<std::vector<int> > path_rev = this->path;
		std::reverse(path_rev.begin(), path_rev.end());
		return path_rev;
	}

	std::vector<bool> Path::get_hidden_rows()
	{
		std::vector<bool> hidden_row_rev = this->hidden_rows;
		std::reverse(hidden_row_rev.begin(), hidden_row_rev.end());
		return hidden_row_rev;
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
		this->print(true);
	}

	void Path::print(bool print_hidden_rows)
	{
		for(int row = this->path.size() - 1; row >= 0; row--)
		{
			if (print_hidden_rows || !this->hidden_rows[row])
			{
				for(std::vector<int>::iterator col = this->path[row].begin(); col != this->path[row].end(); ++col)
				{
					std::cout<<*col<<" ";
				}

			}
			else
			{
				std::cout<<"-1 ";
			}
			std::cout<<std::endl;
		}
	}

} /* namespace dynamic_shortest_path */
