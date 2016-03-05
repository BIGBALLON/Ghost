#pragma once


// CACOStatic

class CACOStatic : public CStatic
{
	DECLARE_DYNAMIC(CACOStatic)

public:
	CACOStatic();
	virtual ~CACOStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_nClicked;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


