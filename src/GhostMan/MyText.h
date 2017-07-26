#pragma once


// CMyText

class CMyText : public CStatic
{
	DECLARE_DYNAMIC(CMyText)

public:
	CMyText();
	virtual ~CMyText();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


