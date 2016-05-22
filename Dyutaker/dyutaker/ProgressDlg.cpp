// ProgressDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "dyutaker.h"
#include "dyutakerDlg.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"
#include "Camera.h"
#include "dp_cam.h"
#include <iostream>
using namespace std;



// CProgressDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CProgressDlg, CDialogEx)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressDlg::IDD, pParent)
{
	CdyutakerDlg* takerDlg = (CdyutakerDlg*)AfxGetMainWnd();
	cameraObj = &(takerDlg->cameraObj);

	isThreadRunning = FALSE;
	isThreadKilled = FALSE;
	progressValue = 0;
}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, progressBar);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialogEx)
//	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CProgressDlg �޽��� ó�����Դϴ�.


class PROGRESSPARAM
{
public:
	bool* isThreadRunning;
	bool* isThreadKilled;
	int* progressValue;
	CProgressCtrl* progressCtrl;
	void set(bool* isThreadRunning, bool* isThreadKilled, int* progressValue, CProgressCtrl* progressCtrl)
	{
		this->isThreadRunning = isThreadRunning;
		this->isThreadKilled = isThreadKilled;
		this->progressValue = progressValue;
		this->progressCtrl = progressCtrl;
	}
};



BOOL CProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


UINT pregressBarThread(LPVOID parameter)
{
	//�Ķ���� �ޱ�
	PROGRESSPARAM* param = (PROGRESSPARAM*)parameter;
	bool* isThreadRunning = param->isThreadRunning;
	bool* isThreadKilled = param->isThreadKilled;
	int* progressValue = param->progressValue;
	CProgressCtrl* progressCtrl = param->progressCtrl;

	while (*isThreadRunning) {

		cout << "Thread is running." << endl;
		wait(100);
		//���α׷��� ���� ������ ��� Ȯ���ϰ� ����
		progressCtrl->SetPos(*progressValue);
	}

	*isThreadKilled = TRUE;
	cout << "Thread has been killed." << endl;

	return 0;
}


void CProgressDlg::routine()
{
	// TODO: Your Code

	//���α׷����� ������ ����
	PROGRESSPARAM* parameter = new PROGRESSPARAM;
	isThreadRunning = TRUE;
	parameter->set(&isThreadRunning, &isThreadKilled, &progressValue, &progressBar);
	AfxBeginThread(pregressBarThread, parameter, 1);


	// ���α׷����� �ʱ�ȭ
	progressBar.SetRange(0, 100);
	progressBar.SetStep(10);


	// ���� ��� ����
	cout << "Getting save directory." << endl;
	progressValue = 10; 
	Sleep(0);

	CString path;
	CString szFilter = _T("mkv Files (*.mkv)|*.mkv|All Files(*.*)|*.*|");
	CFileDialog fileDialog(FALSE, NULL, NULL, NULL, szFilter);
	fileDialog.m_ofn.lpstrTitle = _T("Save");
	if (fileDialog.DoModal() == IDOK) {
		CString check = fileDialog.GetFileExt();
		if (check == "mkv") {
			path = fileDialog.GetPathName();
		}
		else {
			path = fileDialog.GetPathName() + _T(".mkv");
		}
	}
	else {
		return;
	}


	//������ mkv���Ϸ� �����ϴ� ��� �Ʒ��� ���� �������� �����մϴ�.
	//������ �����մϴ�.
	progressValue = 20;
	Sleep(0);
	cameraObj->downEvent();
	wait(500);

	progressValue = 30;
	Sleep(0);
	cameraObj->downEventCancle();
	wait(500);


	//������ disparity map video�� ��ȯ�մϴ�.�� multi-focus video�� ��ȯ�մϴ�.
	cout << "Saving disparity map video and multi-focus video." << endl;
	progressValue = 40;
	Sleep(0);

	int delayFrame = cameraObj->delayFrame;
	getDisparityMapAndMultifocusVideos("LEFT.MOV", "RIGHT.MOV", delayFrame);





	// ffmpeg.exe ���(������) ã��
	cout << "Finding current project path." << endl;
	progressValue = 80;
	Sleep(0);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	TCHAR tempPath[_MAX_PATH];
	GetModuleFileName(::AfxGetInstanceHandle(), tempPath, _MAX_PATH);
	PathRemoveFileSpec(tempPath);
	CString projectPath = _T("C:/Pofo");
	CString ffmpegPath = projectPath + _T("/ffmpeg.exe");
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	// ffmpeg.exe�� �̿��Ͽ� mkv���� ����
	cout << "ffmpeg.exe is running." << endl;
	progressValue = 90;
	Sleep(0);

	//CString command = _T("-y -i multifocus.avi -i dspMap.avi -c copy -vcodec libx264 -map 0 -map 1 ") + path;
	CString command = _T("-y -i multifocus.avi -i dspMap.avi -pix_fmt yuv420p -c copy -map 0 -map 1 ") + path;
	SHELLEXECUTEINFO ShExecInfo3 = { 0 };
	ShExecInfo3.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo3.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo3.hwnd = NULL;
	ShExecInfo3.lpVerb = _T("open");
	ShExecInfo3.lpFile = ffmpegPath;
	ShExecInfo3.lpParameters = command;
	ShExecInfo3.lpDirectory = projectPath;
	ShExecInfo3.nShow = SW_HIDE;
	ShExecInfo3.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo3);
	WaitForSingleObject(ShExecInfo3.hProcess, INFINITE);


	//������ ����
	cout << "Mkv video has been saved." << endl;
	progressValue = 100;
	Sleep(0);

	AfxMessageBox(_T("Mkv video has been saved."));
	isThreadRunning = FALSE;
	while (isThreadKilled == FALSE) {
		wait(100);
	}

	delete parameter;

	return;
}


void CProgressDlg::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialogEx::PostNcDestroy();
}


BOOL CProgressDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;
}
