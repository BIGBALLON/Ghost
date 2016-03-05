#pragma once


// CCloseStatic

class CCloseStatic : public CStatic
{
	DECLARE_DYNAMIC(CCloseStatic)

public:
	CCloseStatic();
	virtual ~CCloseStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


