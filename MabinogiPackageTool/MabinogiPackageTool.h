
// MabinogiPackageTool.h : MabinogiPackageTool Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMabinogiPackageToolApp:
// �йش����ʵ�֣������ MabinogiPackageTool.cpp
//

class CMabinogiPackageToolApp : public CWinAppEx
{
public:
	CMabinogiPackageToolApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	CFont * GetDefaultFont();
	HBRUSH GetDefaultBackground();
	CString GetMyTempPath(void);
	CString GetMyTempFilePrefix(void);

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
private:
	CString m_strTempPath;
	CString m_strTempFilePrefix;
	
public:
	afx_msg void OnFileMakePackFile();
};

extern CMabinogiPackageToolApp theApp;
