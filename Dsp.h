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
			Dsp(int num_hyp, int mult_hyp_dist, int num_connections, int width, int recalculation_threshold);
			virtual ~Dsp();
			void forward(std::vector<float> new_edges, int hyp, bool append_edges);
			Path backward();
			Path backward(int hyp);
			std::vector<std::vector<float> > get_graph();
			void print_nodes(int hyp);
			void print_edges(int hyp);
			std::vector<Path> get_paths();
			void update_graph(std::vector<float> new_edges);
			void update_graph(std::vector<std::vector<float> > graph);
			int partial;
			int full;
		private:
			std::vector<float> get_parents(int y, std::vector<float>::iterator it);
			std::vector<float> get_parent_indices(int y);
			std::vector<float> get_childern(int index);
			int get_start_index(int row_num);
			int get_max_index(int hyp, int row_num);
			int get_max_index(std::vector<float> row);
			std::vector<int> get_max_indices(int row_num, int num_indices);
			std::vector<int> get_max_indices(std::vector<float> row, int num_indices);
			std::vector<std::vector<std::vector<float> > > nodes;
			std::vector<std::vector<std::vector<float> > > edges;
			void forward_all(int hyp);
			void forward_all(int hyp, int end);
			void update_edges(std::vector<Path> discovered_paths, int hyp);
			std::vector<bool> hidden_rows;
			bool is_hidden_row(std::vector<float> row);
			bool index_far_enough(int index, std::vector<int> indices);
			void append_to_graph(std::vector<float> nodes, std::vector<float> edges, int hyp, bool append_edges);
			std::vector<float> modify_row(std::vector<float> row, int central_index);
			std::vector<Path> paths;
			const int num_hyp;
			const int mult_hyp_dist;
			const int num_connections;
			const int width;
			const int recalculation_threshold;
	};
} /* namespace dynamic_shortest_path */

#endif /* DSP_H_ */
