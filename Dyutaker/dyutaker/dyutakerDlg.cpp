
// dyutakerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "dyutaker.h"
#include "dyutakerDlg.h"
#include "afxdialogex.h"
#include "dp_cam.h"
#include "ProgressDlg.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class THREADPARAM
{
	Camera* camera;
	bool* bThreadContitnue;
	bool* bThreadIsKilled;
public:
	THREADPARAM();
	Camera* getCameraHandle();
	bool* getThreadContinueFlag();
	bool* getThreadKilledFlag();
};
THREADPARAM::THREADPARAM()
{
	CdyutakerApp* app = (CdyutakerApp*)AfxGetApp();
	CdyutakerDlg* pDlg = (CdyutakerDlg*)(app->m_pMainWnd);

	camera = &(pDlg->cameraObj);

	bThreadContitnue = &(pDlg->bThreadContinue);
	bThreadIsKilled = &(pDlg->bThreadIsKilled);
}
Camera* THREADPARAM::getCameraHandle()
{
	return this->camera;
}
bool* THREADPARAM::getThreadContinueFlag()
{
	return this->bThreadContitnue;
}
bool* THREADPARAM::getThreadKilledFlag()
{
	return this->bThreadIsKilled;
}
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//���Ϻи��ϰ�ʹ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdyutakerDlg ��ȭ ����



CdyutakerDlg::CdyutakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdyutakerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdyutakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAMERA_VALIDAITION, m_validationButton);
	DDX_Control(pDX, IDC_SHOOT, m_shootButton);
	DDX_Control(pDX, IDC_STOP, m_stopButton);
}

BEGIN_MESSAGE_MAP(CdyutakerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CAMERA_VALIDAITION, &CdyutakerDlg::OnBnClickedCameraValidaition)
	ON_BN_CLICKED(IDC_SHOOT, &CdyutakerDlg::OnBnClickedShoot)
	ON_BN_CLICKED(IDC_STOP, &CdyutakerDlg::OnBnClickedStop)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_QUIT_PROGRAM, &CdyutakerDlg::OnBnClickedExitProgram)
//	ON_WM_CTLCOLOR()
//ON_WM_DRAWITEM()
//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CdyutakerDlg �޽��� ó����

BOOL CdyutakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_quit_button.Attach(((CBitmapButton *)GetDlgItem(IDC_QUIT_PROGRAM))->m_hWnd);
	m_quit_button.LoadBitmaps(IDB_QUIT, IDB_QUIT, NULL, NULL);
	m_quit_button.SizeToContent();

	m_validationButton.Attach(((CBitmapButton *)GetDlgItem(IDC_CAMERA_VALIDAITION))->m_hWnd);
	m_validationButton.LoadBitmaps(IDB_CONNECT_VISIBLE, IDB_CONNECT_CLICK, NULL, IDB_CONNECT_DISABLED);
	m_validationButton.SizeToContent();

	m_shootButton.Attach(((CBitmapButton *)GetDlgItem(IDC_SHOOT))->m_hWnd);
	m_shootButton.LoadBitmaps(IDB_SHOOT_VISIBLE, IDB_SHOOT_CLICK, NULL, IDB_SHOOT_DISABLED);
	m_shootButton.SizeToContent();

	m_stopButton.Attach(((CBitmapButton *)GetDlgItem(IDC_STOP))->m_hWnd);
	m_stopButton.LoadBitmaps(IDB_STOP_VISIBLE, IDB_STOP_CLICK, NULL, IDB_STOP_DISABLED);
	m_stopButton.SizeToContent();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CdyutakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CdyutakerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CdyutakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CdyutakerDlg::OnBnClickedCameraValidaition()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_validationButton.EnableWindow(FALSE);

	if (cameraObj.edsdkInit()) {
		AfxMessageBox(_T("EDSDK�� ����� �������� ���߽��ϴ�."));
	}
	else {
		if (cameraObj.cameraSetup()) {
			AfxMessageBox(_T("ī�޶� ������ Ȯ���ϼ���"));
		}
		else {
			cameraObj.checkLeft();
			wait(1000);
			cameraObj.liveViewSetup();
			// ��ư Ȱ��ȭ
			m_shootButton.EnableWindow(TRUE);
		}
	}

	m_validationButton.EnableWindow(TRUE);
}


void CdyutakerDlg::OnBnClickedShoot()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// shoot ��ư�� Ȱ��ȭ��ư�� ��Ȱ��ȭ �ϰ� stop��ư�� Ȱ��ȭ�մϴ�.
	m_validationButton.EnableWindow(FALSE);
	m_shootButton.EnableWindow(FALSE);
	bThreadContinue = TRUE;
	bThreadIsKilled = FALSE;
	// ���� �Կ��� �����մϴ�.
	cameraObj.recordStart();
	// ���� �Կ� ������ ���� 
	THREADPARAM* pParams = new THREADPARAM;
	AfxBeginThread(getFrameThread, pParams);

	m_stopButton.EnableWindow(TRUE);
}


void CdyutakerDlg::OnBnClickedStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ���� �Կ� ������ �����մϴ�.
	m_stopButton.EnableWindow(FALSE);
	bThreadContinue = FALSE;

	while (bThreadIsKilled == FALSE){
		wait(100);
	}
	cameraObj.recordStop();

	// ������ ������ �� Ȯ���մϴ�.
 	if (AfxMessageBox(_T("Do you want to save video?"), MB_YESNO) == IDYES) {
		CProgressDlg* progressDlg = new CProgressDlg;
		progressDlg->Create(CProgressDlg::IDD);
		progressDlg->ShowWindow(SW_SHOW);
		progressDlg->routine();

		progressDlg->DestroyWindow();
		delete progressDlg;
		
		cameraObj.liveViewSetup();
		m_shootButton.EnableWindow(TRUE);
		m_validationButton.EnableWindow(TRUE);
	}
	else {
		wait(500);
		cameraObj.downEventCancle();
		cameraObj.liveViewSetup();
		m_shootButton.EnableWindow(TRUE);
		m_validationButton.EnableWindow(TRUE);
	}
}

UINT getFrameThread(LPVOID pParam)
{
	THREADPARAM* pParams = (THREADPARAM*)pParam;
	Camera* camera = pParams->getCameraHandle();

	bool* bThreadContinue = pParams->getThreadContinueFlag();
	bool* bThreadIsKilled = pParams->getThreadKilledFlag();
	delete pParams;

	while (*bThreadContinue) {
		(*camera).liveViewAll();

		std::cout << "Thread is running!" << endl;
	}

	(*bThreadIsKilled) = TRUE;
	std::cout << "Thread is stopped." << endl;
	return 0;
}


void wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

BOOL CdyutakerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// ���̾�α� ��� �� �ٲٱ�
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;
}


void CdyutakerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// ���̾�α� ������ �����Ͽ� â �����̱�
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CDialog::OnLButtonDown(nFlags, point);
}


BOOL CdyutakerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	// ESC ���� ����
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}


void CdyutakerDlg::OnBnClickedExitProgram()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnDestroy(); 
	OnOK();
}