
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
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MabinogiPackageToolView.cpp �еĵ��԰汾
inline CMabinogiPackageToolDoc* CMabinogiPackageToolView::GetDocument() const
   { return reinterpret_cast<CMabinogiPackageToolDoc*>(m_pDocument); }
#endif

