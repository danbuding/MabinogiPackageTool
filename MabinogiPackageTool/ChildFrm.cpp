
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "MabinogiPackageTool.h"

#include "ChildFrm.h"
#include "LeftView.h"
#include "MabinogiPackageToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &CChildFrame::OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &CChildFrame::OnViewStyle)
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	// ������ִ���
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMabinogiPackageToolView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������
CMabinogiPackageToolView* CChildFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CMabinogiPackageToolView* pView = DYNAMIC_DOWNCAST(CMabinogiPackageToolView, pWnd);
	return pView;
}

void CChildFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	if (!pCmdUI)
		return;

	// TODO: �Զ������չ�˴����Դ�����ͼ���˵��ϵ�ѡ�
	CMabinogiPackageToolView* pView = GetRightPane(); 

	// ����Ҵ�����δ�������߲�����ͼ������ô˷�Χ�ڵ�����
	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;
		// ��������� ID_VIEW_LINEUP����ֻ���ڴ���
		// LVS_ICON �� LVS_SMALLICON ģʽʱ����������
		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// ����ʹ�õ�������ӳ��ͼ����ʽ
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}

void CChildFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: �Զ������չ�˴����Դ�����ͼ���˵��ϵ�ѡ�
	CMabinogiPackageToolView* pView = GetRightPane();

	// ����Ҵ����Ѵ��������� CMabinogiPackageToolView������˵�����...
	if (pView != NULL)
	{
		int nStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// Ҫ���б�ؼ����������
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// ������������б�ؼ��ϵ���ʽ
		case ID_VIEW_DETAILS:
			nStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			nStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			nStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			nStyle = LVS_LIST;
			break;
		}

		// ������ʽ�����ڽ��Զ����»���
		if (nStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, nStyle);
	}
}
