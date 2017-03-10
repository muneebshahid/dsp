import numpy as np
import os
import sys

def remove_indices(indices, arr):
	return np.delete(arr, indices)

def calc_pr(g, d):
	d_mats = os.listdir(d)
	pr = np.zeros((len(d_mats), 2))	
	g_mat = np.loadtxt(g)
	total_positives = np.where(g_mat)[0].size

	# load each thresholded matrix and calculate pr
	for i, d_mat_file in enumerate(d_mats):
		tp = 0
		fp = 0
		fn = 0
		print 'loading: ', d_mat_file
		d_mat = np.loadtxt(d + d_mat_file)
		
		# look for matches in each row.
		for gt_row, d_row in zip(g_mat, d_mat):		    
		    gt_row_data = np.where(gt_row)[0]
		    d_row_data = np.where(d_row)[0]

		    # matched indices are marked in the loop and count as true positives.
		    # afterwards matched indices are removed and remaining are counted as false positives	  
		    d_marked_indices = []
		    # gt_marked_indices = []

		    for j, ele in enumerate(d_row_data):

		    	# get all the gt path indices which are close enough to score matrix element.	
		    	gt_match = np.where(abs(gt_row_data - ele) <= 5)[0]

		    	# matches found
		    	if gt_match.size > 0:		    		
		    		d_marked_indices.append(j)		    		
		    		# gt_marked_indices.extend(list(gt_match))		    		
		    		tp += 1

		    # remove marked indices.
		    d_row_data = remove_indices(d_marked_indices, d_row_data)		    
		    # gt_row_data = remove_indices(gt_marked_indices, gt_row_data)		    

		    # count false positives
		    for ele in d_row_data:
		    	fp += 1

		    # for ele in gt_row_data:
		    # 	fn += 1
		    # sys.exit(0)

		pr[i, 0] = (tp / float(tp + fp)) if tp != 0 else 0
		pr[i, 1] = (tp / float(total_positives))
	return pr[::-1]


path_gt = 'groundtruth_matrix_gardenspoint.txt'
path_d_mat = 'paths/mats/'
pr = calc_pr(path_gt, path_d_mat)
np.save('pr_' + path_gt.replace('.txt', ''), pr)
