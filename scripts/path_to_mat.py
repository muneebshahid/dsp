import numpy as np
import os

root_folder = 'paths'
save_root = root_folder + '/mats/'
path_num = 1
dim_x = 676
dim_y = 322

for threshold_file in os.listdir(root_folder + '/0'):
	path_mat = np.zeros((dim_x, dim_y))
	threshold_files = []
	write = False
	for path_folder in range(path_num):
		path_folder_str = str(path_folder)
		curr_threshold_file = threshold_file.replace('0_', path_folder_str + '_')
		file_name = root_folder + '/' + path_folder_str + '/' + curr_threshold_file
		print 'loading file: ', file_name
		curr_loaded_file = np.loadtxt(file_name)
		if len(curr_loaded_file) != 0:
			if len(curr_loaded_file.shape) == 1:
				print len(curr_loaded_file.shape)
				path_mat[curr_loaded_file[0]][curr_loaded_file[1]]
			else:
				for ele in curr_loaded_file:
					ind_x, ind_y = int(ele[0]), int(ele[1])
					path_mat[ind_x][ind_y] = 1
	np.savetxt(save_root + 'path_mat_' + threshold_file.replace('0_', ''), path_mat, fmt='%i')
