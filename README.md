##<u>UNINFORMED SEARCH</u>
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

* \<task\> algorithm that you are supposed to use for this case
* \<source\> name of the source node
* \<destinations\> names of the destination nodes
* \<middle nodes\> names of the middle nodes
* \<#pipes\> represents the number of pipes
* \<graph\> represents start-end nodes, lengths and off-times of pipes
* \<start-time\> the time when water will start flowing

### Task:
---------

This field indicates which algorithm you are going to use to solve the problem. The input is either “BFS”, “DFS” or “UCS” (without the double quotes)
There are multiple definitions for these algorithms. In this homework we ask you to use the definition in subsection 3.4 of “Artificial Intelligence, A modern Approach, 3rd edition” (starting at page 81). The reference implementation used to create the problem solutions will use these algorithms. Hence beware that using different algorithms may result in incorrect solutions.

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
This section contains #pipes number of lines. Each line in this section represents one pipe of the system. Format of each line is as following: (There is one space between each field)
\<start\> \<end\> \<length\> \<#off-periods\> \< period1 \> …. \<periodn\>
<b>Example: S E 10 3 10-12 15-16 25-29</b>
