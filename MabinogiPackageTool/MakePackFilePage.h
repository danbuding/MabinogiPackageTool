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
private:
	CString m_strInputFolder;
	CString m_strOutputFile;
	int m_nVersion;
	CSpinButtonCtrl m_spinVersion;
public:
	afx_msg void OnClickedBrowserInput();
	afx_msg void OnClickedBrowserOutput();
};
