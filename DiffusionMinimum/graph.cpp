#include "graph.h"
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

void Graph::reset(){
	for (auto &i : nodes) {
		i.parent = NIL;
		i.priority = DBL_MAX;
		i.type = UNDISCOVERED;
	}
}

void Graph::dijkstra(int s){
	using fibNode = fib::node<Node>;	//fibonacci��
	reset();
	getNodeRef(s).priority = 0;

	fib::FibonacciHeap<Node> Q;
	std::vector<fibNode*> ptrs;	//����fib���еĽڵ�ָ�룬����decreaseKey����
	for (auto &i : nodes) {
		ptrs.push_back(Q.insert(i));	
	}

	while (!Q.isEmpty()) {
		Node n = Q.getMinimum();
		Q.removeMinimum();
		int u = n.id;
		for (auto &i : neighbors[id2index(u)]) {
			if ((UNDISCOVERED == getNodeRef(u).type) && relax(n.id, i.dest, i.weight)) {
				Q.decreaseKey(ptrs[id2index(i.dest)], getNodeRef(i.dest));
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

bool Graph::isNodeExist(int id)const{
	return idTable.end() != idTable.find(id);
}
bool operator < (const Node& m, const Node& n) {
	return m.priority < n.priority;
}
bool operator > (const Node& m, const Node& n) {
	return m.priority > m.priority;
}