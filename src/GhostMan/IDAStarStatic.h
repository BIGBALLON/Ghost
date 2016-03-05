#pragma once


// CIDAStarStatic

class CIDAStarStatic : public CStatic
{
	DECLARE_DYNAMIC(CIDAStarStatic)

public:
	CIDAStarStatic();
	virtual ~CIDAStarStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_nClicked;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


