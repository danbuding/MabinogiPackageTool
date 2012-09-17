
// MabinogiPackageToolView.h : CMabinogiPackageToolView ��Ľӿ�
//

#pragma once


class CMabinogiPackageToolView : public CListView
{
protected: // �������л�����
	CMabinogiPackageToolView();
	DECLARE_DYNCREATE(CMabinogiPackageToolView)

// ����
public:
	CMabinogiPackageToolDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMabinogiPackageToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	HIMAGELIST GetShellImageList(BOOL bLarge);
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
//	afx_msg void OnCancelMode();
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // MabinogiPackageToolView.cpp �еĵ��԰汾
inline CMabinogiPackageToolDoc* CMabinogiPackageToolView::GetDocument() const
   { return reinterpret_cast<CMabinogiPackageToolDoc*>(m_pDocument); }
#endif

