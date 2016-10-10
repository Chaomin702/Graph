#ifdef _WINDOWS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <algorithm>
#include "graph.h"


void Graph::insert(const Node &n){
	if (isNodeExist(n.id))
		return;
	idTable[n.id] = nodes.size();
	nodes.push_back(n);
	neighbors.push_back(std::vector<Edge>());
}

void Graph::insert(const Edge &e){
	if (!isNodeExist(e.source))
		insert(Node(e.source));
	if (!isNodeExist(e.dest))
		insert(Node(e.dest));
	neighbors[id2index(e.source)].push_back(e);
	++getNodeRef(e.source).outdegree;
	++getNodeRef(e.dest).indegree;
}

bool Graph::relax(int u, int v, double w){
	if (getNodeRef(v).priority > getNodeRef(u).priority + w) {
		getNodeRef(v).priority = getNodeRef(u).priority + w;
		getNodeRef(v).parent = u;
		return true;
	}
	return false;
}

double Graph::weight(int s, int t){
	assert(isNodeExist(s));
	for (auto &i : neighbors[id2index(s)]) {
		if (i.dest == t)
			return i.weight;
	}
	return DBL_MAX;
}

void Graph::reset(){
	for (auto &i : nodes) {
		i.parent = NIL;
		i.priority = DBL_MAX;
		i.type = UNDISCOVERED;
	}
}

void Graph::dijkstra(int s){
	using fibNode = fib::node<Node>;	//fibonacci堆
	reset();
	getNodeRef(s).priority = 0;

	fib::FibonacciHeap<Node> Q;
	std::vector<fibNode*> ptrs;	//保存fib堆中的节点指针，方便decreaseKey传参
	for (auto &i : idTable) {
		ptrs.push_back(Q.insert(getNodeRef(i.first)));	
	}

	while (!Q.isEmpty()) {
		Node n = Q.getMinimum();
		Q.removeMinimum();
		int u = n.id;
		for (auto &i : neighbors[id2index(u)]) {
			if ((UNDISCOVERED == getNodeRef(u).type) && relax(n.id, i.dest, i.weight)) {
				Q.decreaseKey(ptrs[i.dest], getNodeRef(i.dest));
			}
		}
		getNodeRef(u).type = VISITED;
	}
}

std::list<int> Graph::shortestpath(int s, int t){
	std::list<int> L;
	int parent = t;
	while (parent != NIL) {
		L.push_front(parent);
		parent = getNodeRef(parent).parent;
	}
	return L;
}

Graph::matrix Graph::johnson(){
	matrix M;
	for (auto &i : idTable) {
		dijkstra(i.first);
		std::vector<double> temp;
		for (auto &k : idTable)
			temp.push_back(getNodeRef(k.first).priority);
		M.push_back(temp);
	}
	return M;
}

bool Graph::isNodeExist(int id)const{
	return idTable.end() != idTable.find(id);
}
bool operator < (const Node& m, const Node& n) {
	return m.priority < n.priority;
}
bool operator > (const Node& m, const Node& n) {
	return m.priority > n.priority;
}