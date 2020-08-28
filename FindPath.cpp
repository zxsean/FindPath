#include "FindPath.h"
#include "SqList.h"
#include "SqHeap.h"
#include "math.h"

static bool _FindPathD(const int* m, //地图
					   int w, //宽
					   int h, //高
					   int e, //终止点
					   int* p, //路径
					   int* c, //路径长度
					   int* s, //死路数组
					   int* sc) //死路数组长度
{
	//得到当前点
	int x = p[*c - 1] % w;
	int y = p[*c - 1] / w;

	//设置上下左右的偏移数组
	static const int offx[] = { 0, 0,-1, 1};
	static const int offy[] = {-1, 1, 0, 0};

	//上下左右找路
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + offx[i];
		int ny = y + offy[i];

		//在地图中
		if (nx >= 0 && nx < w && ny >= 0 && ny < h)
		{
			int nxb = nx + ny * w;

			//找到路
			if (nxb == e)
			{
				//下标放入路径
				p[(*c)++] = nxb;

				return true;
			}

			//是通路
			if (m[nxb])
			{
				//判断是否走过
				bool wz = true;
				for (int j = 0; j < *c; ++j)
				{
					if (p[j] == nxb)
					{
						wz = false;
						break;
					}
				}
				//没有走过
				if (wz)
				{
					//判断是否为死路
					bool sl = false;
					for (int j = 0; j < *sc; ++j)
					{
						if (s[j] == nxb)
						{
							sl = true;
							break;
						}
					}

					//不是死路
					if (!sl)
					{
						//下标放入路径
						p[(*c)++] = nxb;

						//递归
						bool zd = _FindPathD(m, w, h, e, p, c, s, sc);

						//没有找到
						if (!zd)
							//将路放入死路数组
							s[(*sc)++] = p[--(*c)];
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

//假设寻路方向为上下左右
bool FindPathD(const int* m,
			   int w,
			   int h,
			   int b,
			   int e,
			   int* p,
			   int* c)
{
	if (!m ||
		w < 1 ||
		h < 1 ||
		b < 0 ||
		b > w * h - 1 ||
		e < 0 ||
		e > w * h - 1 ||
		!p ||
		!c)
		return false;

	*c = 0;
	p[*c] = b;
	*c += 1;

	if (b == e)
		return true;

	//死路数组及其长度
	int* s = new int[w * h];
	int sc = 0;

	bool zd = _FindPathD(m, w, h, e, p, c, s, &sc);

	delete [] s;

	return zd;
}

//广度优先寻路
bool FindPathW(const int* m,
			   int w,
			   int h,
			   int b,
			   int e,
			   int* p,
			   int* c)
{
	if (!m ||
		w < 1 ||
		h < 1 ||
		b < 0 ||
		b > w * h - 1 ||
		e < 0 ||
		e > w * h - 1 ||
		!p ||
		!c)
		return false;

	//发散点记录数组
	int *f = new int[w * h];

	*c = 0;
	p[*c] = b;
	f[*c] = -1;//起点发散点-1
	*c += 1;

	if (b == e)
		return true;

	int FaSan;//发散点
	int Len = *c;//数组长度初始化等于路径长度
	bool FindWay = true;

	//设置上下左右的偏移数组
	static const int offx[] = { 0, 0,-1, 1};
	static const int offy[] = {-1, 1, 0, 0};

	while(FindWay)
	{
		//得到当前点
		FaSan = p[*c - 1];//发散点
		int x = FaSan % w;
		int y = FaSan / w;
		//上下左右找路
		for (int i = 0; i < 4; ++i)
		{
			int nx = x + offx[i];
			int ny = y + offy[i];
			//四方向查找完毕
			//在地图中
			if (nx >= 0 && nx < w && ny >= 0 && ny < h)
			{
				int nxb = nx + ny * w;

				//找到路
				if (nxb == e)
				{
					//下标放入路径
					p[Len] = nxb;
					f[Len] = FaSan;
					Len += 1;
					FindWay = false;
					break;
				}

				//是通路
				if (m[nxb])
				{
					//判断是否走过
					bool wz = true;
					for (int j = 0; j < Len; ++j)
					{
						if (p[j] == nxb)
						{
							wz = false;
							break;
						}
					}
					//没有走过
					if (wz)
					{
						p[Len] = nxb;
						f[Len] = FaSan;
						Len += 1;
					}
				}
			}
		}
		if (*c == Len)//所有可走路径点尝试完,依旧没有路可走
			return false;
		else
			*c += 1;//一次四周for循环找通路完毕后路径下标+1查找下一路径点四周通路
	}

	if(FindWay == false)//输出线路
	{
		int LuLen = 0;//路径长度初始化
		Len -= 1;//Len-1否则数非法
		int* Lu = new int[Len];
		Lu[LuLen] = p[Len];//路径开始点为子数组最后一位
		LuLen += 1;//路径长度+1
		while (Len > 0)
		{
			for (int i = 0;i < Len;++i)
			{
				if (p[i] == f[Len])//在父数组中查找子数组中的发散点
				{
					Len = i;//更改长度
				}
			}
			Lu[LuLen] = p[Len];
			LuLen += 1;
		}
		for (int i = 0; i < LuLen; i++)//数组拷贝
			p[i] = Lu[i];
		*c = LuLen;//数组长度修改
	}
	return true;
}

//A*寻路
//辅助函数
bool bigger(const ANODE* a, const ANODE* b)//定位辅助函数
{
	return a->index > b->index;
}

bool LocaFather(const ANODE* a, const ANODE* b)//定位辅助函数
{
	return a->father == b->index;
}

bool biggerF(const ANODE* a, const ANODE* b)//堆辅助函数得到最小f值
{
	return a->f < b->f;
}

bool FindOp(const ANODE* a, const ANODE* b)//开表定位
{
	return a->index == b->index;
}

int GetH(int b,int e,int w)
{
	int ex = e % w;
	int ey = e / w;
	int bx = b % w;
	int by = b / w;
	//|x1 - x2| + |y1 - y2|
	int h = abs(bx - ex) + abs(by - ey);
	return h * 5;
}

//A*寻路主函数
bool FindPathA(const int* m,
			   int w,
			   int h,
			   int b,
			   int e,
			   int* p,
			   int* c)
{
	if (!m ||
		w < 1 ||
		h < 1 ||
		b < 0 ||
		b > w * h - 1 ||
		e < 0 ||
		e > w * h - 1 ||
		!p ||
		!c)
		return false;

	if (b == e)
		return true;

	//设置上,下,左,右,左上,右上,左下,右下的偏移数组
	static const int offx[] = { 0, 0,-1, 1, -1, 1,-1,1};
	static const int offy[] = {-1, 1, 0, 0, -1,-1, 1,1};
	static const int offG[] = { 5, 5, 5, 5, 7, 7, 7, 7};//移动消耗
	CSqHeap<ANODE> OpenList(biggerF);//开表
	CSqList<ANODE> CloseList(bigger);//闭表
	ANODE Start;
	Start.father = -1;//父地图块下标
	Start.index = b;//本地图块下标
	Start.g = 0;//走过路径消耗
	Start.h = GetH(b,e,w);//预估路径消耗
	Start.f = Start.g + Start.h;//f值
	OpenList.Enter(Start);
	bool FindWay = false;
	int Father;
	int x,y;

	while(OpenList.Length() && FindWay == false)
	{
		ANODE MinF;
		OpenList.Quit(&MinF);
		CloseList.Push(MinF);
		x = MinF.index % w;
		y = MinF.index / w;
		for (int i = 0;i < 8;++i)
		{
			int nx = x + offx[i];
			int ny = y + offy[i];

			if (nx >= 0 && nx < w && ny >= 0 && ny < h)
			{
				int nxb = nx + ny * w;
				//找到路
				if (nxb == e)
				{
					FindWay = true;
					Father = MinF.index;
					break;
				}
				else
				{
					if (m[nxb])//是通路
					{
						ANODE N;
						N.index = nx + ny * w;
						N.father = MinF.index;
						N.g = MinF.g + offG[i];
						N.h = GetH(N.index,e,w);
						N.f = N.g + N.h;

						if(CloseList.Locate(N,0) == -1)//判断N是否在闭表中
						{
							if (OpenList.Locate(N,0,FindOp) != -1)//判断N是否在开表中
							{
								if(OpenList.BiggerG(N,0,FindOp))//判断N是否比开表中N的G小
								{
									//更新开表中N
									//int pos = OpenList.XiuGai(N,0,FindOp);
									OpenList.XiuGai(N,0,FindOp);
									//OpenList.Get(pos);
									OpenList.Enter(N);
								}
							}
							else
								OpenList.Enter(N);
						}
					}
				}
			}
		}
	}

	if (FindWay)
	{
		ANODE Temp;
		Temp.index = Father;
		*c = 0;
		int pos = CloseList.Locate(Temp,0);
		p[*c] = e;
		(*c) += 1;
		while(1)
		{
			if (*c > 1)
				pos = CloseList.LocateFather(Temp,0,LocaFather);

			Temp = *CloseList.Get(pos - 1);
			CloseList.Erase(pos);
			p[*c] = Temp.index;
			(*c) += 1;
			if (Temp.father == -1)
				break;
		}
		return true;
	}
	return false;
}