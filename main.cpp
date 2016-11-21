/*
 * main.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: Muneeb
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Dsp.h"
#include "Path.h"
#include <cstdio>
#include <ctime>
#include <string>
#include <direct.h>
#include <windows.h>

using namespace std;
using namespace dynamic_shortest_path;

std::vector<std::vector<float> > read_graph()
{
//	std::ifstream scores("datasets/sequence3/normalized_scores.txt");
//	std::ifstream scores("datasets/sequence1/normalized_scores.txt");
//	std::ifstream scores("datasets/newcollege/normalized_scores.txt");
//	std::ifstream scores("datasets/vprice/normalized_scores.txt");
	std::ifstream scores("datasets/gardenspoint/normalized_scores.txt");

	std::string line;
	std::vector<std::vector<float> > lines;
	while (std::getline(scores, line))
	{
		lines.push_back(std::vector<float>());
		std::stringstream split(line);

		float value;
		while (split >> value)
		{
			lines.back().push_back(value);
		}
	}
	return lines;
}

int main()
{
	std::vector<std::vector<float> > lines = read_graph();

	int hypothesis_distance;
	int num_hypothesis;
	float threshold_min;
	float threshold_max;

	int num_hypothesis_new_college = 10;
	int hypothesis_distance_new_college = 50;
	float threshold_min_new_college = 0.1;
	float threshold_max_new_college = 3.5;

	int num_hypothesis_seq_1 = 1;
	int hypothesis_distance_seq_1 = 10;
	float threshold_min_seq_1 = 0.6;
	float threshold_max_seq_1 = 1.2;

	int num_hypothesis_seq_3 = 2;
	int hypothesis_distance_seq_3 = 100;
	float threshold_min_seq_3 = 0.1;
	float threshold_max_seq_3 = 1.7;

	int num_hypothesis_vprice = 2;
	int hypothesis_distance_vprice = 50;
	float threshold_min_vprice = 0.4;
	float threshold_max_vprice = 2.5;

	int num_hypothesis_gp = 1;
	int hypothesis_distance_gp = 10;
	float threshold_min_gp = 0.67;
	float threshold_max_gp = 1.8;

	int use_settings = 4;
	if (use_settings  == 0)
	{
		num_hypothesis = num_hypothesis_new_college;
		hypothesis_distance = hypothesis_distance_new_college;
		threshold_min = threshold_min_new_college;
		threshold_max = threshold_max_new_college;
	}
	else if (use_settings == 1)
	{
		num_hypothesis = num_hypothesis_seq_1;
		hypothesis_distance = hypothesis_distance_seq_1;
		threshold_min = threshold_min_seq_1;
		threshold_max = threshold_max_seq_1;
	}
	else if (use_settings == 2)
	{
		num_hypothesis = num_hypothesis_seq_3;
		hypothesis_distance = hypothesis_distance_seq_3;
		threshold_min = threshold_min_seq_3;
		threshold_max = threshold_max_seq_3;
	}
	else if (use_settings == 3)
	{
		num_hypothesis = num_hypothesis_vprice;
		hypothesis_distance = hypothesis_distance_vprice;
		threshold_min = threshold_min_vprice;
		threshold_max = threshold_max_vprice;
	}
	else
	{
		num_hypothesis = num_hypothesis_gp;
		hypothesis_distance = hypothesis_distance_gp;
		threshold_min = threshold_min_gp;
		threshold_max = threshold_max_gp;
	}

//	hypothesis_distance = 100;
//	num_hypothesis = 2;
//	threshold_min = .1;
//	threshold_max = 1.7;

	std::cout<<"hyp dist: " << hypothesis_distance;
	std::cout<<"\nnum hyp: " << num_hypothesis;
	std::cout<<"\nthrehsold min: "<< threshold_min;
	std::cout<<"\nthrehsold max: "<< threshold_max;
	int num_connections = 3;
	const unsigned int recalculation_threshold = 0;
	Dsp dsp(num_hypothesis, hypothesis_distance, num_connections, lines[0].size(), recalculation_threshold);
	std::clock_t start;
	double duration;
	std::cout<<"\nstarting..."<<std::endl;
	std::cout.flush();
	start = std::clock();
	for(std::vector<int>::size_type i = 0; i != lines.size(); i++)
	{
		std::cout<<"Processing: " << i << " out of " << lines.size() << std::endl;
		dsp.update_graph(lines[i]);
	}
	std::vector<Path> paths = dsp.get_paths();
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout<<"duration: "<< duration <<std::endl;

	//	thresholds new college



	CreateDirectory( "PATHS", NULL );
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		stringstream ss;
		ss << i;
		string str = ss.str();
		string root_folder = "PATHS\\" + str;
		CreateDirectory( &(root_folder)[0], NULL );
		float curr_threshold = threshold_min;
		while (curr_threshold < threshold_max)
		{
			stringstream tt;
			tt << curr_threshold;
			std::string threshold_string;
			threshold_string = tt.str();

			if (threshold_string.length() == 1)
			{
				threshold_string += ".0";
			}
			std::cout<<threshold_string<<std::endl;
			std::string save_path = root_folder + "\\" + str + "_" + threshold_string + ".txt";
			paths.at(i).write_path(save_path, curr_threshold);
			curr_threshold += .1;
		}
	}
	return 0;
}
