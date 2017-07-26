// ACOStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "GhostMan.h"
#include "ACOStatic.h"


// CACOStatic

IMPLEMENT_DYNAMIC(CACOStatic, CStatic)

CACOStatic::CACOStatic()
{
	m_nClicked = 0;
}

CACOStatic::~CACOStatic()
{
}


BEGIN_MESSAGE_MAP(CACOStatic, CStatic)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CACOStatic 消息处理程序



void CACOStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACKMOUSEEVENT csTME;
	csTME.cbSize = sizeof(csTME);
	csTME.dwFlags = TME_LEAVE | TME_HOVER;
	csTME.hwndTrack = m_hWnd;		// 指定要 追踪 的窗口 
	csTME.dwHoverTime = 10;			// 鼠标在按钮上停留超过 10ms ，才认为状态为 HOVER
	::_TrackMouseEvent(&csTME);	// 开启 Windows 的 WM_MOUSELEAVE ， WM_MOUSEHOVER 事件支持
	//	CStatic::OnMouseMove(nFlags, point);
}


void CACOStatic::OnMouseLeave()
{

	if (m_nClicked)
	{
		HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SA_CLICK), RT_GROUP_ICON);
		HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SA_CLICK));
		SetBitmap(hBmp);
	}
	else
	{
		HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SA_NORMAL), RT_GROUP_ICON);
		HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SA_NORMAL));
		SetBitmap(hBmp);
	}


	CStatic::OnMouseLeave();
}

void CACOStatic::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SA_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SA_CLICK));
	SetBitmap(hBmp);

	CStatic::OnMouseHover(nFlags, point);
}

BOOL CACOStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 使用自己的鼠标绘制函数。
	::SetCursor(::LoadCursorW(NULL, IDC_HAND));
	return TRUE;
}
