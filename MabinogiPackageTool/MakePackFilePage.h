#pragma once
#include "afxcmn.h"


// CMakePackFilePage �Ի���

class CMakePackFilePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CMakePackFilePage)

public:
	CMakePackFilePage();
	virtual ~CMakePackFilePage();

// �Ի�������
	enum { IDD = IDD_MAKEPACKFILEPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
public:
	CString m_strInputFolder;
	CString m_strOutputFile;
	unsigned long m_ulVersion;
//	CSpinButtonCtrl m_spinVersion;
public:
	afx_msg void OnClickedBrowserInput();
	afx_msg void OnClickedBrowserOutput();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnInitDialog();
};
