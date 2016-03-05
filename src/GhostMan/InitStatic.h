#pragma once


// CInitStatic

class CInitStatic : public CStatic
{
	DECLARE_DYNAMIC(CInitStatic)

public:
	CInitStatic();
	virtual ~CInitStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


