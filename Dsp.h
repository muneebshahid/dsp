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
			Dsp(int num_connections, float hidden_threshold, float genuine_match_threshold, int mult_hyp_dist, std::vector<float> first_edges);
			virtual ~Dsp();
			void forward(std::vector<float> new_edges);
			Path backward();
			std::vector<std::vector<float> > get_graph();
			void print();
		private:
			void update_scores(std::vector<float> new_edges);
			std::vector<float> get_parents(int y, std::vector<float>::iterator it);
			std::vector<float> get_parent_indices(int y);
			std::vector<float> get_childern(int index);
			int get_start_index(int row_num);
			int get_max_index(int row_num);
			int get_max_index(std::vector<float> row);
			std::vector<std::vector<float> > graph;
			std::vector<bool> hidden_rows;
			bool is_hidden_row(std::vector<float> row);
			float hidden_threshold;
			int num_connections;
			int mult_hyp_dist;
			float genuine_match_threshold;
	};

} /* namespace dynamic_shortest_path */

#endif /* DSP_H_ */
