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
	std::vector<float> get_path();
	void print();
	void append(float step);
	float get_cost();
private:
	std::vector<float> path;
};

} /* namespace dynamic_shortest_path */

#endif /* PATH_H_ */
