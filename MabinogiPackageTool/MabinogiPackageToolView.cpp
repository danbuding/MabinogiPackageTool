
// MabinogiPackageToolView.cpp : CMabinogiPackageToolView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MabinogiPackageTool.h"
#endif

#include "MabinogiPackageToolDoc.h"
#include "MabinogiPackageToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMabinogiPackageToolView

IMPLEMENT_DYNCREATE(CMabinogiPackageToolView, CListView)

BEGIN_MESSAGE_MAP(CMabinogiPackageToolView, CListView)
	ON_WM_STYLECHANGED()
END_MESSAGE_MAP()

// CMabinogiPackageToolView ����/����

CMabinogiPackageToolView::CMabinogiPackageToolView()
{
	// TODO: �ڴ˴���ӹ������

}

CMabinogiPackageToolView::~CMabinogiPackageToolView()
{
}

BOOL CMabinogiPackageToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

void CMabinogiPackageToolView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
}


// CMabinogiPackageToolView ���

#ifdef _DEBUG
void CMabinogiPackageToolView::AssertValid() const
{
	CListView::AssertValid();
}

void CMabinogiPackageToolView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMabinogiPackageToolDoc* CMabinogiPackageToolView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMabinogiPackageToolDoc)));
	return (CMabinogiPackageToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMabinogiPackageToolView ��Ϣ�������
void CMabinogiPackageToolView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: ��Ӵ�������Ӧ�û��Դ�����ͼ��ʽ�ĸ���	
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);	
}
