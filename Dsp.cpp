/*
 * dsp.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: Muneeb
 */

#include "Dsp.h"

namespace dynamic_shortest_path

{

	Dsp::Dsp(int num_hyp, int mult_hyp_dist, int num_connections, int width, int recalculation_threshold)
				: num_hyp (num_hyp),
				  mult_hyp_dist (mult_hyp_dist),
				  num_connections (num_connections),
				  width (width),
				  recalculation_threshold (recalculation_threshold)
	{
		this->partial = 0;
		this->full = 0;
		for (int hyp = 0; hyp < this->num_hyp; hyp++)
		{
			this->nodes.push_back(std::vector<std::vector<float> > ());
			this->edges.push_back(std::vector<std::vector<float> > ());
			this->paths.push_back(Path());
		}
	}

	Dsp::~Dsp()
	{
	}

//	bool Dsp::is_hidden_row(std::vector<float> edges)
//	{
//		return *std::max_element(edges.begin(), edges.end()) < this->hidden_threshold;
//	}

	int Dsp::get_start_index(int y)
	{
		int start_index = y - this->num_connections + 1;
		return std::max(0, start_index);
	}

	std::vector<float> Dsp::get_parents(int y, std::vector<float>::iterator it)
	{
		int start_index = this->get_start_index(y);
		std::vector<float> parents(it + start_index, it + y + 1);
		return parents;
	}

	std::vector<float> Dsp::modify_row(std::vector<float> row, int central_index)
	{
		int reverse_index = central_index - this->mult_hyp_dist;
		int forward_index = central_index + this->mult_hyp_dist;
		int last_index = this->width - 1;
		int start_index = std::max(0, reverse_index);
		int end_index = std::min(last_index, forward_index);
		while(start_index <= end_index)
		{
			row.at(start_index) = -1;
			start_index++;
		}
		return row;
	}

	void Dsp::update_graph(std::vector<float> edges)
	{
		if (edges.size() != this->width)
		{
			std::cout<<"Size of provided data in consistent with earlier data.";
		}
		else
		{
			std::vector<Path> curr_paths;
			for (int hyp = 0; hyp < this->num_hyp; hyp++)
			{
				// First path has yet to be calculated for the current run.
				if (hyp == 0)
				{
					this->forward(edges, hyp, true);
					curr_paths.push_back(this->backward(hyp));
				}
				else if ((this->paths.at(hyp - 1).size() > 1) &&
						(std::abs(curr_paths.at(hyp - 1).get_element(-2) - this->paths.at(hyp - 1).get_element(-1))) <= this->recalculation_threshold)
				{
					edges = this->modify_row(edges, curr_paths.at(hyp - 1).get_element(-1));
					this->forward(edges, hyp, true);
					curr_paths.push_back(this->backward(hyp));
					this->partial++;
				}
				else
				{
					this->full++;
					this->update_edges(curr_paths, hyp);
					this->nodes.at(hyp) = std::vector<std::vector<float> >();
					this->forward_all(hyp, -1, -1);
					curr_paths.push_back(this->backward(hyp));
				}
			}
			this->paths = curr_paths;
		}
	}

	void Dsp::append_to_graph(std::vector<float> nodes, std::vector<float> edges, int hyp, bool append_edges)
	{
		this->nodes.at(hyp).push_back(nodes);
		if (append_edges)
		{
			this->edges.at(hyp).push_back(edges);
		}
	}

	void Dsp::forward(std::vector<float> new_edges, int hyp, bool append_edges)
	{
		if (this->nodes.at(hyp).size() > 0)
		{
				std::vector<float> nodes;
				for(std::vector<int>::size_type i = 0; i != new_edges.size(); i++)
				{
					std::vector<float> parents = this->get_parents(i, this->nodes.at(hyp).back().begin());
					nodes.push_back(*std::max_element(parents.begin(), parents.end()) + new_edges[i]);
				}
				this->append_to_graph(nodes, new_edges, hyp, append_edges);
		}
		else
		{
				this->append_to_graph(new_edges, new_edges, hyp, append_edges);
		}
	}

