// CustomScrollBarsDoc.h : interface of the CCustomScrollBarsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMSCROLLBARSDOC_H__E00932A0_03C0_4E5E_A9CF_7D303543E891__INCLUDED_)
#define AFX_CUSTOMSCROLLBARSDOC_H__E00932A0_03C0_4E5E_A9CF_7D303543E891__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomScrollBarsDoc : public CDocument
{
protected: // create from serialization only
	CCustomScrollBarsDoc();
	DECLARE_DYNCREATE(CCustomScrollBarsDoc)

// Attributes
public:
	SIZE m_sizeInPix;
	SIZE m_sizeInHiMetric;
	LPPICTURE m_pPicture;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomScrollBarsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomScrollBarsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomScrollBarsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMSCROLLBARSDOC_H__E00932A0_03C0_4E5E_A9CF_7D303543E891__INCLUDED_)
