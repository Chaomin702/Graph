#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <assert.h>
#include "graph.h"
//从文件导入图，格式： node_source node_dest edge_weight /r/t ...
Graph importEdgesFormFile(const std::string& filename) {
	std::ifstream f(filename);
	assert(f);
	Graph g;
	std::string line;
	int source, dest;
	double weight;
	while (std::getline(f, line)) {
		std::stringstream ss(line);
		ss >> source >> dest >> weight;
		g.insert(source, dest, weight);
	}
	f.close();
	return g;
}
