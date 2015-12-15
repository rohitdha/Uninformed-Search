#ifndef _waterFlow_h_included_
#define _waterFlow_h_included_

using namespace std;

class uninformedSearch {
	string task, source, destination, middlenodes;
	int pipes;
	vector<string> graphOfPipes;
	vector<string> *individualPipes;
	vector<string> nodesInfo;
	vector<list<vector<string> > > *adjList;
	int startTime;
	map<string,int> MapNodeToNumber;
	map<int,string> MapNumberToNode;
	int **adjMatrix;
	int totalEdges;
public:
	uninformedSearch();
	uninformedSearch(vector<string> & line);
 	void setData(vector<string> & line);
	void getData();
	string getTask();
	string getSource();
	string getMiddleNodes();
	string getDestination();
	vector<string> getGraphs();
	vector<string>* getListOfNodes();
	vector<list<vector<string> > >* getadjacency_list();
	int getPipes();
	string bfs(int &);
	string dfs(int &);
	string ucs(int &);
	string doTask();
	int getNumberOfNodes();
	void adj_matrix();
	void adj_list();
	int checkDestination(string &);
	~uninformedSearch();
};

#endif
