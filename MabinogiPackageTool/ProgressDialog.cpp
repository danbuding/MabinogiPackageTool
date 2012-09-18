// ProgressWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MabinogiPackageTool.h"
#include "ProgressDialog.h"

CProgressMonitor::CProgressMonitor()
{
}

CProgressMonitor::~CProgressMonitor()
{
}

// CProgressWnd

IMPLEMENT_DYNAMIC(CProgressDialog, CWnd)

CProgressDialog::CProgressDialog(CWnd *pParentWnd, CRunnable *runnable)
{
	Create(pParentWnd, TEXT("����"));
	m_pRunnable = runnable;
}

CProgressDialog::~CProgressDialog()
{
}


BEGIN_MESSAGE_MAP(CProgressDialog, CWnd)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

struct SThreadParamter
{
	CRunnable *pRunnable;
	CProgressMonitor *pMonitor;
};
UINT RunnableThreadFuc(LPVOID pParam)
{
	SThreadParamter *p = (SThreadParamter*) pParam;
	Sleep(100);
	return 0;
}
// CProgressWnd ��Ϣ�������


BOOL CProgressDialog::Create(CWnd* pParent, LPCTSTR pszTitle)
{
	CString csClassName = AfxRegisterWndClass(CS_OWNDC|CS_HREDRAW|CS_VREDRAW,
                                              ::LoadCursor(NULL, IDC_APPSTARTING),
                                              CBrush(::GetSysColor(COLOR_BTNFACE)));

	BOOL bSuccess = CreateEx(WS_EX_DLGMODALFRAME, // Extended style
                        csClassName,                       // Classname
                        pszTitle,                          // Title
						WS_BORDER|WS_CAPTION|WS_POPUPWINDOW,     // style
                        0,0,                               // position - updated soon.
                        390,130,                           // Size - updated soon
                        pParent->GetSafeHwnd(),            // handle to parent
                        0,                                 // No menu
                        NULL);    
    if (!bSuccess) 
		return FALSE;

	return TRUE;
}

int CProgressDialog::DoModal(void)
{
	GetParent()->EnableWindow(FALSE);
	EnableWindow(TRUE);

	CenterWindow();
	ShowWindow(SW_SHOW);

	// �����߳�
	SThreadParamter param;
	param.pRunnable = m_pRunnable;
	param.pMonitor = NULL;
	CWinThread *pThread = AfxBeginThread(RunnableThreadFuc, (LPVOID)&param);

	// ������Ϣѭ��
	DWORD dwRet;
	GetExitCodeThread(pThread->m_hThread, &dwRet);
	while (dwRet == STILL_ACTIVE) 
	{
		Sleep(1);
		if (!AfxGetApp()->PumpMessage()) 
		{
			::PostQuitMessage(0);
			return 0;
		}
		GetExitCodeThread(pThread->m_hThread, &dwRet);
	}

	CloseWindow();

	return 0;
}


void CProgressDialog::OnClose()
{
	GetParent()->EnableWindow(TRUE);
	CWnd::OnClose();
}
