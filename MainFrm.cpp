// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CustomScrollBars.h"

#include "MainFrm.h"
#include "CustomScrollBarsDoc.h"
#include "CustomScrollBarsView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

//habeeb
	CRect rc(0,0,0,0);
	VERIFY(myHScroll.Create(WS_VISIBLE|WS_CHILD|SBS_HORZ,
	    rc, this, AFX_IDW_HSCROLL_FIRST));
	VERIFY(myVScroll.Create(WS_VISIBLE|WS_CHILD|SBS_VERT,
		rc, this, AFX_IDW_HSCROLL_FIRST+1));
	VERIFY(m_cuteBox.Create(WS_VISIBLE|WS_CHILD|SBS_SIZEBOX,
		rc, this,-1));
	m_brColor.CreateSolidBrush(RGB(0,255,0));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

void CMainFrame::RecalcLayout(BOOL bNotify) 
{
    CFrameWnd::RecalcLayout();
    CCustomScrollBarsView* pView = (CCustomScrollBarsView*)GetActiveView();
    if (pView) {
        CRect rect;
        pView->GetWindowRect(&rect);
        ScreenToClient(&rect);

        // shrink view by scrollbars
        int cyHScroll = GetSystemMetrics(SM_CYHSCROLL);
        int cxVScroll = GetSystemMetrics(SM_CXVSCROLL);
        rect.right  -= cxVScroll;
        rect.bottom -= cyHScroll;
        pView->MoveWindow(rect);

        // next, move the scroll bars: horz, vert and box
        rect.left   = rect.right;
        rect.right += cxVScroll;
        myVScroll.MoveWindow(rect);

        rect.left   = 0;
        rect.right -= cxVScroll;
        rect.top    = rect.bottom;
        rect.bottom+= cyHScroll;
        myHScroll.MoveWindow(rect);

        rect.left = rect.right;
        rect.right+=cxVScroll;
        m_cuteBox.MoveWindow(rect);
    }
}

HBRUSH CMainFrame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (nCtlColor==CTLCOLOR_SCROLLBAR) {
		return m_brColor;
	}
	return CFrameWnd::OnCtlColor(pDC, pWnd, nCtlColor);
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	TRACE(_T("CMainFrame::OnQueryNewPalette\n"));

	this->Invalidate();
	
	return TRUE;
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CFrameWnd::OnPaletteChanged(pFocusWnd);
	
	TRACE(_T("CMainFrame::OnPaletteChanged\n"));

	if (pFocusWnd != this && !this->IsChild(pFocusWnd))
        this->Invalidate();
}
