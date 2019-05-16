// TestHf.h : main header file for the TESTHF application
//

#if !defined(AFX_TESTHF_H__D60D8698_D097_4B6B_AB3E_22D037F57CF5__INCLUDED_)
#define AFX_TESTHF_H__D60D8698_D097_4B6B_AB3E_22D037F57CF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestHfApp:
// See TestHf.cpp for the implementation of this class
//

class CTestHfApp : public CWinApp
{
public:
	CTestHfApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestHfApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestHfApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTHF_H__D60D8698_D097_4B6B_AB3E_22D037F57CF5__INCLUDED_)
