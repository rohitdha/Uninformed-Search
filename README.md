##<u>UNINFORMED SEARCH PROJECT</u>
--------------------------


### Introduction:
-----------------

There is an old city that has an antique plumbing system. There are a lot of pipes in the city that are useless or rarely work. We want to find a route for water to traverse from one side of the city to the other side. There is a source of water in which water will start flowing through the system. And there are some destinations which whenever water reaches one of them; we consider the task of routing the water through the city to be done. So, formally speaking, there is one start node (source) and one or more end nodes (destinations) in the city.

One strange fact about this city is that some of the pipes which are old do not function in specific times. So, the route for water might be different in different times. You will be given the time periods when each pipe doesn’t work. But if water is already flowing in a pipe, it will continue flowing even if time reaches one of those periods. You just have to make sure that when you want to select the next pipe for the rest of your water route, it is in its working time! Keep in mind that water cannot stay in one point waiting for a pipe to start working. If you reach a point where there is no pipe open from there, simply this route isn’t a valid route and you have to disregard it.

You have to keep track of the time too. This is simple. We assume that it takes n units of time for water to flow through a pipe if the length of the pipe is n. For example if you have two pipes with length 3 and 4 in your route till now and you have started from time 2, current time will be 2 + 3 + 4 = 9.

Your task is to find a route based on the availability of the pipes in a given time using <b>Search Algorithms - Breadth First Search, Depth First Search, Uniform Cost Search</b>.You are given the start time that water will start flowing and then you have to report the time which water reaches the other side of the city.

### Input:
----------

Given a text input file. First line of this file represents the number of test cases. The next line will be the beginning of the 1st test case. Each test case ends with an empty line. Each test case consists of the following lines:

* <b>\<task\></b> algorithm that you are supposed to use for this case
* <b>\<source\></b> name of the source node
* <b>\<destinations\></b> names of the destination nodes
* <b>\<middle nodes\></b> names of the middle nodes
* <b>\<#pipes\></b> represents the number of pipes
* <b>\<graph\></b> represents start-end nodes, lengths and off-times of pipes
* <b>\<start-time\></b> the time when water will start flowing

### Task:
---------

This field indicates which algorithm you are going to use to solve the problem. The input is either <b>“BFS”, “DFS” or “UCS”</b> (without the double quotes)

### Source:
-----------

This is the name of the source of water.

### Destinations:
-----------------

This is a space separated line consisting of names of the destination (goal) nodes.

### Middle-nodes:
-----------------

This is a space separated line consisting of the middle nodes, i.e. nodes that are neither source nor destination. (It may be an empty line which means there are no middle nodes.)

### #Pipes:
-----------

This number represents the number of pipes in the system.
Graph:
This section contains <b>#pipes</b> number of lines. Each line in this section represents one pipe of the system. Format of each line is as following: (There is one space between each field)
\<start\> \<end\> \<length\> \<#off-periods\> \< period1 \> …. \<periodn\>

<b>Example: S E 10 3 10-12 15-16 25-29</b>

It means that this pipe starts from point S , ends in point E , has the length 10, and it has 3 off-periods. It is not working from time 10 to 12, 15 to 16 and 25 to 29. Period 10-12 means that if we are at time 10, 11 or 12 we cannot use this pipe as the next pipe. Some pipes may always work. In that case, the 4th field for these pipes will be 0. Please note that the pipes are unidirectional, i.e. for a pipe that has starting point A and ending point B, the water can flow from A to B only and not in the reverse direction.
The pipe length will be 1 for both BFS and DFS (i.e. pipe length is ignored by these algorithms and is always assumed to be 1). Also, ignore the off-periods for these algorithms, i.e. when using BFS-DFS; assume that all pipes work all the time.

### Start-time:
---------------

This is an integer denoting the time when water will start flowing from the source point.

### Output:
-----------

Create a file named <b>“waterFlow.cpp”</b> 
Run the file:

g++ waterFlow.cpp –o waterFlow.o

./waterFlow.o –i inputFile

### Clarifications:
-------------------

* For <b>BFS-DFS</b>, whenever you want to insert nodes to your frontier, insert them in alphabetical order and then remove them according to the algorithm. Also for <b>UCS</b>, upon choosing a node from the frontier, in case of ties, choose the one that comes first in alphabetical order.
* For <b>DFS</b>, you should not visit a node that has already been visited to avoid the infinite-loop issue.
* For <b>UCS</b>, you can pop a node from the frontier only if the pipe from current node to that particular node is active at that time.
* It’s not possible for a node to be both source and destination.
* There will be one source node and at least one destination node. There is no bound on maximum number of destination/middle nodes and pipes.
* Names of the nodes (source, destinations and middle nodes) are unique, case-sensitive and are all alphabetical strings. (Just uppercase letters)
* Pipe lengths are positive integers.
* A pipe can have multiple off-times. The <b>off-times</b> will be specified in <b>0-23 hour format</b>. So if the time goes to 24, revert it back to 0.
* First and second numbers in pipe off-periods are both positive integers and not equal. Also the second number is always greater than the first number.
* There may be some overlapping periods when the pipes don’t work too, i.e. a pipe can have off-periods like 2-4 and 3-7.
