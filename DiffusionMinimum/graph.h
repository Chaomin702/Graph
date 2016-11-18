#pragma once
#include <vector>
#include <unordered_map>
#include <limits>
#include <assert.h>
#include <float.h>
#include <list>
#include <map>
#include <unordered_set>
enum {
	NIL = -1
};
typedef enum {
	UNDISCOVERED,
	VISITED
}nodeType;
struct Node {
	int id;		
	int indegree, outdegree;
	int parent;
	double priority;		//·��Ȩ��
	nodeType type;
	Node() = default;
	explicit Node(int ID) :id(ID), indegree(0), outdegree(0), parent(NIL), priority(DBL_MAX),type(UNDISCOVERED) {}
};
bool operator < (const Node& m, const Node& n);
bool operator <=(const Node&m, const Node&n);
bool operator >=(const Node&m, const Node&n);
bool operator > (const Node& m, const Node& n);
bool operator ==(const Node&m, const Node&n);
struct compare_node
{
	bool operator()(const Node& n1, const Node& n2) const {
		return n1.priority > n2.priority;
	}
};
std::ostream& operator <<(std::ostream& os, const Node&m);
struct Edge {
	int source, dest;
	double weight;
	Edge(int s, int d, double w) :source(s), dest(d), weight(w) {}
};
bool operator == (const Edge& m, const Edge&n);
class Graph {
public:
	Graph() = default;
	//���ļ�����ͼ����ʽ�� node_source node_dest edge_weight /r/t ...
	Graph(const std::string&);
	using matrix = std::vector<std::vector<double>>;
	//�ڵ�����
	int nodesNum()const { return nodes.size(); }
	//����ڵ�
	void insert(int id) {
		insert(Node(id));
	}
	//s->t�ı�Ȩ�أ��������򷵻�DBL_MAX
	double weight(int s, int t);
	//�����(source,dest,weight)
	void insert(int s, int t, double w) {
		insert(Edge(s, t, w));
	}
	//��ȡ�ڵ㿽��
	Node getNode(int id) const{
		auto it = nodes.find(id);
		assert(it != nodes.end());
		return it->second;
	}
	//�ڵ����
	const std::vector<Edge>& getNeighbors(int id)const{
		auto it = neighbors.find(id);
		assert(it != neighbors.end());
		return it->second;
	}
	//�ڵ��б�
	std::vector<int> getNodeList()const {
		std::vector<int> L;
		for (auto &i : nodes)
			L.push_back(i.first);
		return L;
	}
	//��ȡ�ڵ�Ȩ��
	double nodePriority(int id)const{return getNodeRef(id).priority; }
	//���ǰ��
	int nodeParent(int id)const {
		return getNodeRef(id).parent;
	}
	void reset();
	//dijkstra���·����������CLRS chapter24ʵ��
	void dijkstra(int s);
	//��ȡs->t���·������
	std::list<int> shortestpath(int s, int t);
	//�������нڵ�Ե����·��Ȩ��
	matrix johnson();
	//����Ϊcsv�ļ�
	void exportGraph(const std::string&);
private:
	std::map<int, Node> nodes;
	std::map<int, std::vector<Edge>> neighbors;
	bool isNodeExist(int id)const {
		return nodes.end() != nodes.find(id);
	}
	const Node& getNodeRef(int id) const{
		assert(isNodeExist(id));
		return nodes.find(id)->second;
	}
	Node& getNodeRef(int id) {
		assert(isNodeExist(id));
		return nodes[id];
	}
	void insert(const Node&);
	void insert(const Edge&);
	//�ɳڷ���������dijkstra
	bool relax(int u, int v, double w);

};