// TestHfDlg.h : header file
//

#if !defined(AFX_TESTHFDLG_H__EED551FE_D8EF_470E_AA9C_2B77125059F7__INCLUDED_)
#define AFX_TESTHFDLG_H__EED551FE_D8EF_470E_AA9C_2B77125059F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestHfDlg dialog

class CTestHfDlg : public CDialog
{
// Construction
public:
	CTestHfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestHfDlg)
	enum { IDD = IDD_TESTHF_DIALOG };
	CSliderCtrl	m_Slider2;
	CSliderCtrl	m_Slider1;
	CString	m_Block;
	CString	m_w;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestHfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestHfDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTHFDLG_H__EED551FE_D8EF_470E_AA9C_2B77125059F7__INCLUDED_)
