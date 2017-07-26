// IDAStarStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "GhostMan.h"
#include "IDAStarStatic.h"


// CIDAStarStatic

IMPLEMENT_DYNAMIC(CIDAStarStatic, CStatic)

CIDAStarStatic::CIDAStarStatic()
{
	m_nClicked = 0;
}

CIDAStarStatic::~CIDAStarStatic()
{
}


BEGIN_MESSAGE_MAP(CIDAStarStatic, CStatic)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CIDAStarStatic 消息处理程序


void CIDAStarStatic::OnMouseMove(UINT nFlags, CPoint point)
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


void CIDAStarStatic::OnMouseLeave()
{

	if (m_nClicked)
	{
		HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_CLICK), RT_GROUP_ICON);
		HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_CLICK));
		SetBitmap(hBmp);
	}
	else
	{
		HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_NORMAL), RT_GROUP_ICON);
		HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_NORMAL));
		SetBitmap(hBmp);
	}


	CStatic::OnMouseLeave();
}

void CIDAStarStatic::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_CLICK));
	SetBitmap(hBmp);

	CStatic::OnMouseHover(nFlags, point);
}

BOOL CIDAStarStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 使用自己的鼠标绘制函数。
	::SetCursor(::LoadCursorW(NULL, IDC_HAND));
	return TRUE;
}
