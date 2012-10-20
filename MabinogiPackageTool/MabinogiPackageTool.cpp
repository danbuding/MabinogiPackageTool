
// MabinogiPackageTool.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MabinogiPackageTool.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "MabinogiPackageToolDoc.h"
#include "LeftView.h"

#include "ProgressDialog.h"
#include "MakePackFilePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMabinogiPackageToolApp

BEGIN_MESSAGE_MAP(CMabinogiPackageToolApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMabinogiPackageToolApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_MAKE_PACK_FILE, &CMabinogiPackageToolApp::OnFileMakePackFile)
END_MESSAGE_MAP()


// CMabinogiPackageToolApp ����

CMabinogiPackageToolApp::CMabinogiPackageToolApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MabinogiPackageTool.AppID.2012"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMabinogiPackageToolApp ����

CMabinogiPackageToolApp theApp;


// CMabinogiPackageToolApp ��ʼ��

BOOL CMabinogiPackageToolApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	EnableTaskbarInteraction();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("��ɭ��"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MabinogiPackageTYPE,
		RUNTIME_CLASS(CMabinogiPackageToolDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CLeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������/��
	m_pMainWnd->DragAcceptFiles();

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// ��������Ҫ�½�һ���ĵ�
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	}

	// ���á�DDE ִ�С�
	EnableShellOpen();
	//RegisterShellFileTypes(TRUE);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CMabinogiPackageToolApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	// ɾ��֮ǰ������������ʱ�ļ�
	CFileFind finder;
	BOOL bWorking = finder.FindFile(GetMyTempPath() + GetMyTempFilePrefix() + TEXT("*.*"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		CFile::Remove(finder.GetFilePath());
	}
	return CWinAppEx::ExitInstance();
}

// CMabinogiPackageToolApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
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


// �������жԻ����Ӧ�ó�������
void CMabinogiPackageToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMabinogiPackageToolApp �Զ������/���淽��

void CMabinogiPackageToolApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	GetContextMenuManager()->AddMenu(strName + TEXT("@LeftView"), IDR_LEFT_POPUP_EDIT);

	//HMENU hMenu = GetContextMenuManager()->GetMenuById(IDR_LEFT_POPUP_EDIT);
	//::SetMenuDefaultItem(hMenu, 0, TRUE);
}

void CMabinogiPackageToolApp::LoadCustomState()
{
}

void CMabinogiPackageToolApp::SaveCustomState()
{
}

// CMabinogiPackageToolApp ��Ϣ�������
CFont * CMabinogiPackageToolApp::GetDefaultFont()
{
	return &afxGlobalData.fontRegular;
}
HBRUSH CMabinogiPackageToolApp::GetDefaultBackground()
{
	return afxGlobalData.brBtnFace;
}

CString CMabinogiPackageToolApp::GetMyTempPath(void)
{
	if (m_strTempPath.GetLength() == 0)
	{
		// ��ʵҲ����ֱ��ʹ��CString�Ļ�����
		TCHAR szTempPath[MAX_PATH + 1] = {0};
		::GetTempPath(MAX_PATH, szTempPath);
		m_strTempPath = szTempPath;
	}
	return m_strTempPath;
}


CString CMabinogiPackageToolApp::GetMyTempFilePrefix(void)
{
	if (m_strTempFilePrefix.GetLength() == 0)
	{
		m_strTempFilePrefix.Format(TEXT("mpt_tmp_%u_"), (DWORD) AfxGetInstanceHandle());
	}
	return m_strTempFilePrefix;
}

void RecursiveFindFile(CString& strPath, vector<CString> &collector)
{
	CFileFind ff;
	BOOL bFind = ff.FindFile(strPath + TEXT("\\*.*"));

	while(bFind)
	{
		bFind = ff.FindNextFile();
		if (ff.IsDots())
			continue;

		if (ff.IsDirectory())
		{
			RecursiveFindFile(ff.GetFilePath(), collector);
		}
		else
		{
			collector.push_back(ff.GetFilePath());
		}
	}
}

