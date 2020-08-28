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
	//渲染区域宽
	//渲染区域高
	//初始光标X位置(0~W-1)
	//初始光标Y位置(0~H-1)
	//光标是否可见
	CConsoleRender(int W, int H, int X, int Y, bool S);
	~CConsoleRender();

	void Clear();
	void SetData(int X, int Y, const char* S);
	void SetData(int X, int Y, const int I);
	void Render();

	//设置光标位置
	void SetCursor(int X, int Y);

	//得到光标位置
	void GetCursor(int* pX, int* pY);

	//设置光标显示与否
	void ShowCursor(bool S);

	//设置颜色
	void SetColour(bool Uc,int colour);
};

#endif