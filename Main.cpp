#include <iostream>
#include <conio.h>
#include "FindPath.h"
#include "ConsoleRender.h"

#define _W 20
#define _H 20
#define _S (_W * _H)
#define _TL 1//通路
#define _SL 0//死路
#define _LU 2//死路

void main()
{
	int ix = 0;
	int iy = 0;
	int lu[_S], luc;
	int aiMap[_S] = {};
	int map[_S]
	=
	{	
		_TL, _TL, _TL, _TL, _TL, _TL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _TL, _TL, _TL, _SL, _SL, _SL, _TL, 
		_TL, _SL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _SL, _TL, _TL, _TL, _SL, _TL, _TL, _TL, _SL, _TL, 
		_TL, _SL, _SL, _SL, _SL, _SL, _TL, _TL, _TL, _TL, _SL, _TL, _TL, _TL, _SL, _TL, _SL, _TL, _SL, _TL, 
		_TL, _TL, _TL, _TL, _TL, _SL, _TL, _SL, _SL, _SL, _SL, _SL, _SL, _TL, _SL, _TL, _SL, _TL, _SL, _TL, 
		_TL, _SL, _SL, _SL, _TL, _SL, _TL, _TL, _TL, _SL, _TL, _TL, _TL, _TL, _SL, _TL, _SL, _TL, _SL, _TL, 
		_TL, _SL, _TL, _SL, _TL, _SL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _SL, _TL, _SL, _SL, _SL, _TL, 
		_TL, _SL, _TL, _SL, _TL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _TL, _TL, _SL, _TL, _SL, _TL, _TL, _TL, 
		_TL, _SL, _TL, _TL, _TL, _SL, _TL, _TL, _TL, _TL, _TL, _SL, _TL, _TL, _SL, _TL, _SL, _SL, _TL, _TL, 
		_TL, _SL, _SL, _SL, _SL, _SL, _TL, _SL, _SL, _SL, _TL, _SL, _TL, _TL, _SL, _SL, _TL, _SL, _TL, _TL, 
		_TL, _TL, _TL, _TL, _TL, _TL, _TL, _SL, _TL, _SL, _TL, _SL, _TL, _TL, _SL, _TL, _TL, _SL, _TL, _TL, 
		_SL, _TL, _SL, _SL, _TL, _TL, _TL, _SL, _TL, _SL, _TL, _SL, _TL, _TL, _SL, _TL, _TL, _SL, _TL, _TL, 
		_SL, _TL, _TL, _SL, _TL, _SL, _TL, _TL, _TL, _SL, _TL, _SL, _TL, _TL, _SL, _SL, _SL, _SL, _TL, _TL, 
		_SL, _TL, _TL, _SL, _TL, _SL, _TL, _SL, _SL, _SL, _TL, _SL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, 
		_SL, _SL, _SL, _SL, _TL, _SL, _TL, _SL, _TL, _TL, _TL, _SL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, 
		_TL, _TL, _TL, _TL, _TL, _SL, _SL, _SL, _TL, _TL, _TL, _SL, _TL, _SL, _SL, _SL, _SL, _SL, _SL, _TL, 
		_SL, _TL, _TL, _TL, _TL, _TL, _TL, _SL, _TL, _TL, _TL, _SL, _TL, _TL, _SL, _TL, _TL, _TL, _TL, _TL, 
		_SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _TL, _TL, _TL, _SL, _TL, _TL, _SL, _TL, _TL, _SL, _TL, _SL, 
		_TL, _TL, _SL, _TL, _TL, _TL, _TL, _SL, _SL, _SL, _SL, _SL, _TL, _TL, _SL, _SL, _SL, _SL, _TL, _SL, 
		_TL, _TL, _SL, _TL, _SL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _TL, _SL, 
		_SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, _SL, 
	};
	for (int i = 0; i < _S; ++i)
		aiMap[i] = map[i];

	CConsoleRender cr(_W,_H,ix,iy,true);
	int x,y;
	int i_b = 0;
	int UseTime = 0;
	bool FindWay = false;//是否寻过路
	while(1)
	{
		system("cls");
		int b_x = i_b % _W;
		int b_y = i_b / _W;
		for (int i = 0; i < _S; ++i)
		{
			int i_x = i % _W;
			int i_y = i / _W;
			switch (aiMap[i])
			{
			case _TL:cr.SetData(i_x,i_y,"  ");break;
			case _SL:cr.SetData(i_x,i_y,"□");break;
			case _LU:cr.SetData(i_x,i_y,"★");break;
			}
		}
		cr.SetData(b_x,b_y,"囧");
		cr.GetCursor(&x,&y);
		std::cout <<"u--a*寻路,i--广度寻路,o--深度寻路,q--清空路径"<<std::endl ;
		cr.Render();
		std::cout <<"寻路耗时"<<UseTime<<"毫秒";
		int i_e = x + y * _W;
		int input = _getch();
		if (input == 'w' && y > 0)
			y--;
		if (input == 's' && y < _H - 1)
			y++;
		if (input == 'a' && x > 0)
			x--;
		if (input == 'd' && x < _W - 1)
			x++;
		if (input == 'u' && aiMap[i_e] == _TL)
		{
			int t1 = GetTickCount();
			bool zd = FindPathA(aiMap,_W,_H,i_b,i_e,lu,&luc);
			UseTime = GetTickCount() - t1;
			if (zd)
			{
				if (FindWay = true)
				{
					for (int i = 0;i <_S; ++i)
						aiMap[i] = map[i];
				}
				for (int i = 0; i < luc; ++i)
				{
					aiMap[lu[i]] = _LU;
				}
				i_b = i_e;
				FindWay = true;
			}
			else
			{
				std::cout<<std::endl ;
				std::cout<<"找不到路"<<std::endl;
				system("pause");
			}
		}
		if (input == 'i' && aiMap[i_e] == _TL)
		{
			int t1 = GetTickCount();
			bool zd = FindPathW(aiMap,_W,_H,i_b,i_e,lu,&luc);
			UseTime = GetTickCount() - t1;
			if (zd)
			{
				if (FindWay = true)
				{
					for (int i = 0;i <_S; ++i)
						aiMap[i] = map[i];
				}
				for (int i = 0; i < luc; ++i)
				{
					aiMap[lu[i]] = _LU;
				}
				i_b = i_e;
				FindWay = true;
			}
			else
			{
				std::cout<<std::endl ;
				std::cout<<"找不到路"<<std::endl;
				system("pause");
			}
		}
		if (input == 'o' && aiMap[i_e] == _TL)
		{
			int t1 = GetTickCount();
			bool zd = FindPathD(aiMap,_W,_H,i_b,i_e,lu,&luc);
			UseTime = GetTickCount() - t1;
			if (zd)
			{
				if (FindWay = true)
				{
					for (int i = 0;i <_S; ++i)
						aiMap[i] = map[i];
				}
				for (int i = 0; i < luc; ++i)
				{
					aiMap[lu[i]] = _LU;
				}
				i_b = i_e;
				FindWay = true;
			}
			else
			{
				std::cout<<std::endl ;
				std::cout<<"找不到路"<<std::endl;
				system("pause");
			}
		}
		if (input == 'q')
		{
			for (int i = 0;i <_S; ++i)
			{
				//lu[i] = 0;
				aiMap[i] = map[i];
			}
			//luc = 0;
		}
		cr.SetCursor(x,y);
	}
	system("pause");
}