// CustomScrollBarsDoc.cpp : implementation of the CCustomScrollBarsDoc class
//

#include "stdafx.h"
#include "CustomScrollBars.h"
#include <afxpriv.h>
#include "CustomScrollBarsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsDoc

IMPLEMENT_DYNCREATE(CCustomScrollBarsDoc, CDocument)

BEGIN_MESSAGE_MAP(CCustomScrollBarsDoc, CDocument)
	//{{AFX_MSG_MAP(CCustomScrollBarsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsDoc construction/destruction

CCustomScrollBarsDoc::CCustomScrollBarsDoc()
{
	m_pPicture = NULL;

}

CCustomScrollBarsDoc::~CCustomScrollBarsDoc()
{
	if (m_pPicture != NULL)
	{
		m_pPicture->Release();
		m_pPicture = NULL;

		TRACE(_T("CImgViewerDoc::~CImgViewerDoc - m_pPicture->Release()\n"));
	}

}

BOOL CCustomScrollBarsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsDoc serialization

void CCustomScrollBarsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsDoc diagnostics

#ifdef _DEBUG
void CCustomScrollBarsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCustomScrollBarsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
	dc << _T("m_pPicture = ") << m_pPicture << _T("\n");
	dc << _T("m_sizeInHiMetric = ") << m_sizeInHiMetric << _T("\n");
	dc << _T("m_sizeInPix = ") << m_sizeInPix << _T("\n");
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomScrollBarsDoc commands

BOOL CCustomScrollBarsDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	this->DeleteContents();

	// The previous image should be unloaded.
	ASSERT(m_pPicture == NULL);

	USES_CONVERSION;
	HRESULT hr = ::OleLoadPicturePath(const_cast<LPOLESTR>(T2COLE(lpszPathName)),
									  NULL,
									  0,
									  0,
									  IID_IPicture,
									  reinterpret_cast<LPVOID *>(&m_pPicture));
	
	TRACE(_T("CImgViewerDoc::OnOpenDocument - OleLoadPicturePath(\"%s\"): ")
		  _T("hr = 0x%08X, m_pPicture = 0x%08X\n"), lpszPathName, hr, m_pPicture);
	
	if (SUCCEEDED(hr) && m_pPicture != NULL)
	{
		// get width and height of picture
		m_pPicture->get_Width(&m_sizeInHiMetric.cx);
		m_pPicture->get_Height(&m_sizeInHiMetric.cy);

		const int HIMETRIC_PER_INCH = 2540;

		HDC hDCScreen = ::GetDC(NULL);
		ASSERT(hDCScreen != NULL);
		// Pixels per logical inch along width
		const int nPixelsPerInchX = ::GetDeviceCaps(hDCScreen, LOGPIXELSX);
		// Pixels per logical inch along height
		const int nPixelsPerInchY = ::GetDeviceCaps(hDCScreen, LOGPIXELSY);
		::ReleaseDC(NULL, hDCScreen);

		// convert himetric to pixels
		m_sizeInPix.cx = (nPixelsPerInchX * m_sizeInHiMetric.cx +
						  HIMETRIC_PER_INCH / 2) / HIMETRIC_PER_INCH;
		m_sizeInPix.cy = (nPixelsPerInchY * m_sizeInHiMetric.cy +
						  HIMETRIC_PER_INCH / 2) / HIMETRIC_PER_INCH;

		return TRUE;
	}
	else
	{
		// OleLoadPicturePath failed.
		CString strErrMsg;
		strErrMsg.Format("Could read the image file.\nNot a valid image, or the format, not supported");
		::AfxMessageBox(strErrMsg, MB_OK | MB_ICONEXCLAMATION);

		// Back to initial state
		this->OnNewDocument();
		this->GetDocTemplate()->SetDefaultTitle(this);
		this->UpdateAllViews(NULL);

		ASSERT(m_pPicture == NULL);
		ASSERT(this->GetPathName().IsEmpty());

		return FALSE;
	}
}

void CCustomScrollBarsDoc::DeleteContents() 
{
	if (m_pPicture != NULL)
	{
		m_pPicture->Release();
		m_pPicture = NULL;

		TRACE(_T("CCustomScrollBarsDoc::DeleteContents - m_pPicture->Release()\n"));
	}
	
	CDocument::DeleteContents();
}
