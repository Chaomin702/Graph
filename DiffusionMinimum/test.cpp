#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <list>
#include "graph.h"
#include "util.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")
//ͼ�ڵ�Ȳ���
static void test_graph_degree() {
	Graph g = importEdgesFormFile("eg.txt");
	EXPECT_EQ_INT(1, g.getNode(0).indegree);
	EXPECT_EQ_INT(2, g.getNode(1).indegree);
	EXPECT_EQ_INT(2, g.getNode(2).indegree);
	EXPECT_EQ_INT(3, g.getNode(3).indegree);
	EXPECT_EQ_INT(2, g.getNode(4).indegree);

	EXPECT_EQ_INT(2, g.getNode(0).outdegree);
	EXPECT_EQ_INT(2, g.getNode(1).outdegree);
	EXPECT_EQ_INT(3, g.getNode(2).outdegree);
	EXPECT_EQ_INT(1, g.getNode(3).outdegree);
	EXPECT_EQ_INT(2, g.getNode(4).outdegree);
}
static void test_graph_dijkstra() {
	Graph g = importEdgesFormFile("eg.txt");
	g.dijkstra(0);
	std::list<int> ans = { 0,2,1 };
	std::list<int> res = g.shortestpath(0, 1);
	EXPECT_EQ_INT(ans.size(), res.size());
	auto it1 = ans.begin(), it2 = res.begin();
	while (it1 != ans.end()) {
		EXPECT_EQ_INT(*it1, *it2);
		++it1;
		++it2;
	}
	EXPECT_EQ_DOUBLE(8.0, g.nodePriority(1));
}
static void test_graph() {
	test_graph_degree();
	test_graph_dijkstra();
}

int main(void) {
	test_graph();
	return 0;
}
