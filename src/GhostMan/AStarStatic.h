#pragma once


// CAStarStatic

class CAStarStatic : public CStatic
{
	DECLARE_DYNAMIC(CAStarStatic)

public:
	CAStarStatic();
	virtual ~CAStarStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	int m_nClicked;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


