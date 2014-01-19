
// WigglerMfcDlg.h : header file
//

#pragma once

// CWigglerMfcDlg dialog
class CWigglerMfcDlg : public CDialog
{
// Construction
public:
	CWigglerMfcDlg(CWnd* pParent = NULL);	// standard constructor
	~CWigglerMfcDlg(void);

// Dialog Data
	enum { IDD = IDD_WIGGLERMFC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	UINT_PTR m_TimerID;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();
	virtual void OnOk();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void SetUpShellNotifyIcon();
	void DeleteShellNotifyIcon();
	static void BuildWiggleDeltas();
	static POINT CreatePoint(int x, int y);

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
