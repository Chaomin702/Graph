#pragma once
#include <vector>
#include "graph.h"

class Community {
public:
	Community(Graph &);
private:
	Graph g;
	int id;
};