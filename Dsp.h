/*
 * dsp.h
 *
 *  Created on: Jan 10, 2016
 *      Author: Muneeb
 */

#ifndef DSP_H_
#define DSP_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include "Path.h"

namespace dynamic_shortest_path
{
	class Dsp
	{
		public:
			Dsp(int num_connections, float hidden_threshold, int mult_hyp_dist, unsigned int width, unsigned int num_hyp);
			virtual ~Dsp();
			void forward(std::vector<float> new_edges);
			void forward(std::vector<float> new_edges, int hyp, int start, int end, bool update_edges);
			Path backward();
			Path backward(int path_num);
			Path backward(int path_num, int hyp);
			std::vector<std::vector<float> > get_graph();
			void print();
		private:
			void update_graph(std::vector<float> new_nodes, std::vector<float> new_edges, int hyp, bool update_edges);
			std::vector<float> get_parents(int y, std::vector<float>::iterator it);
			std::vector<float> get_parent_indices(int y);
			std::vector<float> get_childern(int index);
			int get_start_index(int row_num);
			int get_max_index(int row_num);
			int get_max_index(std::vector<float> row);
			std::vector<int> get_max_indices(int row_num, int num_indices);
			std::vector<int> get_max_indices(std::vector<float> row, int num_indices);
			std::vector<std::vector<std::vector<float> > > nodes;
			std::vector<std::vector<std::vector<float> > > edges;
			void forward_all(int hyp, int start, int end);
			std::vector<bool> hidden_rows;
			bool is_hidden_row(std::vector<float> row);
			bool index_far_enough(int index, std::vector<int> indices);
			const int num_connections;
			const float hidden_threshold;
			const int mult_hyp_dist;
			const unsigned int width;
	};
} /* namespace dynamic_shortest_path */

#endif /* DSP_H_ */
