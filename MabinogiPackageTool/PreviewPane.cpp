// PreviewPane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MabinogiPackageTool.h"
#include "PreviewPane.h"


// CPreviewPane

IMPLEMENT_DYNAMIC(CPreviewPane, CDockablePane)

CPreviewPane::CPreviewPane()
{

}

CPreviewPane::~CPreviewPane()
{
}


BEGIN_MESSAGE_MAP(CPreviewPane, CDockablePane)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CPreviewPane ��Ϣ�������




int CPreviewPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
