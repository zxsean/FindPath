#include "ConsoleRender.h"
#include <iostream>
#include <windows.h>
#include <assert.h>

#define SC_RED 1
#define SC_GREEN 2
#define SC_BLUD 3

int _S;
int lens1;
int lensCR ;

char* m_P2;//×Ö·û´®Í·
char* m_P3;//¹â±ê
char* m_P4;//×Ö·û´®Î²
bool UseC = false;//ÊÇ·ñÊ¹ÓÃÑÕÉ«
int Scolour;//ÑÕÉ«

CConsoleRender::CConsoleRender(int W, int H, int X, int Y, bool S)
{
	assert(W >= _W_MIN && W <= _W_MAX && H >= _H_MIN && H <= _H_MAX);

	m_W = 2 * W;
	m_H = H;
	_S = 2 * W * H;
	m_X = X;
	m_Y = Y;
	m_S = S;
	m_P = new char[3 * _S]; 
	//m_P = new char[(W * 2 + 5) * (H + 2)];
	Clear();
}

CConsoleRender::~CConsoleRender()
{
	delete [] m_P;
	if (m_P2)
		delete [] m_P2;
	if (m_P3)
		delete [] m_P3;
	if (m_P4)
		delete [] m_P4;
}

void CConsoleRender::Clear()
{
	memset(m_P,' ',_S);
}

void CConsoleRender::Render()
{
	if (UseC)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		//SetConsoleTextAttribute(handle, FOREGROUND_RED);
		switch (Scolour)
		{
		case SC_RED:SetConsoleTextAttribute(handle, FOREGROUND_RED);break;//ºì
		case SC_GREEN:SetConsoleTextAttribute(handle, FOREGROUND_GREEN);break;//ÂÌ
		case SC_BLUD:SetConsoleTextAttribute(handle, FOREGROUND_BLUE);break;//À¶
		default:SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);break;//ºÚÉ«
		}
	}
	lensCR = _S;
	m_P [lensCR] = 0;
	m_P [lensCR+1] = 0;
	m_P [lensCR+2] = 0;
	for (int i = 0; i < _S;++i)
	{
		if (i % m_W == 0 )
		{
			int ilen = 0;
			lensCR+=2;
			ilen=lensCR - _S - 2;
			memcpy(m_P + i+ilen+2, m_P+i+ilen, _S);
			memcpy(m_P + i +ilen, "©§", 2);
		}
		if (i % m_W == m_W - 1)
		{
			int ilen = 0;
			lensCR+=1;
			ilen=lensCR-_S-1;
			memcpy(m_P + i+ilen+1, m_P+i+ilen, _S);
			memcpy(m_P + i +ilen + 1, "\n", 1);
		}
		if (i % m_W == m_W - 1)
		{
			int ilen = 0;
			lensCR+=2;
			ilen=lensCR - _S - 2;
			memcpy(m_P + i+ilen+2, m_P+i+ilen, _S);
			memcpy(m_P + i +ilen, "©§", 2);
		}
	}

	////©³©»©·©¿©ï©¥©§
	std::cout <<"©³";
	for (int i = 0; i < m_W / 2;++i)
		std::cout <<"©¥";
	std::cout <<"©·"<<std::endl ;

	//Êä³öcr×Ö·û´®
	if (m_S)
	{
		int rw = m_W + 5;
		int rh = m_H + 1;
		m_P2 = new char[3 * _S]; 
		m_P3 = new char[3]; 
		m_P4 = new char[3 * _S]; 

		char* q1 = m_P;
		int Headerlen = m_Y * rw + 2 + m_X * 2;//Í·

		char* q2 = q1 + Headerlen;
		int CursorLen = 2;//¹â±ê

		char* q3 = q2 + CursorLen;
		int TailLen = rw * rh - (Headerlen + CursorLen);//Î²

		//¸´ÖÆ×Ö·û´®Í·
		memcpy(m_P2, q1, Headerlen);
		m_P2[Headerlen] = 0;
		//¸´ÖÆ¹â±ê
		memcpy(m_P3, q2, CursorLen);
		m_P3[CursorLen] = 0;
		//¸´ÖÆ×Ö·û´®Î²
		memcpy(m_P4, q3, TailLen);
		m_P4[TailLen] = 0;

		std::cout<<m_P2;

		if (UseC)
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			std::cout<<m_P3;
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			//SetConsoleTextAttribute(handle, FOREGROUND_RED);
			switch (Scolour)
			{
			case SC_RED:SetConsoleTextAttribute(handle, FOREGROUND_RED);break;//ºì
			case SC_GREEN:SetConsoleTextAttribute(handle, FOREGROUND_GREEN);break;//ÂÌ
			case SC_BLUD:SetConsoleTextAttribute(handle, FOREGROUND_BLUE);break;//À¶
			default:SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);break;//ºÚÉ«
			}
		}
		else
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			std::cout<<m_P3;
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		std::cout<<m_P4;
	}
	else
	{
		std::cout <<m_P;
	}
	std::cout <<"©»";
	for (int i = 0; i < m_W / 2;++i)
		std::cout <<"©¥";
	std::cout <<"©¿"<<std::endl ;
}

void CConsoleRender::SetData(int X, int Y, const char* S)
{
	int i_x_y = 2 * X + m_W * Y;
	lens1 = (int)strlen(S);
	for(int i = 0,j = i_x_y; i < lens1;++i,++j )
		m_P[j] = S[i];
}

void CConsoleRender::SetData(int X, int Y, const int I)
{
	char  S[32];
	_itoa_s(I, S, 32, 10);
	int i_x_y = 2 * X + m_W * Y;
	lens1 = (int)strlen(S);
	for(int i = 0,j = i_x_y; i < lens1;++i,++j )
		m_P[j] = S[i];
}
void CConsoleRender::SetCursor(int X, int Y)
{
	m_X = X;
	m_Y = Y;
}

void CConsoleRender::GetCursor(int* pX, int* pY)
{
	*pX = m_X;
	*pY = m_Y;
}

void CConsoleRender::ShowCursor(bool S)
{
	m_S = S;
}

void CConsoleRender::SetColour(bool Uc,int colour)
{
	UseC = Uc;
	Scolour = colour;
}