	void Dsp::forward_all(int hyp, int start, int end)
	{
		for (int row_index = 0; row_index < this->edges.at(hyp).size(); row_index++)
		{
			this->forward(this->edges.at(hyp).at(row_index), hyp, false);
		}
	}

	void Dsp::update_edges(std::vector<Path> discovered_paths, int hyp)
	{
		this->edges.at(hyp) = this->edges.at(0);
		for (unsigned int path_index = 0; path_index < discovered_paths.size(); path_index++)
		{
			std::vector<int> curr_path = discovered_paths.at(path_index).get_path();
			for(unsigned int element = 0; element < curr_path.size(); element++)
			{
				this->edges.at(hyp).at(element) = this->modify_row(this->edges.at(hyp).at(element), curr_path.at(element));
			}
		}
	}

	Path Dsp::backward()
	{
		return this->backward(1);
	}

	Path Dsp::backward(int hyp)
	{
		Path path;
		int last_row_index = this->nodes.at(hyp).size() - 1;
		int max_index = this->get_max_index(hyp, last_row_index);
		float value = this->edges.at(hyp).at(last_row_index).at(max_index);
		path.append(max_index, value);
		for (int row = last_row_index - 1; row >= 0; row--)
		{
			int last_max_index = path.get_element(-1);
			std::vector<float> parents = this->get_parents(last_max_index, this->nodes.at(hyp).at(row).begin());
			std::reverse(parents.begin(), parents.end());
			max_index = last_max_index - this->get_max_index(parents);
			value = this->edges.at(hyp).at(row).at(max_index);
			path.append(max_index, value);
		}
		path.reverse();
		return path;
	}

	int Dsp::get_max_index(int hyp, int row_num)
	{
		return this->get_max_index(this->nodes.at(hyp).at(row_num));
	}

	int Dsp::get_max_index(std::vector<float> row)
	{
		int index = 0;
		float max = 0;
		for(std::vector<float>::size_type i = 0; i != row.size(); i++)
		{
			if (row[i] > max)
			{
				index = i;
				max = row[i];
			}
		}
		return index;
	}

	bool Dsp::index_far_enough(int index, std::vector<int> indices)
	{
		bool is_far_enough = true;
		for (unsigned int i = 0; i < indices.size(); i++)
		{
			is_far_enough &= (std::abs(index - indices[i]) > this->mult_hyp_dist);
		}
		return is_far_enough;
	}

	std::vector<int> Dsp::get_max_indices(int row_num, int num_indices)
	{
		return this->get_max_indices(this->nodes.at(0).at(row_num), num_indices);
	}

	std::vector<int> Dsp::get_max_indices(std::vector<float> row, int num_indices)
	{
		std::vector<int> indices;

		for (int index = 0; index < num_indices; index++)
		{
			int curr_index = -1;
			float max = 0;
			for(std::vector<float>::size_type i = 0; i != row.size(); i++)
			{
				if (row[i] > max && index_far_enough(i, indices))
				{
					curr_index = i;
					max = row[i];
				}
			}
			if (curr_index >= 0)
			{
				indices.push_back(curr_index);
			}
		}
		return indices;
	}

	std::vector<Path> Dsp::get_paths()
	{
		return this->paths;
	}

	std::vector<std::vector<float> > Dsp::get_graph()
	{
		return this->nodes.at(0);
	}

	void Dsp::print_edges(int hyp)
	{
		for(std::vector<std::vector<float> >::iterator row = this->edges.at(hyp).begin(); row != this->edges.at(hyp).end(); ++row)
		{
			for(std::vector<float>::iterator col = row->begin(); col != row->end(); ++col)
			{
				std::cout<<*col<<" ";
			}
			std::cout<<std::endl;
		}
	}

	void Dsp::print_nodes(int hyp)
	{
		for(std::vector<std::vector<float> >::iterator row = this->nodes.at(hyp).begin(); row != this->nodes.at(hyp).end(); ++row)
		{
			for(std::vector<float>::iterator col = row->begin(); col != row->end(); ++col)
			{
				std::cout<<*col<<" ";
			}
			std::cout<<std::endl;
		}
	}
} /* namespace dynamic_shortest_path */
