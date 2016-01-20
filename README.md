# dsp

Uses dynamic programming to handle changing graph (scoring matrix) and maintains multiple path hypothesis.

- Dsp dsp(3, .05, 2, width); creates a dsp instance where:
-- 3 = number of connections to next row.
-- .05 threshold for hidden rows, if all incoming edges are below this threshold then that row is treated as a hidden row i.e no corresponding db images was found.
--  2 = number of images, after which a new hypothesis is searched.
-- width = number of edges in each call.

- Call forward to add a set of edges.
-- they will be added to the graph given their lenght matches "width".

- Call backward/backwar(int path_num) to find a specifice number of hypothesis/paths separated by "number of images".
-- backwards returns a "Path" variable.
-- call path.print() to print whole path or path.print(false) to not print hidden rows (-1 is printed instead)
-- use path.get_path() to get the path vector, use path.get_hidden_rows() to a bool vector indicating which row is hidden and which isn't.

- Call dsp.print() to see evolving graph.

a sample graph that I've been testing on:
.2  .5  .6  .7  .9  .5  .5  .3  .2  .1
.1  .2  .3  .7  .8  .9  .7  .7  .5  .3
.1  .4  .5  .6  .7  .9  .8  .7  .5  .5
.2  .5  .4  .5  .5  .7  .9  .7  .1  .3
.1  .3  .2  .5  .6  .8  .7  .9  .1  .2
.2  .4  .4  .6  .7  .8  .9  .6  .6  .5
.8  .9  .2  .3  .5  .7  .8  .8  .7  .3
.01 .01 .01 .01 .01 .01 .01 .01 .01 .01
.2  .4  .9  .8  .2  .4  .7  .9  .8  .7
.8  .9  .8  .5  .2  .3  .2  .1  .1  .9
.5  .6  .8  .9  .7  .2  .2  .2  .1  .9
.1  .1  .2  .5  .9  .3  .2  .2  .2  .9
