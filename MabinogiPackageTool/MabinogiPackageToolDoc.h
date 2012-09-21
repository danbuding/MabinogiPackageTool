
// MabinogiPackageToolDoc.h : CMabinogiPackageToolDoc ��Ľӿ�
//


#pragma once

#include <vector>
#include <memory>
#include "../MabinogiPackageResource/mabipackage.h"

using namespace std;
using namespace std::tr1;


class CPackEntry
{
public:
	shared_ptr< vector<byte> > GetData()
	{
		PPACKENTRY pEntry = pack_input_read_for_entry(m_pInput, m_index);
		shared_ptr< vector<byte> > buffer(new vector<byte>(pEntry->decompress_size));

		pack_input_read(m_pInput, &*buffer->begin(), buffer->size());

		return buffer;
	}

	PPACKENTRY GetEntry() 
	{
		return pack_input_get_entry(m_pInput, m_index);
	}
	
	/**
	 * д��ָ�����ļ�
	 */
	void WriteToFile(LPCTSTR lpszFileName)
	{
		// ���·������������Ҫ����
		TCHAR szFullPath[MAX_PATH] = {0};
		lstrcpy(szFullPath, lpszFileName);
		for (int i = 0; szFullPath[i] != 0 && i < MAX_PATH; i++)
		{
			// ���Դ��������ļ���
			if (szFullPath[i] == '\\' || szFullPath[i] == '/')
			{
				if (szFullPath[i - 1] != ':')
				{
					// ��ʱ����һ���ļ���·��
					TCHAR old = szFullPath[i];
					szFullPath[i] = 0; // ֱ�ӽض��ַ���
					if (::GetFileAttributes(szFullPath) !=  FILE_ATTRIBUTE_DIRECTORY)
					{
						::CreateDirectory(szFullPath, NULL);
					}
					
					szFullPath[i] = old; // �ָ�
				}
			}
		}

		shared_ptr<vector<byte> > spData = GetData();
		CFile file(lpszFileName, CFile::modeCreate | CFile::modeWrite);
		file.Write(&*spData->begin(), spData->size());
		file.Close();
	}

	CString m_strName;
	size_t m_index;
	PPACKINPUT m_pInput;

};

/**
 * Tree �ڵ�
 */
class CPackFolder
{
public:
	void Clean()
	{
		m_entries.clear();
		m_children.clear();
	};

	shared_ptr<CPackFolder> FindOrCreateFolder( LPCTSTR name )
	{
		for (size_t i = 0;i < m_children.size();i++)
		{
			if (m_children.at(i)->m_strName == name)
			{
				return m_children.at(i);
			}
		}

		// �����µ�
		shared_ptr<CPackFolder> spFolder(new CPackFolder);
		spFolder->m_strName = name;
		spFolder->m_parent = this;
		m_children.push_back(spFolder);
		return spFolder;
	}

	CString m_strName;
	CPackFolder *m_parent;
	vector<shared_ptr<CPackFolder>> m_children;
	vector<shared_ptr<CPackEntry>> m_entries;
};

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
	shared_ptr<CPackFolder> m_spRoot;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	shared_ptr<CPackFolder> GetRoot();
	CPackFolder *m_pSelectedFolder;
	virtual void DeleteContents();
private:
	void Parse(void);
};
