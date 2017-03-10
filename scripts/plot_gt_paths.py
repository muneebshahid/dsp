from matplotlib import pyplot as plt
import numpy as np
import os
dataset = '15seq2'
gt = 'datasets/gt/'+ dataset +'/groundtruth_matrix.txt'
rec = 'datasets/' + dataset + '/normalized_scores.txt'
tra = 'paths/mats/'
p_map = 'hot'

gt_f = np.loadtxt(gt)
plt.imshow(gt_f, cmap=p_map)
# plt.savefig('gt.png', bbox_inches='tight')
plt.figure()
rec_f = np.loadtxt(rec)
plt.imshow(rec_f, cmap=p_map)
# plt.savefig('scores.png', bbox_inches='tight')

tra_files = []
for i, file in enumerate(os.listdir(tra)):
	plt.figure()
	curr_file = np.loadtxt(tra + file)
	plt.imshow(curr_file, cmap='hot')
	# plt.savefig(str(i) + '.png', bbox_inches='tight')


plt.show()

