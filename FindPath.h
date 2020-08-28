#ifndef _FIND_PATH_H_
#define _FIND_PATH_H_

//地图为char类型,非0为通路,0为障碍

//深度优先寻路
bool FindPathD(const int* m, //地图
			   int w, //地图宽
			   int h, //地图高
			   int b, //起始下标
			   int e, //终止下标
			   int* p, //得到的路径(应该传递一个数组首地址,该数组大小应该为地图的大小)
			   int* c); //得到的路径长度(应该传递一个int的地址)

//广度优先寻路
bool FindPathW(const int* m,
			   int w,
			   int h,
			   int b,
			   int e,
			   int* p,
			   int* c);

//A*寻路
bool FindPathA(const int* m,
			   int w,
			   int h,
			   int b,
			   int e,
			   int* p,
			   int* c);

struct ANODE//a*结构体
{
	int father;//父节点
	int index;//当前节点
	int g;
	int h;//曼哈顿方法 当前格到目的格之间水平和垂直的方格的数量总和 * 5
	int f;
};
//f值 g + h
#endif