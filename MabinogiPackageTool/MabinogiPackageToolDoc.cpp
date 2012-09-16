
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
		m_pPackInput = pack_input(ar.GetFile()->GetFilePath());
		//PPACKINPUT input = pack_input(ar.GetFile()->GetFilePath());
		//PPACKOUTPUT output = pack_output(ar.GetFile()->GetFilePath() + L".test", 111);
		//byte buffer[10240];

		//size_t count = pack_input_get_entry_count(input);
		//for (int i = 0; i < count; i++)
		//{
		//	PPACKENTRY entry = pack_input_get_entry(input, i);

		//	pack_input_read_for_entry(input, i);
		//	pack_output_put_next_entry(output, entry);

		//	USES_CONVERSION;
		//	TRACE(L"%d/%d %s\n", i, count, A2W( entry->name));

		//	size_t size;
		//	while ((size = pack_input_read(input, buffer, 10240)) >0 )
		//	{
		//		pack_output_write(output, buffer, size);
		//	}

		//	pack_output_close_entry(output);
		//	
		//}
		//
		//pack_input_close(input);
		//pack_output_close(output);
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


void CMabinogiPackageToolDoc::DeleteContents()
{
	if (m_pPackInput != NULL)
	{
		pack_input_close(m_pPackInput);
		m_pPackInput = NULL;
	}
}


PPACKINPUT CMabinogiPackageToolDoc::GetPackInput(void)
{
	return m_pPackInput;
}
