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

	void Path::append(int row, int col, float edge_value)
	{
		this->path.push_back(std::vector<int> ());
		this->path.back().push_back(row);
		this->path.back().push_back(col);
		this->edge_values.push_back(edge_value);
	}

	void Path::reverse()
	{
		std::reverse(this->path.begin(), this->path.end());
		std::reverse(this->edge_values.begin(), this->edge_values.end());
	}

	std::vector<std::vector<int> > Path::get_path()
	{
		return this->path;
	}

	std::vector<std::vector<int> > Path::get_path(float threshold)
	{
		std::vector<std::vector<int> > path;
		for(unsigned int element = 0; element < this->path.size(); element++)
		{
			int row = this->path.at(element).at(0);
			int col = this->path.at(element).at(1);
			float value = this->edge_values.at(element);
			if (threshold == NULL || value >= threshold)
			{
				path.push_back(std::vector<int>());
				path.back().push_back(row);
				path.back().push_back(col);
			}
		}
		return path;
	}

	int Path::size()
	{
		return this->path.size();
	}

	std::vector<int> Path::get_element(int i)
	{
		if (i >= 0)
		{
			return this->path.at(i);
		}
		else
		{
			return this->path.at(this->path.size() + i);
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
			f << this->path.at(i).at(1) << '\n';
		}
	}

	void Path::write_path(std::string save_path, float threshold)
	{
		std::ofstream f(save_path.c_str());
		std::vector<std::vector<int> > path = this->get_path(threshold);
		for(unsigned int i = 0; i < path.size(); i++)
		{
			f << path.at(i).at(0) << ' ' << path.at(i).at(1) << '\n';
		}
	}

	void Path::print(bool print_hidden_rows)
	{

		for(std::vector<std::vector<int> >::iterator ele = this->path.begin(); ele != this->path.end(); ++ele)
		{
			std::cout<<(*ele).at(0)<<" "<<(*ele).at(1)<<"\n";
		}
	}

} /* namespace dynamic_shortest_path */
