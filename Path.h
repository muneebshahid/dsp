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

namespace dynamic_shortest_path {

class Path {
public:
	Path();
	virtual ~Path();
	std::vector<int> get_path();
	int size();
	int get_length();
	void print();
	void print(bool print_hidden_rows);
	void append(int step);
	void append(int step, bool is_hidden);
	float get_cost();
	int get_element(int i);
	void reverse();
	std::vector<bool> get_hidden_rows();
private:
	std::vector<int> path;
	std::vector<bool> hidden_rows;
};

} /* namespace dynamic_shortest_path */

#endif /* PATH_H_ */
