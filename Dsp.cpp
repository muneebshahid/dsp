/*
 * dsp.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: Muneeb
 */

#include "Dsp.h"

namespace dynamic_shortest_path {

	Dsp::Dsp(int num_connections, std::vector<float> first_edges)
	{
		this->num_connections = num_connections;
		this->graph.push_back(first_edges);
	}

	Dsp::Dsp(int num_connections, std::vector<std::vector<float> > graph)
	{
		this->num_connections = num_connections;
		this->graph = graph;
	}

	Dsp::~Dsp()
	{
	}

	int Dsp::get_start_index(int y)
	{
		return std::max(0, y - this->num_connections + 1);
	}

	std::vector<float> Dsp::get_parents(int y, std::vector<float>::iterator it)
	{
		int start_index = this->get_start_index(y);
		std::vector<float> parents(it + start_index, it + y + 1);
		return parents;
	}


	void Dsp::update_scores(std::vector<float> edges)
	{
		std::vector<float> nodes;
		for(std::vector<int>::size_type i = 0; i != edges.size(); i++)
		{
			std::vector<float> parents = this->get_parents(i, this->graph.back().begin());
			nodes.push_back(*std::max_element(parents.begin(), parents.end()) + edges[i]);
		}
		this->graph.push_back(nodes);
	}

	void Dsp::forward(std::vector<float> new_edges)
	{
		if (new_edges.size() != this->graph[0].size())
		{
			std::cout<<"Size of provided data in consistent with earlier data.";
		}
		else
		{
			this->update_scores(new_edges);
		}
	}

	Path Dsp::backward()
	{
		Path path;
		int max_index = get_max_index(this->graph.size() - 1);
		path.append(max_index);
		for(std::vector<std::vector<float> >::reverse_iterator row = this->graph.rbegin() + 1; row != this->graph.rend(); ++row)
		{
			std::vector<float> parents = this->get_parents(max_index, row->begin());
			for(std::vector<int>::size_type i = 0; i != parents.size(); i++)
			{
				std::cout<<parents[i]<<"\n";
			}
			std::cout<<"\nP SIZE: " <<parents.size()<< "\n";
			std::reverse(parents.begin(), parents.end());
			max_index -= this->get_max_index(parents);
			path.append(max_index);
		}
		return path;
	}

	int Dsp::get_max_index(int row_num)
	{
		return this->get_max_index(this->graph[row_num]);
	}

	int Dsp::get_max_index(std::vector<float> row)
	{
		int index = 0;
		float max = row[0];
		for(std::vector<float>::size_type i = 1; i != row.size(); i++)
		{
			if (row[i] > max)
			{
				index = i;
				max = row[i];
			}
		}
		return index;
	}

	std::vector<std::vector<float> > Dsp::get_graph()
	{
		return this->graph;
	}

	void Dsp::print()
	{
		std::vector<float>::iterator col;
		for(std::vector<std::vector<float> >::iterator row = this->graph.begin(); row != this->graph.end(); ++row)
		{
			for(std::vector<float>::iterator col = row->begin(); col != row->end(); ++col)
			{
				std::cout<<*col<<" ";
			}
			std::cout<<std::endl;
		}
	}
} /* namespace dynamic_shortest_path */
