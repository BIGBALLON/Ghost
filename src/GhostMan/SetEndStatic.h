#pragma once


// CSetEndStatic

class CSetEndStatic : public CStatic
{
	DECLARE_DYNAMIC(CSetEndStatic)

public:
	CSetEndStatic();
	virtual ~CSetEndStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	int m_nClicked;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


