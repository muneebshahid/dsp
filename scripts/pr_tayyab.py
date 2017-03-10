# -*- coding: utf-8 -*-
"""
Created on Fri Jul  4 17:15:00 2014

@author: Tayyab Naseer

"""

import numpy as np
import os


def calc_PR(gt_data, hp_data, match_accuracy, is_bm):
    #print 'GT data', gt_data.shape
    #print 'Result Data', hp_data.shape
    assert np.shape(gt_data) == np.shape(hp_data)

    positives = np.sum(gt_data)
    t_pos = 0
    f_pos = 0
    f_neg = 0
    t_neg = 0

    for gt_match, hp_match in zip(gt_data, hp_data):

        gt_match = np.where(gt_match)[0]
        hp_match = np.where(hp_match)[0]
        
        l_gt = len(gt_match)
        l_hp = len(hp_match)

        diff = abs(l_gt - l_hp)

        if l_gt == 0 and l_hp == 0:
            t_neg += 1
            continue  
        elif l_gt > l_hp:
            f_neg += diff
        prev_hp_element=-18 
        for hp_element in hp_match:
            if (not (hp_element - prev_hp_element > 20)):
                prev_hp_element = hp_element
                continue
            prev_hp_element = hp_element
            match_found = False
            for gt_element in gt_match:            
                if abs(hp_element - gt_element) <= match_accuracy:					
                    match_found = True					
                    break
            if match_found:
                t_pos += 1
            else:
                if(hp_element!=-1):
                    f_pos += 1
    
    if (t_pos + f_pos !=0):
        print "t_pos: {0}, t_neg: {1}, f_pos: {2}, f_neg: {3}".format(t_pos, t_neg, f_pos, f_neg)
        print 'Precision %f'%(t_pos / float(t_pos + f_pos))  
        print 'Recall %f'%(t_pos / float(positives))
        rec = (t_pos / float(positives))
        prec=(t_pos / float(t_pos + f_pos)) 
    else:
        rec, prec= 0, 0
    return [rec, prec]

path_gt = 'groundtruth_matrix_seq1.txt' 
d_path = 'paths/mats/'
d_mats = os.listdir(d_path)
pr = np.zeros((len(d_mats), 2)) 
gt_data = np.loadtxt(path_gt)

for i, d_mat_file in enumerate(d_mats):
    print 'loading: ', d_mat_file
    d_mat = np.loadtxt(d_path + d_mat_file)
    pr[i, :] = (calc_PR(gt_data, d_mat, 5,0))

np.savetxt('pr_' + path_gt, pr, fmt='%0.6f')

    
   
   


