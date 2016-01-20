# dsp

Uses dynamic programming to handle changing graph (scoring matrix) and maintains multiple path hypothesis.
------------------------------------------------------------------------------------------------------------------------------------
- Dsp dsp(3, .05, 2, width); creates a dsp instance where:
- 3 = number of connections to next row.
- .05 threshold for hidden rows, if all incoming edges are below this threshold then that row is treated as a hidden row i.e no corresponding db images was found.
- 2 = number of images (mult_hyp_dist), after which a new hypothesis is searched.
- width = number of edges in each call.

------------------------------------------------------------------------------------------------------------------------------------

- Call forward to add a set of edges, they will be added to the graph given their lenght matches "width".

------------------------------------------------------------------------------------------------------------------------------------

- Call backward/backwar(int path_num) to find a specifice number of hypothesis/paths separated by "number of images".
- calling backward(2) is equivalent of calling dijkstra's shortest path twice, with first path and images with in mult_hyp_dist of the first path removed. i.e it returns two paths that are "far enough". However if the path with higher scores comes closer than mult_hyp_dist to other paths, then the path with lesser scores is discontinued.
- backwards returns a "Path" variable.
- call path.print() to print whole path or path.print(false) to not print hidden rows (-1 is printed instead)
- use path.get_path() to get the path vector, use path.get_hidden_rows() to a bool vector indicating which row is hidden and which isn't.

------------------------------------------------------------------------------------------------------------------------------------
- Call dsp.print() to see evolving graph.
