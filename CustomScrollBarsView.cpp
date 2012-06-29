// CustomScrollBarsView.cpp : implementation of the CCustomScrollBarsView class
//

#include "stdafx.h"
#include "CustomScrollBars.h"

#include "CustomScrollBarsDoc.h"
#include "CustomScrollBarsView.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsView

IMPLEMENT_DYNCREATE(CCustomScrollBarsView, CScrollView)

BEGIN_MESSAGE_MAP(CCustomScrollBarsView, CScrollView)
	//{{AFX_MSG_MAP(CCustomScrollBarsView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsView construction/destruction

CCustomScrollBarsView::CCustomScrollBarsView()
{

}

CCustomScrollBarsView::~CCustomScrollBarsView()
{
}

BOOL CCustomScrollBarsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsView drawing

void CCustomScrollBarsView::OnDraw(CDC* pDC)
{
	CCustomScrollBarsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if (pDoc->m_pPicture != NULL)
	{
		// get palette
		HPALETTE hPal;
		pDoc->m_pPicture->get_hPal(reinterpret_cast<OLE_HANDLE *>(&hPal));

		CPalette *pPalOld = NULL;
		if (hPal != NULL)
		{
			TRACE(_T("CCustomScrollBarsView::OnDraw - RealizePalette\n"));
			pPalOld = pDC->SelectPalette(CPalette::FromHandle(hPal), FALSE);
			pDC->RealizePalette();
		}

		// transparent?
		DWORD dwAttr;
		if (FAILED(pDoc->m_pPicture->get_Attributes(&dwAttr)) ||
			(dwAttr & PICTURE_TRANSPARENT))
		{
			TRACE(_T("CCustomScrollBarsView::OnDraw - Transparent\n"));

			// use an off-screen DC to prevent flickering
			CDC MemDC;
			MemDC.CreateCompatibleDC(pDC);
			CBitmap Bmp;
			Bmp.CreateCompatibleBitmap(pDC,
									   pDoc->m_sizeInPix.cx,
									   pDoc->m_sizeInPix.cy);



			CBitmap *pBmpOld = MemDC.SelectObject(&Bmp);
			CPalette *pPalMemOld = NULL;
			if (hPal != NULL)
			{
				pPalMemOld = MemDC.SelectPalette(CPalette::FromHandle(hPal), FALSE);
				MemDC.RealizePalette();
			}

			RECT rc = { 0, 0, pDoc->m_sizeInPix.cx, pDoc->m_sizeInPix.cy };

			MemDC.FillSolidRect(&rc, ::GetSysColor(COLOR_WINDOW));

			// display picture using IPicture::Render
			pDoc->m_pPicture->Render(MemDC.GetSafeHdc(),
									 0,
									 0,
									 pDoc->m_sizeInPix.cx,
									 pDoc->m_sizeInPix.cy,
									 0,
									 pDoc->m_sizeInHiMetric.cy,
									 pDoc->m_sizeInHiMetric.cx,
									 -pDoc->m_sizeInHiMetric.cy,
									 &rc);

			pDC->BitBlt(0, 0, pDoc->m_sizeInPix.cx, pDoc->m_sizeInPix.cy,
						&MemDC, 0, 0, SRCCOPY);

			MemDC.SelectObject(pBmpOld);

			if (pPalMemOld != NULL)
			{
				ASSERT(hPal != NULL);
				MemDC.SelectPalette(pPalMemOld, FALSE);
			}
		}
		else
		{
			RECT rc;
			this->GetClientRect(&rc);
			// display picture using IPicture::Render
			pDoc->m_pPicture->Render(pDC->GetSafeHdc(),
									 0,
									 0,
									 pDoc->m_sizeInPix.cx,
									 pDoc->m_sizeInPix.cy,
									 0,
									 pDoc->m_sizeInHiMetric.cy,
									 pDoc->m_sizeInHiMetric.cx,
									 -pDoc->m_sizeInHiMetric.cy,
									 &rc);
		}

		if (pPalOld != NULL)
		{
			ASSERT(hPal != NULL);
			pDC->SelectPalette(pPalOld, FALSE);
		}
	}
}

void CCustomScrollBarsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsView printing

BOOL CCustomScrollBarsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCustomScrollBarsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCustomScrollBarsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsView diagnostics

#ifdef _DEBUG
void CCustomScrollBarsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCustomScrollBarsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCustomScrollBarsDoc* CCustomScrollBarsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomScrollBarsDoc)));
	return (CCustomScrollBarsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsView message handlers

CScrollBar* CCustomScrollBarsView::GetScrollBarCtrl(int nBar) const
{
	CWnd* pParent = GetParent();
	UINT nID = AFX_IDW_HSCROLL_FIRST;
	if (nBar==SB_VERT)
	    nID++;
	return (CScrollBar*)pParent->GetDlgItem(nID);

}


BOOL CCustomScrollBarsView::OnEraseBkgnd(CDC* pDC) 
{
	CBrush br(::GetSysColor(COLOR_WINDOW));
    this->FillOutsideRect(pDC, &br);

	return TRUE;	
	return CScrollView::OnEraseBkgnd(pDC);
}

void CCustomScrollBarsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CScrollView::OnUpdate(pSender, lHint, pHint);

	CCustomScrollBarsDoc *pDoc = this->GetDocument();
	ASSERT_VALID(pDoc);

	this->SetScrollSizes(MM_TEXT,
						 pDoc->m_pPicture != NULL
						 ? CSize(pDoc->m_sizeInPix.cx, pDoc->m_sizeInPix.cy)
						 : CSize(0, 0));

	#ifdef _DEBUG
		pDoc->Dump(afxDump);
	#endif //_DEBUG	
	
}

void CCustomScrollBarsView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnPrepareDC(pDC, pInfo);

	if (pDC->IsPrinting())
	{
		// Set the mapping mode so that the image is printed at the same
		// size as on the screen. Note that images may be too large to be
		// printed completely.
		CDC ScreenDC;
		ScreenDC.CreateIC(_T("DISPLAY"), NULL, NULL, NULL);
		pDC->SetMapMode(MM_ANISOTROPIC);
		pDC->SetWindowExt(ScreenDC.GetDeviceCaps(LOGPIXELSX),
						  ScreenDC.GetDeviceCaps(LOGPIXELSY));
		pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
							pDC->GetDeviceCaps(LOGPIXELSY));
		pDC->SetWindowOrg(0, 0);
		pDC->SetViewportOrg(0, 0);
	}
}
