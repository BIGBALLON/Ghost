#pragma once


// CBFSStatic

class CBFSStatic : public CStatic
{
	DECLARE_DYNAMIC(CBFSStatic)

public:
	CBFSStatic();
	virtual ~CBFSStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	int m_nClicked;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


