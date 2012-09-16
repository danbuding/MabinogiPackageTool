
// MabinogiPackageToolDoc.cpp : CMabinogiPackageToolDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MabinogiPackageTool.h"
#endif

#include "MabinogiPackageToolDoc.h"

#include <propkey.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMabinogiPackageToolDoc

IMPLEMENT_DYNCREATE(CMabinogiPackageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMabinogiPackageToolDoc, CDocument)
END_MESSAGE_MAP()


// CMabinogiPackageToolDoc ����/����

CMabinogiPackageToolDoc::CMabinogiPackageToolDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_pPackInput = NULL;
	m_spRoot = shared_ptr<CPackFolder>(new CPackFolder);
}

CMabinogiPackageToolDoc::~CMabinogiPackageToolDoc()
{
}

BOOL CMabinogiPackageToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMabinogiPackageToolDoc ���л�

void CMabinogiPackageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		m_pPackInput = pack_input(ar.GetFile()->GetFilePath());

		Parse();

	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMabinogiPackageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMabinogiPackageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMabinogiPackageToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMabinogiPackageToolDoc ���

#ifdef _DEBUG
void CMabinogiPackageToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMabinogiPackageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMabinogiPackageToolDoc ����

shared_ptr<CPackFolder> CMabinogiPackageToolDoc::GetRoot()
{
	return m_spRoot;
}


void CMabinogiPackageToolDoc::DeleteContents()
{
	if (m_pPackInput)
	{
		pack_input_close(m_pPackInput);
		m_pPackInput = NULL;
	}

	m_spRoot->Clean();
}


void CMabinogiPackageToolDoc::Parse(void)
{
	m_pSelectedFolder = NULL;
	m_spRoot->Clean();
	if (m_pPackInput)
	{
		// TODO ���ļ��ж�ȡ�����ļ�����
		m_spRoot->m_strName = TEXT("Data");

		// ��������״�ṹ
		size_t count = pack_input_get_entry_count(m_pPackInput);
		for (size_t i = 0; i < count; i++)
		{
			USES_CONVERSION;
			PPACKENTRY pEntry = pack_input_get_entry(m_pPackInput, i);
			
			static LPCTSTR lpszTokens = TEXT("/\\");
			int pos = 0;
			// �ָ�·��
			vector<CString> paths;
			CString resToken;
			CString fullName = CA2W(pEntry->name);
			resToken = fullName.Tokenize(lpszTokens, pos);
			while (resToken != TEXT(""))
			{
				paths.push_back(resToken);
				resToken = fullName.Tokenize(lpszTokens, pos);
			}

			CString fileName = *paths.rbegin();
			paths.pop_back();

			shared_ptr<CPackFolder> spFolder = m_spRoot;
			for (size_t j = 0;j < paths.size();j++)
			{
				CString path = paths.at(j);
				spFolder = spFolder->FindOrCreateFolder(path);
			}

			shared_ptr<CPackEntry> entry(new CPackEntry);
			entry->index = i;
			entry->m_pInput = m_pPackInput;
			entry->m_strName = fileName;
			spFolder->m_entries.push_back(entry);

		}

		m_pSelectedFolder = m_spRoot.get();
	}
}
