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
	double priority;		//·��Ȩ��
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
	//�ڵ�����
	int nodesNum()const { return nodes.size(); }
	//����ڵ�
	void insert(int id) {
		insert(Node(id));
	}
	//�����(source,dest,weight)
	void insert(int s, int t, double w) {
		insert(Edge(s, t, w));
	}
	//��ȡ�ڵ㿽��
	Node getNode(int id) const{
		return nodes[id2index(id)];
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

private:
	std::map<int, int> idTable;	//�ڵ�id=>�ڲ���������ӳ��
	std::vector<Node> nodes;	//�ڵ㼯
	std::vector<std::vector<Edge>> neighbors;	//�ڵ��ھӼ�

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
	//�ɳڷ���������dijkstra
	bool relax(int u, int v, double w);

};