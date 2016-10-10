#pragma once
#include <vector>
#include <unordered_map>
#include <limits>
#include <assert.h>
#include <float.h>
#include <list>
#include <map>
#include "fibonacci.hpp"
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
	double priority;		//路径权重
	nodeType type;
	Node() = default;
	Node(int ID) :id(ID), indegree(0), outdegree(0), parent(NIL), priority(DBL_MAX),type(UNDISCOVERED) {}
};
bool operator < (const Node& m, const Node& n);
bool operator > (const Node& m, const Node& n);
struct Edge {
	int source, dest;
	double weight;
	Edge(int s, int d, double w) :source(s), dest(d), weight(w) {}
};

class Graph {
public:
	using matrix = std::vector<std::vector<double>>;
	//节点数量
	int nodesNum()const { return nodes.size(); }
	//插入节点
	void insert(int id) {
		insert(Node(id));
	}
	//插入边(source,dest,weight)
	void insert(int s, int t, double w) {
		insert(Edge(s, t, w));
	}
	//获取节点拷贝
	Node getNode(int id) const{
		return nodes[id2index(id)];
	}
	//获取节点权重
	double nodePriority(int id)const{return getNodeRef(id).priority; }
	//借点前驱
	int nodeParent(int id)const {
		return getNodeRef(id).parent;
	}
	void reset();
	//dijkstra最短路方法，参照CLRS chapter24实现
	void dijkstra(int s);
	//获取s->t最短路径链表
	std::list<int> shortestpath(int s, int t);
	//计算所有节点对的最短路径权重
	matrix johnson();

private:
	std::map<int, int> idTable;	//节点id=>内部向量索引映射
	std::vector<Node> nodes;	//节点集
	std::vector<std::vector<Edge>> neighbors;	//节点邻居集

	bool isNodeExist(int id)const;
	int id2index(int id)const {
		assert(isNodeExist(id));
		return idTable.find(id)->second;
	}
	const Node& getNodeRef(int id) const{
		return nodes[id2index(id)];
	}
	Node& getNodeRef(int id) {
		return nodes[id2index(id)];
	}
	void insert(const Node&);
	void insert(const Edge&);
	//松弛方法，用于dijkstra
	bool relax(int u, int v, double w);

};