UINT lambda_OnFileMakePackFile(CProgressMonitor *pMonitor, LPVOID pParam)
{
	CMakePackFilePage *pPage = (CMakePackFilePage*) pParam;
			
	pMonitor->BeginTask(TEXT("����pack�ļ���") + pPage->m_strOutputFile, -1);

	// �Ȳ��ҳ����е��ļ�
	vector<CString> filePaths;
	RecursiveFindFile(pPage->m_strInputFolder, filePaths);
	int prefixLength = lstrlen(pPage->m_strInputFolder);

	PPACKOUTPUT output = pack_output(pPage->m_strOutputFile, pPage->m_ulVersion);

	for(auto iter = filePaths.begin();iter != filePaths.end();++iter)
	{
		CString& filePath = *iter;
	//for (CString& filePath : filePaths)
	//{
		pMonitor->SubTask(filePath);

		USES_CONVERSION;

		if (pMonitor->IsCanceled())
		{
			break;
		}
		s_pack_entry entry;
		CFile file(filePath, CFile::modeRead);
		CFileStatus fs;
		file.GetStatus(fs);

		SYSTEMTIME  st;  
		FILETIME  ft;

		fs.m_mtime.GetAsSystemTime(st); 
		::SystemTimeToFileTime(&st,  &ft);
		memcpy(&entry.ft[0], &ft, sizeof(FILETIME));
		memcpy(&entry.ft[1], &ft, sizeof(FILETIME));

		fs.m_ctime.GetAsSystemTime(st); 
		::SystemTimeToFileTime(&st,  &ft); 
		memcpy(&entry.ft[2], &ft, sizeof(FILETIME));
		memcpy(&entry.ft[3], &ft, sizeof(FILETIME));

		fs.m_atime.GetAsSystemTime(st); 
		::SystemTimeToFileTime(&st,  &ft); 
		memcpy(&entry.ft[4], &ft, sizeof(FILETIME));

		// ��ȫ·��ת��Ϊ���·��
		LPCTSTR lpszRelativePath = ((LPCTSTR)filePath) + prefixLength + 1;
		lstrcpyA( entry.name, CT2A(lpszRelativePath));

#pragma warning( push )
#pragma warning( disable : 4244 ) // ��ֹ����ת����ʧ�ľ���
		// д���ļ����ݣ���ʵ����ʹ���ڴ��ļ�ӳ�����Ч��
		// pack�ļ��ĸ�ʽ�������޷����뵥������4G���ļ�
		if (fs.m_size < (1024i64 * 1024 * 1024 * 4))
		{
			char *buffer = new char[fs.m_size];
			file.Read(buffer, fs.m_size);
			file.Close();

			pack_output_put_next_entry(output, &entry);
			pack_output_write(output, (byte*)buffer, fs.m_size);
			pack_output_close_entry(output);
			delete[] buffer;
		} else {
			// ������Ϣ
		}
#pragma warning( pop )
	}

	if (pMonitor->IsCanceled())
	{
		pack_output_drop(output);
	}
	else
	{
		pack_output_close(output);
	}

	return 0;
}

