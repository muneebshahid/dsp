/*
 * dsp.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: Muneeb
 */

#include "Dsp.h"

namespace dynamic_shortest_path

{
	Dsp::Dsp(int num_connections, float hidden_threshold, int mult_hyp_dist, unsigned int width, unsigned int num_hyp)
				: num_connections (num_connections),
				  hidden_threshold (hidden_threshold),
				  mult_hyp_dist (mult_hyp_dist),
				  width (width)
	{
		for (unsigned int hyp = 0; hyp < num_hyp; hyp++)
		{
			this->nodes.push_back(std::vector<std::vector<float> > ());
			this->edges.push_back(std::vector<std::vector<float> > ());
		}
	}

	Dsp::~Dsp()
	{
	}

	bool Dsp::is_hidden_row(std::vector<float> edges)
	{
		return *std::max_element(edges.begin(), edges.end()) < this->hidden_threshold;
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


	void Dsp::update_graph(std::vector<float> nodes, std::vector<float> edges, int hyp, bool update_edges)
	{
		if (this->hidden_threshold > 0)
		{
			float max_element = *std::max_element(edges.begin(), edges.end());
			this->hidden_rows.push_back(max_element < this->hidden_threshold);
		}
		this->nodes.at(hyp).push_back(nodes);
		if (update_edges)
		{
			this->edges.at(hyp).push_back(edges);
		}
	}

	void Dsp::forward(std::vector<float> new_edges)
	{
		this->forward(new_edges, 0, -1, -1, true);
	}

	void Dsp::forward(std::vector<float> new_edges, int hyp, int start, int end, bool update_edges)
	{
		if (new_edges.size() != this->width)
		{
			std::cout<<"Size of provided data in consistent with earlier data.";
		}
		else if (this->nodes.at(hyp).size() > 0)
		{
				std::vector<float> nodes;
				for(std::vector<int>::size_type i = 0; i != new_edges.size(); i++)
				{
					std::vector<float> parents = this->get_parents(i, this->nodes.at(hyp).back().begin());
					nodes.push_back(*std::max_element(parents.begin(), parents.end()) + new_edges[i]);
				}
				this->update_graph(nodes, new_edges, hyp, update_edges);
		}
		else
		{
				this->update_graph(new_edges, new_edges, hyp, update_edges);
		}
	}

	void forward_all(int hyp, int start, int end)
	{
	}

	Path Dsp::backward()
	{
		return this->backward(1);
	}

	Path Dsp::backward(int path_num)
	{
		return this->backward(path_num, 0);
	}

	Path Dsp::backward(int path_num, int hyp)
	{
		Path path;
		int last_row_index = this->nodes.at(hyp).size() - 1;
		path.append(this->get_max_indices(last_row_index, path_num));
		for (int row = last_row_index - 1; row >= 0; row--)
		{
			std::vector<int> max_indices;
			std::vector<int> last_row = path.get_row(-1);
			for (std::vector<int>::iterator max_index = last_row.begin(); max_index != last_row.end(); ++max_index)
			{
				std::vector<float> parents = this->get_parents(*max_index, this->nodes.at(0).at(row).begin());
				std::reverse(parents.begin(), parents.end());
				*max_index -= this->get_max_index(parents);
				if (this->index_far_enough(*max_index, max_indices))
				{
					max_indices.push_back(*max_index);
				}
			}
			path.append(max_indices, this->hidden_rows[row]);
		}
		return path;
	}

	int Dsp::get_max_index(int row_num)
	{
		return this->get_max_index(this->nodes.at(0).at(row_num));
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

	std::vector<std::vector<float> > Dsp::get_graph()
	{
		return this->nodes.at(0);
	}

	void Dsp::print()
	{
		for(std::vector<std::vector<float> >::iterator row = this->nodes.at(0).begin(); row != this->nodes.at(0).end(); ++row)
		{
			for(std::vector<float>::iterator col = row->begin(); col != row->end(); ++col)
			{
				std::cout<<*col<<" ";
			}
			std::cout<<std::endl;
		}
	}
} /* namespace dynamic_shortest_path */
