# Graph

- [x] 从文件中导入图
- [x] 基于Fibonacci 堆实现的Dijkstra算法
- [x] 所有节点对最短路径的Johnson算法(不支持负权值边)

### 用例

  ![gra](gra.jpg)

```c++
#include <iostream>
#include <list>
#include "graph.h"

int main(void){
	Graph g = importEdgesFormFile("eg.txt");
	g.dijkstra(0);	//起点为0
 	std::list<int> res = g.shortestpath(0, 1);
  	for(auto i:res){
      std::cout << i << " ";
  	}
  	std::cout << "path weight: " << g.nodePriority(1) << std::endl;
  	return 0;
}
```

output

```
0 2 1
path weight: 8
```