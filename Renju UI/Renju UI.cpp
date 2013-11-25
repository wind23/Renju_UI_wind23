// Renju UI.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Renju UI.h"

#define MAX_LOADSTRING 100
#define WM_LEFTCLICK (WM_USER+1)
#define WM_SETPOSITION (WM_USER+2)

// 以下是与界面有关的一些参数，可根据需要修改

COLORREF cBlack=RGB(0,0,0); //黑子颜色
COLORREF cWhite=RGB(255,255,255); //白子颜色
COLORREF cGrey=RGB(63,63,63); //灰子颜色
COLORREF cBoard=RGB(255,255,0); //棋盘颜色
COLORREF cLast=RGB(255,0,0); //最后一子标记颜色
int iSize=13; //棋盘格半径
int iRadius=12; //棋子半径
int iRadius2=2; //星位半径
int xPos=25; //棋盘x坐标
int yPos=15; //棋盘y坐标
int xSize=450; //窗口宽度
int ySize=495; //窗口高度
int xWindow=300; //窗口起始x坐标
int yWindow=100; //窗口起始y坐标
wchar_t Font[]=L"Times New Roman"; //字体
int iSizeFont=15; //字体大小

///////////////////////////////////////////////////////////
int board[15][15]={0};
int move=0;
HBRUSH hBrushBoard;
HBRUSH hBrushBlack;
HBRUSH hBrushWhite;
HBRUSH hBrushGrey;
HBRUSH hBrush0;
HBRUSH hBrush1;
HPEN hPenLine;
HPEN hPenLine2;
HPEN hPenLine3;
HFONT hFont;

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING]=L"Renju UI";					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	hBrushBoard=CreateSolidBrush(cBoard);
	hBrushBlack=CreateSolidBrush(cBlack);
	hBrushWhite=CreateSolidBrush(cWhite);
	hBrushGrey=CreateSolidBrush(cGrey);
	hBrush0=CreateSolidBrush(0);
	hBrush1=CreateSolidBrush(RGB(255,255,255));
	hPenLine=CreatePen(PS_SOLID,1,0);
	hPenLine2=CreatePen(PS_SOLID,3,0);
	hPenLine3=CreatePen(PS_SOLID,1,0);
	hFont=CreateFont(iSizeFont, 0, 0, 0, 700, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,Font);
	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RENJUUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RENJUUI));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RENJUUI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(hBrushBoard);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_RENJUUI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW& ~WS_MAXIMIZEBOX& ~WS_THICKFRAME,
     xWindow, yWindow, xSize, ySize, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		SelectObject(hdc, hPenLine);
		for(int i=0;i<15;i++)
		{
			MoveToEx(hdc, iSize+xPos, (iSize*2+1)*i+iSize+yPos, NULL);
			LineTo(hdc, (iSize*2+1)*14+iSize+1*0+xPos, (iSize*2+1)*i+iSize+yPos);
			MoveToEx(hdc, (iSize*2+1)*i+iSize+xPos, iSize+yPos, NULL);
			LineTo(hdc, (iSize*2+1)*i+iSize+xPos, (iSize*2+1)*14+iSize+1*0+yPos);
		}
		SelectObject(hdc, hPenLine2);
		MoveToEx(hdc, iSize-(1+3/2)-1+xPos, iSize-(1+3/2)-1+yPos, NULL);
		LineTo(hdc, (iSize*2+1)*14+iSize+1+(1+3/2)+xPos, iSize-(1+3/2)-1+yPos);
		LineTo(hdc, (iSize*2+1)*14+iSize+1+(1+3/2)+xPos, (iSize*2+1)*14+iSize+1+(1+3/2)+yPos);
		LineTo(hdc, iSize-(1+3/2)-1+xPos, (iSize*2+1)*14+iSize+1+(1+3/2)+yPos);
		LineTo(hdc, iSize-(1+3/2)-1+xPos, iSize-(1+3/2)-1+yPos);
		LineTo(hdc, (iSize*2+1)*14+iSize+1+(1+3/2)+xPos, iSize-(1+3/2)-1+yPos);
		LineTo(hdc, iSize-(1+3/2)-1+xPos, iSize-(1+3/2)-1+yPos);
		LineTo(hdc, iSize-(1+3/2)-1+xPos, (iSize*2+1)*14+iSize+1+(1+3/2)+yPos);
		LineTo(hdc, (iSize*2+1)*14+iSize+1+(1+3/2)+xPos, (iSize*2+1)*14+iSize+1+(1+3/2)+yPos);
		LineTo(hdc, (iSize*2+1)*14+iSize+1+(1+3/2)+xPos, iSize-(1+3/2)-1+yPos);
		LineTo(hdc, iSize-(1+3/2)-1+xPos, iSize-(1+3/2)-1+yPos);
		SetPixel(hdc, iSize-4+xPos, iSize-4+yPos, 0);
		SetPixel(hdc, iSize+(iSize*2+1)*14+4+xPos, iSize+(iSize*2+1)*14+4+yPos, 0);
		SetPixel(hdc, iSize-4+xPos, iSize+(iSize*2+1)*14+4+yPos, 0);
		SetPixel(hdc, iSize+(iSize*2+1)*14+4+xPos, iSize-4+yPos, 0);
		SetPixel(hdc, iSize+(iSize*2+1)*14+xPos, iSize+(iSize*2+1)*14+yPos, 0);
		SelectObject(hdc, hPenLine);
		SelectObject(hdc, hBrush0);
		Ellipse(hdc, (iSize*2+1)*3+iSize-iRadius2+xPos, (iSize*2+1)*3+iSize-iRadius2+yPos, (iSize*2+1)*3+iSize+1+iRadius2+1-1+xPos, (iSize*2+1)*3+iSize+1+iRadius2+1-1+yPos);
		Ellipse(hdc, (iSize*2+1)*3+iSize-iRadius2+xPos, (iSize*2+1)*11+iSize-iRadius2+yPos, (iSize*2+1)*3+iSize+1+iRadius2+1-1+xPos, (iSize*2+1)*11+iSize+1+iRadius2+1-1+yPos);
		Ellipse(hdc, (iSize*2+1)*11+iSize-iRadius2+xPos, (iSize*2+1)*11+iSize-iRadius2+yPos, (iSize*2+1)*11+iSize+1+iRadius2+1-1+xPos, (iSize*2+1)*11+iSize+1+iRadius2+1-1+yPos);
		Ellipse(hdc, (iSize*2+1)*11+iSize-iRadius2+xPos, (iSize*2+1)*3+iSize-iRadius2+yPos, (iSize*2+1)*11+iSize+1+iRadius2+1-1+xPos, (iSize*2+1)*3+iSize+1+iRadius2+1-1+yPos);
		Ellipse(hdc, (iSize*2+1)*7+iSize-iRadius2+xPos, (iSize*2+1)*7+iSize-iRadius2+yPos, (iSize*2+1)*7+iSize+1+iRadius2+1-1+xPos, (iSize*2+1)*7+iSize+1+iRadius2+1-1+yPos);

		SelectObject (hdc, hFont);
		SetTextColor (hdc, 0);
		SetBkMode(hdc, TRANSPARENT);
		for(int i=0;i<15;i++)
		{
			SIZE size;
			TCHAR b[3];
			TCHAR a[2]={'A'+i,0};
			if(14-i<=8)
			{
				b[0]='1'+14-i;
				b[1]=0;
				b[2]=0;
			}
			else
			{
				b[0]='1';
				b[1]='1'+4-i;
				b[2]=0;
			}
			GetTextExtentPoint32(hdc, a, lstrlen(a), &size);
			TextOut(hdc, (int)((iSize*2+1)*i+iSize-size.cx/2+xPos), (int)((iSize*2+1)*14.8+iSize-size.cy/2+yPos), a, lstrlen(a));
			GetTextExtentPoint32(hdc, b, lstrlen(b), &size);
			TextOut(hdc, (int)((iSize*2+1)*(-0.8)+iSize-size.cx/2+xPos), (int)((iSize*2+1)*i+iSize-size.cy/2+yPos), b, lstrlen(b));
		}
		
		for(int i=0;i<15;i++)
		{
			for(int j=0;j<15;j++)
			{
				if(board[i][j]>0)
				{
					if(board[i][j]>2000)
					{
						SelectObject(hdc, hPenLine3);
						SelectObject(hdc, hBrushGrey);
						Ellipse(hdc, (iSize*2+1)*i+iSize+1-iRadius-1+xPos, (iSize*2+1)*j+iSize+1-iRadius-1+yPos, (iSize*2+1)*i+iSize+1+iRadius+xPos, (iSize*2+1)*j+iSize+1+iRadius+yPos);
						SelectObject (hdc, hFont);
						SetBkMode(hdc, TRANSPARENT);
						SetTextColor(hdc, cLast);
						TCHAR c[4];
						SIZE size;
						wsprintf(c, L"%d", board[i][j]-2000);
						GetTextExtentPoint32(hdc, c, lstrlen(c), &size);
						TextOut(hdc, (iSize*2+1)*i+iSize+xPos-size.cx/2, (iSize*2+1)*j+iSize+yPos-size.cy/2, c, lstrlen(c));
					}
					else if(board[i][j]>1000)
					{
						SelectObject(hdc, hPenLine3);
						SelectObject(hdc, hBrushBlack);
						Ellipse(hdc, (iSize*2+1)*i+iSize+1-iRadius-1+xPos, (iSize*2+1)*j+iSize+1-iRadius-1+yPos, (iSize*2+1)*i+iSize+1+iRadius+xPos, (iSize*2+1)*j+iSize+1+iRadius+yPos);
						SelectObject (hdc, hFont);
						SetBkMode(hdc, TRANSPARENT);
						SetTextColor(hdc, cLast);
						TCHAR c[4];
						SIZE size;
						wsprintf(c, L"%d", board[i][j]-1000);
						GetTextExtentPoint32(hdc, c, lstrlen(c), &size);
						TextOut(hdc, (iSize*2+1)*i+iSize+xPos-size.cx/2, (iSize*2+1)*j+iSize+yPos-size.cy/2, c, lstrlen(c));
					}
					else
					{
						SelectObject(hdc, hPenLine3);
						SelectObject(hdc, hBrushBlack);
						Ellipse(hdc, (iSize*2+1)*i+iSize+1-iRadius-1+xPos, (iSize*2+1)*j+iSize+1-iRadius-1+yPos, (iSize*2+1)*i+iSize+1+iRadius+xPos, (iSize*2+1)*j+iSize+1+iRadius+yPos);
						SelectObject (hdc, hFont);
						SetBkMode(hdc, TRANSPARENT);
						SetTextColor(hdc, RGB(255,255,255));
						TCHAR c[4];
						SIZE size;
						wsprintf(c, L"%d", board[i][j]);
						GetTextExtentPoint32(hdc, c, lstrlen(c), &size);
						TextOut(hdc, (iSize*2+1)*i+iSize+xPos-size.cx/2, (iSize*2+1)*j+iSize+yPos-size.cy/2, c, lstrlen(c));
					}
				}
				else if(board[i][j]<0)
				{
					if(board[i][j]<-1000)
					{
						SelectObject(hdc, hPenLine3);
						SelectObject(hdc, hBrushWhite);
						Ellipse(hdc, (iSize*2+1)*i+iSize+1-iRadius-1+xPos, (iSize*2+1)*j+iSize+1-iRadius-1+yPos, (iSize*2+1)*i+iSize+1+iRadius+xPos, (iSize*2+1)*j+iSize+1+iRadius+yPos);
						SelectObject (hdc, hFont);
						SetBkMode(hdc, TRANSPARENT);
						SetTextColor(hdc, cLast);
						TCHAR c[4];
						SIZE size;
						wsprintf(c, L"%d", -(board[i][j]+1000));
						GetTextExtentPoint32(hdc, c, lstrlen(c), &size);
						TextOut(hdc, (iSize*2+1)*i+iSize+xPos-size.cx/2, (iSize*2+1)*j+iSize+yPos-size.cy/2, c, lstrlen(c));
					}
					else
					{
						SelectObject(hdc, hPenLine3);
						SelectObject(hdc, hBrushWhite);
						Ellipse(hdc, (iSize*2+1)*i+iSize+1-iRadius-1+xPos, (iSize*2+1)*j+iSize+1-iRadius-1+yPos, (iSize*2+1)*i+iSize+1+iRadius+xPos, (iSize*2+1)*j+iSize+1+iRadius+yPos);
						SelectObject (hdc, hFont);
						SetBkMode(hdc, TRANSPARENT);
						SetTextColor(hdc, RGB(0,0,0));
						TCHAR c[4];
						SIZE size;
						wsprintf(c, L"%d", -board[i][j]);
						GetTextExtentPoint32(hdc, c, lstrlen(c), &size);
						TextOut(hdc, (iSize*2+1)*i+iSize+xPos-size.cx/2, (iSize*2+1)*j+iSize+yPos-size.cy/2, c, lstrlen(c));
					}
				}
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		{
			int xP=LOWORD(lParam);
			int yP=HIWORD(lParam);			
			int x=(xP-xPos+iSize*2+1)/(iSize*2+1)-1;
			int y=(yP-yPos+iSize*2+1)/(iSize*2+1)-1;
			if(x>=0&&x<=14&&y>=0&&y<=14)
			{
				SendMessage(hWnd, WM_LEFTCLICK, 0, x*256+y);
			}
		}
		break;
	case WM_RBUTTONDOWN: //这里是右键单击的动作，可根据需要修改
		{
			if(move>0)
			{
				int f=0;
				for(int i=0;i<15;i++)
				{
					for(int j=0;j<15;j++)
					{
						if(board[i][j]==move+1000||board[i][j]==-move-1000)
						{
							SendMessage(hWnd, WM_SETPOSITION, 0, i*256+j); 
							f=1;
							if(move>0)
							{
								int f1=0;
								for(int i1=0;i1<15;i1++)
								{
									for(int j1=0;j1<15;j1++)
									{
										if(board[i1][j1]==move||board[i1][j1]==-move)
										{
											int cc;
											if(move%2==1)
											{
												cc=1;
											}
											else
											{
												cc=-1;
											}
											SendMessage(hWnd, WM_SETPOSITION, cc*(move+1000), i1*256+j1); 
											f1=1;
										}
										if(f1)
										{
											break;
										}
									}
									if(f1)
									{
										break;
									}
								}
							}
						}
						if(f)
						{
							break;
						}
					}
					if(f)
					{
						break;
					}
				}
			}
		}
		break;
	case WM_LEFTCLICK: // 这里是左键单击坐标(x,y)之后的动作，可根据需要修改
		{
			int x=lParam/256;
			int y=lParam%256;
			if(board[x][y]==0)
			{
				int f=0;
				if(move>0)
				{
					for(int i=0;i<15;i++)
					{
						for(int j=0;j<15;j++)
						{
							if(board[i][j]==1000+move)
							{
								SendMessage(hWnd, WM_SETPOSITION, board[i][j]-1000, i*256+j);
								f=1;
							}
							else if(board[i][j]==-1000-move)
							{
								SendMessage(hWnd, WM_SETPOSITION, board[i][j]+1000, i*256+j);
								f=1;
							}
							if(f)
							{
								break;
							}
						}
						if(f)
						{
							break;
						}
					}
				}
				if(move%2==0)
				{
					SendMessage(hWnd, WM_SETPOSITION, move+1+1000, x*256+y);
				}
				else
				{
					SendMessage(hWnd, WM_SETPOSITION, -(move+1+1000), x*256+y);
				}
			}
		}
		break;
	case WM_SETPOSITION: // 将棋盘board[x][y]处的值设为v，发送消息：
							// SendMessage(hWnd, WM_SETPOSITION, v, x*256+y);
							// v的值：
								// 1~225: 黑子
								// -1~-225：白子
								// 1001~1225：黑子（最后一子，红色标记）
								// -1001~-1225：白子（最后一子，红色标记）
								// 2001~2225：黑子打点（灰色棋子）
								// 具体值为棋子的标号
		{
			int x=lParam/256;
			int y=lParam%256;
			int v=wParam;
			int vPre=board[x][y];
			board[x][y]=v;
			int m;
			int mPre;
			if(vPre==0||vPre>2000)
			{
				mPre=0;
			}
			else
			{
				mPre=1;
			}
			if(v==0||v>2000)
			{
				m=0;
			}
			else
			{
				m=1;
			}
			move+=m-mPre;
			RECT rect;
			rect.left=(iSize*2+1)*x+iSize+1-iSize-1+xPos;
			rect.top=(iSize*2+1)*y+iSize+1-iSize-1+yPos;
			rect.right=(iSize*2+1)*x+iSize+1+iSize+xPos;
			rect.bottom=(iSize*2+1)*y+iSize+1+iSize+yPos;
			InvalidateRect(hWnd, &rect, TRUE);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
