#include "FindPath.h"
#include "SqList.h"
#include "SqHeap.h"
#include "math.h"

static bool _FindPathD(const int* m, //��ͼ
					   int w, //��
					   int h, //��
					   int e, //��ֹ��
					   int* p, //·��
					   int* c, //·������
					   int* s, //��·����
					   int* sc) //��·���鳤��
{
	//�õ���ǰ��
	int x = p[*c - 1] % w;
	int y = p[*c - 1] / w;

	//�����������ҵ�ƫ������
	static const int offx[] = { 0, 0,-1, 1};
	static const int offy[] = {-1, 1, 0, 0};

	//����������·
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + offx[i];
		int ny = y + offy[i];

		//�ڵ�ͼ��
		if (nx >= 0 && nx < w && ny >= 0 && ny < h)
		{
			int nxb = nx + ny * w;

			//�ҵ�·
			if (nxb == e)
			{
				//�±����·��
				p[(*c)++] = nxb;

				return true;
			}

			//��ͨ·
			if (m[nxb])
			{
				//�ж��Ƿ��߹�
				bool wz = true;
				for (int j = 0; j < *c; ++j)
				{
					if (p[j] == nxb)
					{
						wz = false;
						break;
					}
				}
				//û���߹�
				if (wz)
				{
					//�ж��Ƿ�Ϊ��·
					bool sl = false;
					for (int j = 0; j < *sc; ++j)
					{
						if (s[j] == nxb)
						{
							sl = true;
							break;
						}
					}

					//������·
					if (!sl)
					{
						//�±����·��
						p[(*c)++] = nxb;

						//�ݹ�
						bool zd = _FindPathD(m, w, h, e, p, c, s, sc);

						//û���ҵ�
						if (!zd)
							//��·������·����
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

//����Ѱ·����Ϊ��������
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

	//��·���鼰�䳤��
	int* s = new int[w * h];
	int sc = 0;

	bool zd = _FindPathD(m, w, h, e, p, c, s, &sc);

	delete [] s;

	return zd;
}

//�������Ѱ·
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

	//��ɢ���¼����
	int *f = new int[w * h];

	*c = 0;
	p[*c] = b;
	f[*c] = -1;//��㷢ɢ��-1
	*c += 1;

	if (b == e)
		return true;

	int FaSan;//��ɢ��
	int Len = *c;//���鳤�ȳ�ʼ������·������
	bool FindWay = true;

	//�����������ҵ�ƫ������
	static const int offx[] = { 0, 0,-1, 1};
	static const int offy[] = {-1, 1, 0, 0};

	while(FindWay)
	{
		//�õ���ǰ��
		FaSan = p[*c - 1];//��ɢ��
		int x = FaSan % w;
		int y = FaSan / w;
		//����������·
		for (int i = 0; i < 4; ++i)
		{
			int nx = x + offx[i];
			int ny = y + offy[i];
			//�ķ���������
			//�ڵ�ͼ��
			if (nx >= 0 && nx < w && ny >= 0 && ny < h)
			{
				int nxb = nx + ny * w;

				//�ҵ�·
				if (nxb == e)
				{
					//�±����·��
					p[Len] = nxb;
					f[Len] = FaSan;
					Len += 1;
					FindWay = false;
					break;
				}

				//��ͨ·
				if (m[nxb])
				{
					//�ж��Ƿ��߹�
					bool wz = true;
					for (int j = 0; j < Len; ++j)
					{
						if (p[j] == nxb)
						{
							wz = false;
							break;
						}
					}
					//û���߹�
					if (wz)
					{
						p[Len] = nxb;
						f[Len] = FaSan;
						Len += 1;
					}
				}
			}
		}
		if (*c == Len)//���п���·���㳢����,����û��·����
			return false;
		else
			*c += 1;//һ������forѭ����ͨ·��Ϻ�·���±�+1������һ·��������ͨ·
	}

	if(FindWay == false)//�����·
	{
		int LuLen = 0;//·�����ȳ�ʼ��
		Len -= 1;//Len-1�������Ƿ�
		int* Lu = new int[Len];
		Lu[LuLen] = p[Len];//·����ʼ��Ϊ���������һλ
		LuLen += 1;//·������+1
		while (Len > 0)
		{
			for (int i = 0;i < Len;++i)
			{
				if (p[i] == f[Len])//�ڸ������в����������еķ�ɢ��
				{
					Len = i;//���ĳ���
				}
			}
			Lu[LuLen] = p[Len];
			LuLen += 1;
		}
		for (int i = 0; i < LuLen; i++)//���鿽��
			p[i] = Lu[i];
		*c = LuLen;//���鳤���޸�
	}
	return true;
}

//A*Ѱ·
//��������
bool bigger(const ANODE* a, const ANODE* b)//��λ��������
{
	return a->index > b->index;
}

bool LocaFather(const ANODE* a, const ANODE* b)//��λ��������
{
	return a->father == b->index;
}

bool biggerF(const ANODE* a, const ANODE* b)//�Ѹ��������õ���Сfֵ
{
	return a->f < b->f;
}

bool FindOp(const ANODE* a, const ANODE* b)//����λ
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

//A*Ѱ·������
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

	//������,��,��,��,����,����,����,���µ�ƫ������
	static const int offx[] = { 0, 0,-1, 1, -1, 1,-1,1};
	static const int offy[] = {-1, 1, 0, 0, -1,-1, 1,1};
	static const int offG[] = { 5, 5, 5, 5, 7, 7, 7, 7};//�ƶ�����
	CSqHeap<ANODE> OpenList(biggerF);//����
	CSqList<ANODE> CloseList(bigger);//�ձ�
	ANODE Start;
	Start.father = -1;//����ͼ���±�
	Start.index = b;//����ͼ���±�
	Start.g = 0;//�߹�·������
	Start.h = GetH(b,e,w);//Ԥ��·������
	Start.f = Start.g + Start.h;//fֵ
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
				//�ҵ�·
				if (nxb == e)
				{
					FindWay = true;
					Father = MinF.index;
					break;
				}
				else
				{
					if (m[nxb])//��ͨ·
					{
						ANODE N;
						N.index = nx + ny * w;
						N.father = MinF.index;
						N.g = MinF.g + offG[i];
						N.h = GetH(N.index,e,w);
						N.f = N.g + N.h;

						if(CloseList.Locate(N,0) == -1)//�ж�N�Ƿ��ڱձ���
						{
							if (OpenList.Locate(N,0,FindOp) != -1)//�ж�N�Ƿ��ڿ�����
							{
								if(OpenList.BiggerG(N,0,FindOp))//�ж�N�Ƿ�ȿ�����N��GС
								{
									//���¿�����N
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