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
//	std::ifstream scores("datasets/15seq2/normalized_scores_cell64.txt");
//	std::ifstream scores("datasets/15seq2/hog64scores_normalized.txt");
//	std::ifstream scores("datasets/15seq2/hog32scores_normalized.txt");
	std::ifstream scores("datasets/15seq2/normalized_scores.txt");
//	std::ifstream scores("datasets/seq1/normalized_scores.txt");
//	std::ifstream scores("datasets/seq1/normalized_scores_old.txt");
//	std::ifstream scores("datasets/seq1/hog32scores_normalized.txt");
//	std::ifstream scores("datasets/seq1/hog64scores_normalized.txt");
//	std::ifstream scores("datasets/seq3/normalized_scores_hog32.txt");

//	std::ifstream scores("datasets/newcollege/normalized_scores.txt");
//	std::ifstream scores("datasets/vprice/normalized_scores.txt");
//	std::ifstream scores("datasets/gardenspoint/normalized_scores.txt");
//	std::ifstream scores("src/scores.txt");

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

void threshold_matrix(std::vector<std::vector<float> > &mat, float threshold)
{
	int rows = mat.size();
	int cols = mat[0].size();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (mat[i][j] < threshold)
			{
				mat[i][j] = threshold;
			}
		}
	}
}


void print_matrix(std::vector<std::vector<float> > &mat)
{
	int rows = mat.size();
	int cols = mat[0].size();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout<<mat[i][j]<<" ";
		}
		std::cout<<"\n";
	}
}

int main()
{
	std::vector<std::vector<float> > lines = read_graph();

	float min = 100.0;
	float max = 0.0;

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		float curr_max = *std::max_element(lines[i].begin(), lines[i].end());
		float curr_min = *std::min_element(lines[i].begin(), lines[i].end());
		if (curr_max > max)
		{
			max = curr_max;
		}
		if (curr_min < min)
		{
			min = curr_min;
		}
	}


	int hypothesis_distance;
	int num_hypothesis;
	float threshold_min = min;
	float threshold_max = max;

	int num_hypothesis_new_college = 10;
	int hypothesis_distance_new_college = 50;

	int num_hypothesis_seq_1 = 1;
	int hypothesis_distance_seq_1 = 10;

	int num_hypothesis_seq_3 = 2;
	int hypothesis_distance_seq_3 = 100;

	int num_hypothesis_vprice = 2;
	int hypothesis_distance_vprice = 50;

	int num_hypothesis_gp = 1;
	int hypothesis_distance_gp = 10;

	int num_hypothesis_default = 1;
	int hypothesis_distance_default = 3;

	int num_hypothesis_15seq12 = 1;
	int hypothesis_distance_15seq12 = 50;

	int num_connections = 4;
	int use_settings = 5;
	bool enable_side_connection = true;

	if (use_settings  == 0)
	{
		num_hypothesis = num_hypothesis_new_college;
		hypothesis_distance = hypothesis_distance_new_college;
	}
	else if (use_settings == 1)
	{
		num_hypothesis = num_hypothesis_seq_1;
		hypothesis_distance = hypothesis_distance_seq_1;
	}
	else if (use_settings == 2)
	{
		num_hypothesis = num_hypothesis_seq_3;
		hypothesis_distance = hypothesis_distance_seq_3;
	}
	else if (use_settings == 3)
	{
		num_hypothesis = num_hypothesis_vprice;
		hypothesis_distance = hypothesis_distance_vprice;
	}
	else if (use_settings == 4)
	{
		num_hypothesis = num_hypothesis_gp;
		hypothesis_distance = hypothesis_distance_gp;
	}
	else if (use_settings == 5)
	{
		num_hypothesis = num_hypothesis_15seq12;
		hypothesis_distance = hypothesis_distance_15seq12;
	}
	else
	{
		num_hypothesis = num_hypothesis_default;
		hypothesis_distance = hypothesis_distance_default;
	}


	std::cout<<"hyp dist: " << hypothesis_distance;
	std::cout<<"\nnum hyp: " << num_hypothesis;
	std::cout<<"\nthrehsold min: "<< threshold_min;
	std::cout<<"\nthrehsold max: "<< threshold_max;

	const unsigned int recalculation_threshold = 0;

	CreateDirectory( "PATHS", NULL );

	for (int i = 0; i < num_hypothesis; i++)
	{
		stringstream ss;
		ss << i;
		string str = ss.str();
		string root_folder = "PATHS\\" + str;
		CreateDirectory( &(root_folder)[0], NULL );
	}

	float curr_threshold = threshold_min;
	while (curr_threshold <= threshold_max)
	{
		Dsp dsp(num_hypothesis, hypothesis_distance, num_connections, lines[0].size(), recalculation_threshold, enable_side_connection);

		stringstream tt;
		tt << curr_threshold;
		std::string threshold_string;
		threshold_string = tt.str();
		if (threshold_string.length() == 1)
		{
			threshold_string += ".0";
		}

		std::clock_t start;
		double duration;
		std::cout<<"\nstarting threshold: "<< threshold_string<<std::endl;
		std::cout.flush();
		start = std::clock();
//		for(std::vector<int>::size_type i = 0; i != lines.size(); i++)
//		{
//			std::cout<<"Processing: " << i << " out of " << lines.size() << std::endl;
//			dsp.update_graph(lines[i]);
//			dsp.print_nodes(0);
//		}

		std::cout<<"Processing: ";
		dsp.update_graph(lines);
		std::vector<Path> paths = dsp.get_paths();
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		std::cout<<"\nDuration: "<< duration <<std::endl;


		for (unsigned int i = 0; i < paths.size(); i++)
		{

			stringstream ss;
			ss << i;
			string str = ss.str();
			string root_folder = "PATHS\\" + str;
			std::string save_path = root_folder + "\\" + str + "_" + threshold_string + ".txt";
			paths.at(i).write_path(save_path, curr_threshold);


//			stringstream ss;
//			ss << i;
//			string str = ss.str();
//			string root_folder = "PATHS\\" + str;
//			CreateDirectory( &(root_folder)[0], NULL );
//			float curr_threshold = threshold_min;
//			while (curr_threshold <= threshold_max)
//			{
//				stringstream tt;
//				tt << curr_threshold;
//				std::string threshold_string;
//				threshold_string = tt.str();
//
//				if (threshold_string.length() == 1)
//				{
//					threshold_string += ".0";
//				}
//				std::cout<<threshold_string<<std::endl;
//				std::string save_path = root_folder + "\\" + str + "_" + threshold_string + ".txt";
//				paths.at(i).write_path(save_path, curr_threshold);
//				curr_threshold += .01;
//			}
		}
//		break;
		curr_threshold += .02;
	}
	return 0;
}
