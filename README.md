# dsp

Uses dynamic programming to handle changing graph (scoring matrix) and maintains multiple path hypothesis.
------------------------------------------------------------------------------------------------------------------------------------
- Dsp(int num_hyp, int mult_hyp_dist, int num_connections, int width, int recalculation_threshold); creates a dsp instance where:
- num_hyp = number of hypothesis to maintain
- mult_hyp_dist = distance between two hypothesis.
- num_connections = number of connections to next row.
- width = number of db images in each call. (must stay same)
- recalculation_threshold = threshold set for recalculating paths from scratch, only happens for secondary or tertiary paths, not for the primary one. Increasing the threshold  will reduce number of recalculations i.e it gets faster, but the result might not be accurate if the ground truths for multiple hyothesis are too close, setting it to zero is the safest way to go.
------------------------------------------------------------------------------------------------------------------------------------

- Call update_graph() to update the graph with a new row of calculations
------------------------------------------------------------------------------------------------------------------------------------
- call get_paths to get the paths for each hypothesis.
- call path.get_path to get whole path or path.get_path(int threshold) to only get rows above the threshold.
- call path.write_path(string file_path) to write whole path or path.write_path(string file_path) to only get rows above the threshold.
-------------------------------------------------------------------------------------------------------------------------------------
In order to match its performance, match it against running dijkstra from scratch each times a new calculation is recived for each hypothesis. The current implementation avoids recalculation as much as possible, but still does so when necessary. 
