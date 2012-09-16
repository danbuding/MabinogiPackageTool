
// LeftView.h : CLeftView ��Ľӿ�
//


#pragma once

#include <memory>
using namespace std::tr1;

class CPackFolder;
class CMabinogiPackageToolDoc;
class CLeftView : public CTreeView
{
protected: // �������л�����
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// ����
public:
	CMabinogiPackageToolDoc* GetDocument();

// ����
public:

// ��д
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_iIconFolder;
	int m_iIconFolderOpen;
	void InsertItem( HTREEITEM hParentItem, shared_ptr<CPackFolder> spFolder );
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // LeftView.cpp �еĵ��԰汾
inline CMabinogiPackageToolDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CMabinogiPackageToolDoc*>(m_pDocument); }
#endif