void CMabinogiPackageToolApp::OnFileMakePackFile()
{
	CMakePackFilePage page;
	CPropertySheet sheet(TEXT("����Pack�ļ���"), theApp.GetMainWnd());
	
	sheet.AddPage(&page);
	
	sheet.m_psh.dwFlags |= PSH_WIZARD97;
	sheet.m_psh.hInstance = AfxGetInstanceHandle();

	sheet.SetWizardMode();
	sheet.SetActivePage(&page);
	if (sheet.DoModal() ==  ID_WIZFINISH)
	{
		//CProgressDialog dlg(GetMainWnd()->GetSafeHwnd(), [](CProgressMonitor *pMonitor, LPVOID pParam) -> UINT
		//{
		//	CMakePackFilePage *pPage = (CMakePackFilePage*) pParam;
		//	
		//	pMonitor->BeginTask(TEXT("����pack�ļ���") + pPage->m_strOutputFile, -1);

		//	// �Ȳ��ҳ����е��ļ�
		//	vector<CString> filePaths;
		//	RecursiveFindFile(pPage->m_strInputFolder, filePaths);
		//	int prefixLength = lstrlen(pPage->m_strInputFolder);

		//	PPACKOUTPUT output = pack_output(pPage->m_strOutputFile, pPage->m_ulVersion);


		//	for (CString& filePath : filePaths)
		//	{
		//		pMonitor->SubTask(filePath);

		//		USES_CONVERSION;

		//		if (pMonitor->IsCanceled())
		//		{
		//			break;
		//		}
		//		s_pack_entry entry;
		//		CFile file(filePath, CFile::modeRead);
		//		CFileStatus fs;
		//		file.GetStatus(fs);

		//		SYSTEMTIME  st;  
		//		FILETIME  ft;

		//		fs.m_mtime.GetAsSystemTime(st); 
		//		::SystemTimeToFileTime(&st,  &ft);
		//		memcpy(&entry.ft[0], &ft, sizeof(FILETIME));
		//		memcpy(&entry.ft[1], &ft, sizeof(FILETIME));

		//		fs.m_ctime.GetAsSystemTime(st); 
		//		::SystemTimeToFileTime(&st,  &ft); 
		//		memcpy(&entry.ft[2], &ft, sizeof(FILETIME));
		//		memcpy(&entry.ft[3], &ft, sizeof(FILETIME));

		//		fs.m_atime.GetAsSystemTime(st); 
		//		::SystemTimeToFileTime(&st,  &ft); 
		//		memcpy(&entry.ft[4], &ft, sizeof(FILETIME));

		//		// ��ȫ·��ת��Ϊ���·��
		//		LPCTSTR lpszRelativePath = ((LPCTSTR)filePath) + prefixLength + 1;
		//		lstrcpyA( entry.name, CT2A(lpszRelativePath));

		//		
		//		// д���ļ����ݣ���ʵ����ʹ���ڴ��ļ�ӳ�����Ч��
		//		char *buffer = new char[fs.m_size];
		//		file.Read(buffer, fs.m_size);
		//		pack_output_put_next_entry(output, &entry);
		//		pack_output_write(output, (byte*)buffer, fs.m_size);
		//		pack_output_close_entry(output);
		//		free(buffer);
		//		file.Close();
		//	}

		//	if (pMonitor->IsCanceled())
		//	{
		//		pack_output_drop(output);
		//	}
		//	else
		//	{
		//		pack_output_close(output);
		//	}

		//	return 0;
		//}, &page, true);
		CProgressDialog dlg(GetMainWnd()->GetSafeHwnd(), lambda_OnFileMakePackFile,  &page, true);
		dlg.DoModal();
	}

	//CFolderPickerDialog fdlg(TEXT("ѡ��һ��"));

	//CProgressDialog dlg(GetMainWnd()->GetSafeHwnd(), [](CProgressMonitor *pMonitor, LPVOID pParam) -> UINT{
	//	pMonitor->BeginTask(TEXT("��ʼһ������"), 100);
	//	for (int i = 0; i < 100; i++)
	//	{
	//		if (pMonitor->IsCanceled())
	//		{
	//			break;
	//		}
	//		CString tmp;
	//		tmp.Format(TEXT("- %d -"), i );
	//		pMonitor->SubTask(tmp);
	//		pMonitor->Worked(1);
	//		//pMonitor->Done();
	//		Sleep(50);
	//	}

	//	Sleep(1000);
	//	return 0;
	//}, NULL, false);

	//dlg.DoModal();
}