// MakePackFilePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MabinogiPackageTool.h"
#include "MakePackFilePage.h"
#include "afxdialogex.h"


// CMakePackFilePage �Ի���

IMPLEMENT_DYNAMIC(CMakePackFilePage, CPropertyPage)

CMakePackFilePage::CMakePackFilePage()
	: CPropertyPage(CMakePackFilePage::IDD)
	, m_strInputFolder(_T(""))
	, m_strOutputFile(_T(""))
	, m_nVersion(100)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
    m_psp.pszHeaderTitle = _T("����Pack�ļ�");
    m_psp.pszHeaderSubTitle = _T("����ָ��һ���汾���ļ������ڴ���һ��Pack�ļ���ע��ѡ�е��ļ��н���ΪPack�ļ��е�Data���ļ��С�");

}

CMakePackFilePage::~CMakePackFilePage()
{
}

void CMakePackFilePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT_FOLDER, m_strInputFolder);
	DDX_Text(pDX, IDC_OUTPUT_FILE, m_strOutputFile);
	DDX_Text(pDX, IDC_VERSION, m_nVersion);
	DDX_Control(pDX, IDC_VERSION_SPIN, m_spinVersion);
}


BEGIN_MESSAGE_MAP(CMakePackFilePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BROWSER_INPUT, &CMakePackFilePage::OnClickedBrowserInput)
	ON_BN_CLICKED(IDC_BROWSER_OUTPUT, &CMakePackFilePage::OnClickedBrowserOutput)
END_MESSAGE_MAP()


// CMakePackFilePage ��Ϣ�������


BOOL CMakePackFilePage::OnSetActive()
{
	GetParentSheet()->SetWizardButtons(PSWIZB_FINISH);
	return CPropertyPage::OnSetActive();
}


void CMakePackFilePage::OnClickedBrowserInput()
{
	CFolderPickerDialog dlg(TEXT("ѡ�����ļ���"), 0, this);
	if (dlg.DoModal() == IDOK)
	{
		m_strInputFolder = dlg.GetPathName();
		UpdateData(FALSE);
	}
}


void CMakePackFilePage::OnClickedBrowserOutput()
{
	CFileDialog dlg(FALSE, TEXT("pack"), 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		TEXT("Mabinogi Resources Files (*.pack)|*.pack||"), this);
	if (dlg.DoModal() == IDOK)
	{
		m_strOutputFile = dlg.GetPathName();
		UpdateData(FALSE);
	}
}
