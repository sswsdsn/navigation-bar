// CustomScrollBarsView.h : interface of the CCustomScrollBarsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMSCROLLBARSVIEW_H__F7511DAB_16A0_4F72_AA27_B1730B9C4EFC__INCLUDED_)
#define AFX_CUSTOMSCROLLBARSVIEW_H__F7511DAB_16A0_4F72_AA27_B1730B9C4EFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomScrollBarsView : public CScrollView
{
protected: // create from serialization only
	CCustomScrollBarsView();
	DECLARE_DYNCREATE(CCustomScrollBarsView)

// Attributes
public:
	CCustomScrollBarsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomScrollBarsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomScrollBarsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomScrollBarsView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CustomScrollBarsView.cpp
inline CCustomScrollBarsDoc* CCustomScrollBarsView::GetDocument()
   { return (CCustomScrollBarsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMSCROLLBARSVIEW_H__F7511DAB_16A0_4F72_AA27_B1730B9C4EFC__INCLUDED_)
