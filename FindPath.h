#ifndef _FIND_PATH_H_
#define _FIND_PATH_H_

//��ͼΪchar����,��0Ϊͨ·,0Ϊ�ϰ�

//�������Ѱ·
bool FindPathD(const int* m, //��ͼ
			   int w, //��ͼ��
			   int h, //��ͼ��
			   int b, //��ʼ�±�
			   int e, //��ֹ�±�
			   int* p, //�õ���·��(Ӧ�ô���һ�������׵�ַ,�������СӦ��Ϊ��ͼ�Ĵ�С)
			   int* c); //�õ���·������(Ӧ�ô���һ��int�ĵ�ַ)

//�������Ѱ·
bool FindPathW(const int* m,
			   int w,
			   int h,
			   int b,
			   int e,
			   int* p,
			   int* c);

//A*Ѱ·
bool FindPathA(const int* m,
			   int w,
			   int h,
			   int b,
			   int e,
			   int* p,
			   int* c);

struct ANODE//a*�ṹ��
{
	int father;//���ڵ�
	int index;//��ǰ�ڵ�
	int g;
	int h;//�����ٷ��� ��ǰ��Ŀ�ĸ�֮��ˮƽ�ʹ�ֱ�ķ���������ܺ� * 5
	int f;
};
//fֵ g + h
#endif