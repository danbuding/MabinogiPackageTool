
// MabinogiPackageToolDoc.h : CMabinogiPackageToolDoc ��Ľӿ�
//


#pragma once

#include "../MabinogiPackageResource/mabipackage.h"

class CMabinogiPackageToolDoc : public CDocument
{
protected: // �������л�����
	CMabinogiPackageToolDoc();
	DECLARE_DYNCREATE(CMabinogiPackageToolDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMabinogiPackageToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	PPACKINPUT m_pPackInput;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
	PPACKINPUT GetPackInput(void);
};
