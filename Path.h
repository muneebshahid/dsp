/*
 * Path.h
 *
 *  Created on: Jan 11, 2016
 *      Author: Muneeb
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

namespace dynamic_shortest_path {

class Path {
public:
	Path();
	virtual ~Path();
	std::vector<int> get_path();
	std::vector<std::vector<int> > get_path(int threshold);
	int size();
	int get_length();
	void print();
	void print(bool print_hidden_rows);
	void append(int step, float edge_value);
	float get_cost();
	int get_element(int i);
	void reverse();
	void write_path(std::string save_path);
	void write_path(std::string save_path, int threshold);
private:
	std::vector<int> path;
	std::vector<float> edge_values;
};

} /* namespace dynamic_shortest_path */

#endif /* PATH_H_ */
