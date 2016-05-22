#pragma once
#include "afxcmn.h"


// CProgressDlg ��ȭ �����Դϴ�.

class CProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	CProgressDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CProgressDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROGRESS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl progressBar;
	Camera* cameraObj;
	bool isThreadRunning;
	int progressValue;
	virtual BOOL OnInitDialog();
	void routine();
	virtual void PostNcDestroy();
	bool isThreadKilled;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

UINT pregressBarThread(LPVOID parameter);