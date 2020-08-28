#ifndef _CONSOLE_RENDER_H_
#define _CONSOLE_RENDER_H_

#define _W_MIN 5
#define _W_MAX 30
#define _H_MIN 5
#define _H_MAX 20

#include <windows.h>

class CConsoleRender
{
	int m_W, m_H, m_X, m_Y;
	bool m_S;
	char* m_P;
	HANDLE m_C;

	CConsoleRender(const CConsoleRender& that);
	CConsoleRender& operator  = (const CConsoleRender& that);

public:
	//��Ⱦ�����
	//��Ⱦ�����
	//��ʼ���Xλ��(0~W-1)
	//��ʼ���Yλ��(0~H-1)
	//����Ƿ�ɼ�
	CConsoleRender(int W, int H, int X, int Y, bool S);
	~CConsoleRender();

	void Clear();
	void SetData(int X, int Y, const char* S);
	void SetData(int X, int Y, const int I);
	void Render();

	//���ù��λ��
	void SetCursor(int X, int Y);

	//�õ����λ��
	void GetCursor(int* pX, int* pY);

	//���ù����ʾ���
	void ShowCursor(bool S);

	//������ɫ
	void SetColour(bool Uc,int colour);
};

#endif