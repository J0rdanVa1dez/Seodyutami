
// dyutakerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "Camera.h"

//static Camera cameraObj[2];

// CdyutakerDlg ��ȭ ����
class CdyutakerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CdyutakerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DYUTAKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCameraValidaition();
	afx_msg void OnBnClickedShoot();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedButton1();
	CBitmapButton m_validationButton;
	CBitmapButton m_shootButton;
	CBitmapButton m_stopButton;
	CBitmapButton m_quit_button;
	Camera cameraObj;
	bool bThreadContinue;
	bool bThreadIsKilled;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedExitProgram();
};

UINT getFrameThread(LPVOID pParam);
void wait(DWORD dwMillisecond);