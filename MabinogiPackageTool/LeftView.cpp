
// LeftView.cpp : CLeftView ���ʵ��
//

#include "stdafx.h"
#include "MabinogiPackageTool.h"

#include "MabinogiPackageToolDoc.h"
#include "LeftView.h"

#include <Uxtheme.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
END_MESSAGE_MAP()


// CLeftView ����/����

CLeftView::CLeftView()
{
	// TODO: �ڴ˴���ӹ������
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= TVS_HASBUTTONS | LVS_SHAREIMAGELISTS | TVS_LINESATROOT;
	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	SHFILEINFO ssfi;
	::SetWindowTheme(GetTreeCtrl().GetSafeHwnd(), L"Explorer", 0);

	TCHAR szCurDir [MAX_PATH + 1];
	if (GetCurrentDirectory(MAX_PATH, szCurDir) > 0)
	{
		SHFILEINFO sfi;
		GetTreeCtrl().SetImageList(CImageList::FromHandle((HIMAGELIST) SHGetFileInfo(
			szCurDir, 0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON)), 0);
	}

    if ( !SHGetFileInfo( szCurDir,
                        0,
                        &ssfi,
                        sizeof( SHFILEINFO ),
                        SHGFI_ICON | 
                        SHGFI_SMALLICON ) )
    {
        
    }

	m_iIconFolder = ssfi.iIcon;

    // we only need the index from the system image list
    DestroyIcon( ssfi.hIcon );

    if ( !SHGetFileInfo( szCurDir,
                        0,
                        &ssfi,
                        sizeof( SHFILEINFO ),
                        SHGFI_ICON | SHGFI_OPENICON |
                        SHGFI_SMALLICON ) )
    {

    }

	m_iIconFolderOpen = ssfi.iIcon;

    // we only need the index of the system image list

    DestroyIcon( ssfi.hIcon );

	shared_ptr<CPackFolder> m_spRoot = GetDocument()->GetRoot();
	if (m_spRoot.get())
	{
		InsertItem( TVI_ROOT, m_spRoot);
	}

}

void CLeftView::InsertItem( HTREEITEM hParentItem, shared_ptr<CPackFolder> spFolder )
{
	HTREEITEM hItem = GetTreeCtrl().InsertItem(spFolder->m_strName, hParentItem);
	GetTreeCtrl().SetItemImage(hItem, m_iIconFolder, m_iIconFolderOpen);
	GetTreeCtrl().SetItemData(hItem, (DWORD_PTR)spFolder.get());
	for (size_t i = 0; i < spFolder->m_children.size();i++)
	{
		InsertItem(hItem, spFolder->m_children.at(i));
	}
}
// CLeftView ���

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMabinogiPackageToolDoc* CLeftView::GetDocument() // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMabinogiPackageToolDoc)));
	return (CMabinogiPackageToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView ��Ϣ�������
