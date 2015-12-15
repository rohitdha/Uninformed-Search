/*
	Author: Rohit Dhawan
	Project: Uninformed Search
	Domain: Artificial Intelligence
	Algorithm: Breadth First Search, Depth First Search, Uniform Cost Search
	Complexity: O(M+N) M: Number of Edges, N:Number Of Nodes
	
	Sample Input:
		1							< Number of Test Cases >
		DFS							< Algorithm to run >
		A							< Start Node >
		B C D						< Destination Node >
		E B F G H I					< Middle Nodes >
		6							< Number of pipes >
		A B 12 0					< Adjoining Nodes, Pipe length, off time, offtime slots(one or many) >
		A C 3 3 2-4 1-5 9-10
		A D 1 0
		A E 3 3 2-4 1-5 9-10
		E H 2 1 1-2
		I C 6 1 10-14
		3							< Start Time from Start Node>
		
	More Details in README.md
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include "waterFlow.h"

using namespace std; 	 	 

// Default constructor
uninformedSearch::uninformedSearch() {
}

// Reading the data from input vector and storing into class variables
void uninformedSearch::setData(vector<string> & line) {
	vector<string>::iterator read_it;
	read_it = line.begin();
	this->task = *read_it;
	read_it++;
	this->source = *read_it;
	read_it++;
	this->destination = *read_it;
	read_it++;
	this->middlenodes = *read_it;
	read_it++;
	this->pipes = atoi((*read_it).c_str());
	read_it++;
	for(int i=0; i<this->pipes; i++,read_it++) {
		this->graphOfPipes.push_back(*read_it);
	}
	this->individualPipes = new vector<string>[this->pipes];
	
	vector<string> graph_of_pipes = this->getGraphs();
	vector<string>::iterator graph_of_pipes_iterator;
	int i;
	string graph_per_line[this->pipes];
	for(graph_of_pipes_iterator = graph_of_pipes.begin(), i=0; nn != graph_of_pipes.end(); ++graph_of_pipes_iterator,i++) {
			graph_per_line[i] = *graph_of_pipes_iterator;
			int j=0;
			string temp = "";
			while(graph_per_line[i][j]) { 
				if(isspace(graph_per_line[i][j])) {
					this->individualPipes[i].push_back(temp);
					temp = "";
					j++;
				}
				temp += graph_per_line[i][j];
				j++;
			}
			this->individualPipes[i].push_back(temp);
	}
	
	this->startTime = atoi((*read_it).c_str());
}

// "Task" getter function
string uninformedSearch::getTask() {
	return this->task;
}

// "Source Node" getter function
string uninformedSearch::getSource() {
	return this->source;
}

// "Destination Nodes" getter function
string uninformedSearch::getDestination() {
	return this->destination;
}

// "Middle Nodes" getter function
string uninformedSearch::getMiddleNodes() {
	return this->middlenodes;
}

// "Pipes details" getter function
vector<string> uninformedSearch::getGraphs() {
	return this->graphOfPipes;
}

// Returns the number of pipes in the system
int uninformedSearch::getPipes() {
	return this->pipes;
}

// Returns the list of adjacent nodes
vector<string>* uninformedSearch::getListOfNodes() {
	return this->individualPipes;
}

// Returns the created adjacency list
vector<list<vector<string> > >* uninformedSearch::getadjacency_list() {
	return this->adjList;
}

//Destructor
uninformedSearch::~uninformedSearch() {
	delete individualPipes;
	free (adjMatrix);
}

// Returns total number of nodes in the graph
int uninformedSearch::getNumberOfNodes() {
	string source = this->getSource();
	string destination = this->getDestination();
	string middlenodes = this->getMiddleNodes();
	int i=0; // A count variable
	// vector that counts the number of nodes in the graph and stores all the nodes
	vector<string> count_edge;
	string var=""; 
	
	// Stores Source node into var 
	while(source[i]) {
		if((isspace(source[i]))) {
			count_edge.push_back(k);
			var = "";
			i++;
		}
		var += source[i];
		i++;
	}
	count_edge.push_back(var);
	i=0;
	var="";
	
	// Stores list of Destination nodes into var
	while(destination[i]) {
		if(isspace(destination[i])) {
			count_edge.push_back(var);
			var = "";
			i++;
		}
		var += destination[i];
		i++;
	}
	count_edge.push_back(var);	
	
	i=0;
	var="";
	
	//Stores list of Middle nodes into var
	while(middlenodes[i]) {
		if(isspace(middlenodes[i])) {
			count_edge.push_back(var);
			var = "";
			i++;
		}
		var += middlenodes[i];
		i++;
	}
	count_edge.push_back(var);
	
	// Sorting the Nodes in the graph in Alphabetical order
	std::sort ( count_edge.begin(), count_edge.end() );
	
	int s = 0;
	vector<string>::iterator in= count_edge.begin();
	while ( in != count_edge.end()) {
		this->nodesInfo.push_back(count_edge[s]);
		s++;++in;
	}
	
    	for(int i=0; i<count_edge.size();i++) {
		this->MapNodeToNumber[count_edge[i]] = i;
	}	
	
    	for(int i=0; i<count_edge.size();i++) {
		this->MapNumberToNode[i] = count_edge[i];
	}
	this->totalEdges = count_edge.size();

	return count_edge.size();
}

// Function to test for Goal Node
int uninformedSearch::checkDestination(string &test) {
	int i=0;
	vector<string> dest;
	string var="";
	// Fetching complete list of destination nodes into vector "dest" .
	while(destination[i]) {
		if(isspace(destination[i])) {
			dest.push_back(var);
			var = "";
			i++;
		}
		var += destination[i];
		i++;
	}
	dest.push_back(var);
	
	vector<string>::iterator goal_node;
	goal_node = find (dest.begin(), dest.end(), test);
	if (goal_node != dest.end()) {
		return 1;
	} else {
		return 0;
	}	
}

// Breadth First Search Algorithm
string uninformedSearch::bfs(int &start_node) {
	
    int count = this->totalEdges;
    string destination = this->getDestination();
    int path_cost = this->startTime;
    int *visited=(int *)calloc(count,sizeof(int));
    queue<int> Q;
    visited[start_node]=1;
    Q.push(start_node);
    int inside=0;
    int check_dest =0;
    map<int,int> test;
    test[start_node] = path_cost;
    
    while(!Q.empty()) {
        int x=Q.front();
        Q.pop(); // pop here. we have x now
	check_dest = this->checkDestination(MapNumberToNode[x]);
	
	if( check_dest == 1) {
		string answer = MapNumberToNode[x] + " ";
		stringstream answer_string;
		answer_string << test[x]%24;
		answer += answer_string.str();
		return answer;
		break;
	}
        
        for(int i=0; i<c; i++) {
		if((this->adjMatrix[x][i] == 1) && visited[i] != 1) {
			Q.push(i);
			visited[i] = 1;
			test[i] = test[x] + 1;
		}
	}
    }
    
    if(!check_dest) {
	return "None";
    }
}

// Depth First Search Algorithm
string uninformedSearch::dfs(int &start_node) {
    
    int count = this->totalEdges;
    string destination = this->getDestination();
    int path_cost = this->startTime;
    int *visited=(int *)calloc(count,sizeof(int));
    stack<int> S;
    visited[start_node]=1;
    S.push(start_node);
    int inside = 0;
    int j=0;
    int check_dest =0;
    map<int,int> test;
    test[start_node] = path_cost;
    
    while(!S.empty()) {
        
        int x = S.top();
        S.pop(); // pop here. we have x now
	visited[x] = 1;
	check_dest = this->checkDestination(MapNumberToNode[x]);
	
	if( check_dest == 1) {
		string answer = MapNumberToNode[x] + " ";
		stringstream answer_string;
		answer_string << test[x]%24;
		answer += answer_string.str();
		return answer;
	}
	
	for(int i=count-1; i>=0; i--) {
		if((this->adjMatrix[x][i] == 1) && visited[i] != 1) {
			S.push(i);
                	test[i] = test[x] + 1;
		}
	}
	path_cost += 1;
	
    }

    if(!check_dest) {
    	return "None";
    }
}

// Uniform Cost Search Algorithm
string uninformedSearch::ucs(int &start_node) {
    
    int count = this->totalEdges;
    int path_cost = this->startTime;
    int *visited=(int *)calloc(count,sizeof(int));
    list<vector<int > > Q;
    map<int,int> test;
    vector<int> node_path;
    test[start_node] = path_cost;
    node_path.push_back(path_cost);
    node_path.push_back(start_node);
    Q.push_back(node_path);
    int check_dest =0;
    while(!Q.empty()) {
		
		node_path.clear();
		vector<int> x = Q.front();
		//clear this vector x before processing don't forget
		Q.pop_front();
		vector<int>::iterator vi;
		vi = x.begin();
		int cost = *vi;
		vi++;
		int node = *vi;
		visited[node] = 1;
		vector<list<vector<string> > > *adj = this->getadjacency_list();
		vector<list<vector<string> > >::iterator it;
		check_dest = this->checkDestination(MapNumberToNode[node]);
		if( check_dest == 1) {
			string answer = MapNumberToNode[node] + " ";
			stringstream ss;
            		cost = cost%24;
			ss << cost;
			answer += ss.str();
			return answer;
			break;
		}
		for(int i = 0; i < node; i++) {
				adj++;
		}
		int noset =0;
		for(it = (*adj).begin(); it != (*adj).end(); it++) {
			list<vector<string> > it2=*it;
			list<vector<string> >::iterator iter=it2.begin();
			
			while(iter!=it2.end()) {
				vector<string> it3=*iter;
				vector<string>::iterator iter1 = it3.begin();
				int p_node = MapNodeToNumber[*iter1];
				
				if (visited[p_node] == 1) {
					noset = 1;
				}
				
				iter1++;
				string p_path = *iter1;
				int value = atoi(p_path.c_str());
				++iter1;
				int dont_push= 0;
				
				while(iter1 != it3.end()) {
					string check = *iter1;
					int  checkin = atoi(check.c_str());
					int start = checkin;
					
					if(checkin) {
						iter1++;
						
						while(start) {
							
							int t=0,v=0;
							string ss = *iter1;
							string token[2];
							
							while( ss[t] != '\0'){
							
								if(ss[t] == '-') {
									v++;
									t++;
								}
								token[v] += ss[t]; 
								t++;
							
							}
							int token_0 = atoi(token[0].c_str());
							int token_1 = atoi(token[1].c_str());
							int check_val = cost % 24;
							
							if(token_0 <= check_val && check_val <= token_1) {
								dont_push = 1;
							}
							
							start --;
							iter1++;
						
						}
					}	else {
						break;
					}
				}
				value = test[node] + value;
				
				if(!dont_push)
					test[p_node] = value;
				
				vector<int> vil;
				vil.push_back(value);	
				vil.push_back(p_node);
				int i=0;
				int k=0;
				int d=0;
				
				if(!dont_push) {			
					list<vector<int> >::iterator it1= Q.begin();
					
					for(it1= Q.begin(); it1 != Q.end(); ++it1,++i) {
						vector<int> it2=*it1;
						vector<int>::iterator it;
						it = find(it2.begin()+1, it2.end(), p_node);
						if (it != it2.end()) {
							k =1;
							break;
						}
					}
				
					if( k==1 ) {
						it1= Q.begin();

						for(int j = 0; j < i; j++) {
							it1++;
						}
					
						vector<int> it2=*it1;
						vector<int>::iterator iter=it2.begin();
					
						if((*iter) >= value) {
							it1 = Q.erase(it1);
							Q.insert(it1,vil);
							d =1;
						} else {
							test[p_node] = *iter;
						}
					
						while(iter!=it2.end()) {
							++iter;
						}
					}
				}
				
				if(dont_push == 0 && k == 0 && noset == 0) {
					Q.push_back(vil);
				}
				vil.clear();
				iter++;
			}
			noset = 0;
		}
		x.clear();
		Q.sort();
	}
	if(!check_dest) {
		return "None";
	}
	
}

// Implementation of Adjacency list
void uninformedSearch::adj_list() {
	int count = this->getNumberOfNodes();
	int dummyCount = 0;	
	vector<string> *node_list = this->getListOfNodes();
	int pipes = this->getPipes();
	vector<string>::iterator vector_iterator;
	
	string edge[2];
	vector<string> store_pipes[this->pipes];
	list<vector<string> > list_pipes[this->pipes];
	this->adjList = new vector<list<vector<string> > >[count];
	for(int i = 0; i < pipes; i++) {
		vector_iterator = (*node_list).begin();
		edge[0] = *vector_iterator;
		++vector_iterator;
		edge[1] = *vector_iterator;
		
		vector<string> test = this->nodesInfo;
		vector<string>::iterator testing;
		vector<string>::iterator testing1;
		testing = find(test.begin(), test.end(), edge[0]);
		testing1 = find(test.begin(), test.end(), edge[1]);
		if(testing != test.end() && testing1 != test.end()) {
			
		} else {
			node_list++;
			continue;
		}
		
		int node =  MapNodeToNumber[edge[0]];
		while( vector_iterator != (*node_list).end() ) {
			store_pipes[i].push_back(*vector_iterator);
			++vector_iterator;
		}
		list_pipes[i].push_back(store_pipes[i]);
		this->adjList[node].push_back(list_pipes[i]);
		sort(this->adjList[node].begin(),this->adjList[node].end());
		node_list++;
	}
}

// Implentation of Adjacency Matrix 
void uninformedSearch::adj_matrix() {
	int count = this->getNumberOfNodes();
	this->adjMatrix = (int **) calloc(count, sizeof(int *));
	
	for(unsigned int i = 0; i < count; i++)
		this->adjMatrix[i] = (int *) calloc(count, sizeof(int));
		
	vector<string> *node_list = this->getListOfNodes();
	int pipes = this->getPipes();
	vector<string>::iterator vector_iterator;
	string edge[2];
	for(int i=0; i < pipes; i++) {
		vector_iterator = (*vili).begin();
		edge[0] = *vector_iterator;
		++vector_iterator;
		edge[1] = *vector_iterator;
		
		vector<string> test = this->nodesInfo;
		vector<string>::iterator testing;
		vector<string>::iterator testing1;
		testing = find(test.begin(), test.end(), edge[0]);
		testing1 = find(test.begin(), test.end(), edge[1]);
		if(testing != test.end() && testing1 != test.end()) {
			
		} else {
			node_list++;
			continue;
		}
		
		adjMatrix[MapNodeToNumber[edge[0]]][MapNodeToNumber[edge[1]]] = 1;
		node_list++;
	}
}

// Function that calls the respective Algorithm based on the test case
string uninformedSearch::doTask() {
	
	string source = this->source;
	string string_source="";
	int i=0;
	vector<string> source_check;
	// Collecting Source node in a vector 
	while(source[i]) {
		if((isspace(source[i]))) {
			source_check.push_back(string_source);
			string_source = "";
			i++;
		}
		string_source += source[i];
		i++;
	}
	
	source_check.push_back(string_source);
	
	//Call to BFS Function
	if(task.compare("BFS") == 0 || task.compare("bfs") == 0) {
		this->adj_matrix();
		return this->bfs(MapNodeToNumber[source_check[0]]);
	}
	
	//Call to DFS Function
	if(task.compare("DFS") == 0 || task.compare("dfs") == 0) {
		this->adj_matrix();
		return this->dfs(MapNodeToNumber[source_check[0]]);
	}
	
	//Call to UCS Function
	if(task.compare("UCS") == 0 || task.compare("ucs") == 0) {
		this->adj_list();
		return this->ucs(MapNodeToNumber[source_check[0]]);
	}
	
}
//Main Function
int main(int argc, char **argv) {
	
	// Reading the input file from command line
	ifstream file(argv[2]);
	string mystr;
	
	// Creating output file
	ofstream outfile;
    	outfile.open("output.txt");
	
	getline(file,mystr);
	
	int no_of_tasks = atoi(mystr.c_str());
	
	// Storing the complete file into a vector
	vector<string> line[no_of_tasks];
	int i=0, j=0;
	
	// Removing trailing spaces and leading spaces
	while(getline(file,mystr)) { 
		mystr.erase(0, mystr.find_first_not_of(" \t\n\r\f\v"));
		mystr.erase(mystr.find_last_not_of(" \n\r\t")+1);
		if(mystr.empty() && j >3) {
			i++;
			j=0;
        	if(i == no_of_tasks) break;				
			getline(file,mystr);
		}
		line[i].push_back(mystr);
		j++;
	}
	
	// Creating object array based on number of testcases present in the input file
	uninformedSearch test_cases[no_of_tasks];
	i = 0;
	int count = no_of_tasks;
	while(count != 0 ) {	
		test_cases[i].setData(line[i]);
		string answer = test_cases[i].doTask();
		outfile << answer << endl; // Appending result of each testcase to the output file
		count--;i++;
	}

	cout<<endl;
	outfile.close();
	return EXIT_SUCCESS; 
}
