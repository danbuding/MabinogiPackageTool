#include "mabipackage.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

struct _s_pack_header
{
	char signature[8];	// 'P' 'A' 'C' 'K' 0x02 0x01 0x00 0x00
	unsigned long d1;	// 1
	unsigned long sum;	// �ļ�����
	FILETIME ft1;
	FILETIME ft2;
	char path[480];		// 'd' 'a' 't' 'a' '\' 0x00 ...

};

struct _s_pack_list_header 
{
	unsigned long sum;				// �ļ�����
	unsigned long list_header_size;	// �ļ�ͷ�б��С(�����˿հ�����)
	unsigned long blank_size;		// �ļ��б��������֮��Ŀհ������С 
	unsigned long data_section_size;		// ��������С
	char zero[16];

};

struct _s_pack_item_name
{
	char len_or_type;
	union
	{
		// len_or_type == 0x05��ʱ��
		struct  
		{
			unsigned long len;
			char  sz_ansi_name2[1];
		};

		// ��ͨ����µ��ļ���
		char sz_ansi_name[1];
	};
};

struct _s_pack_item_info
{
	unsigned long seed;
	unsigned long zero;
	unsigned long offset;
	unsigned long compress_size;
	unsigned long decompress_size;
	unsigned long is_compressed;
	FILETIME ft[5];
};

#pragma pack()

PPACKINPUT pack_input(char *file_name) 
{
	// ��������ֵ
	PPACKINPUT input = (PPACKINPUT) malloc(sizeof(s_pack_input_stream));
	memset(input, 0, sizeof(s_pack_input_stream));

	// ���ļ�
	input->_file = fopen(file_name, "rb");

	size_t tmp;
	_s_pack_header header;
	tmp = fread(&header, sizeof(header), 1, input->_file);
	if (tmp != sizeof(header))
	{
		fprintf(stderr, "%s(%d)-%s:%s", __FILE__, __LINE__ , __FUNCTION__, "read header error.");
		pack_input_close(input);
		return 0;
	}

	// ����ļ�ͷ
	if (memcmp(header.signature, "PACK", 4) != 0)
	{
		fprintf(stderr, "%s(%d)-%s:%s", __FILE__, __LINE__ , __FUNCTION__, "header signature error.");
		pack_input_close(input);
		return 0;
	}

	_s_pack_list_header list_header;
	tmp = fread(&list_header, sizeof(list_header), 1, input->_file);
	if (tmp != sizeof(list_header))
	{
		fprintf(stderr, "%s(%d)-%s:%s", __FILE__, __LINE__ , __FUNCTION__, "read list header error.");
		pack_input_close(input);
		return 0;
	}

	// ���ص��ڴ�
	void *p_list_buffer = malloc(list_header.list_header_size);
	tmp = fread(p_list_buffer, list_header.list_header_size, 1, input->_file);
	if (tmp != sizeof(list_header.list_header_size))
	{
		fprintf(stderr, "%s(%d)-%s:%s", __FILE__, __LINE__ , __FUNCTION__, "read list content error.");
		pack_input_close(input);
		return 0;
	}

	char *p_tmp = (char *) p_list_buffer;
	for (size_t i = 0; i < list_header.sum; i++)
	{
		_s_pack_item_name * p_item_name = (_s_pack_item_name *) p_tmp;
		size_t size;
		if (p_item_name->len_or_type < 4)
		{
			// ��һ�ֽ�С��4
			size = (0x10 * (p_item_name->len_or_type + 1));
		}
		else if (p_item_name->len_or_type == 4)
		{
			// �ɶ�Ķ�ħè��������ôҪ�������
			size = 0x60 ;
		}
		else
		{
			// �����ο�mabiunpack����
			size = p_item_name->len + 5;
		}

		string name;
		if ( p_item_name->len_or_type <= 0x04 )
		{
			name = p_item_name->sz_ansi_name;
		}
		else // 0x05
		{
			name = p_item_name->sz_ansi_name2;
		}

		// ָ���Խ���ƶ�����
		p_tmp += size;

		_s_pack_item_info * p_info = (_s_pack_item_info *) p_tmp;

		/*
		// �ۼ��ļ�ƫ�ƣ���ʵ�����޸����ڴ�
		pInfo->offset += sizeof(PACKAGE_HEADER) + sizeof(PACKAGE_LIST_HEADER) + listHeader.list_header_size;

		// ָ�붨λ����һ��
		pTemp += sizeof(ITEM_INFO);

		shared_ptr<IResource> spResource(new CPackResource(name, spFile, pInfo));
		pResourceSet->m_Resources.push_back( spResource );
		*/

	}

}
PPACKOUTPUT pack_output(char *file_name) 
{

}

void pack_input_close(PPACKINPUT input)
{
	if (input)
	{
		// ������Ҫ�ر��ļ�
		if (input->_file)
		{
			fclose(input->_file);
			input->_file = 0;
		}

		free(input);
	}
}
void pack_output_close(PPACKOUTPUT output)
{
}

void pack_inpu_reset(PPACKINPUT input)
{
}
PPACKENTRY pack_input_get_next_entry(PPACKINPUT input)
{
}
size_t pack_input_read(PPACKINPUT input, byte* buffer, size_t size);
{
}

void pack_output_put_next_entry(PPACKOUTPUT output, PPACKENTRY entry)
{
}
void pack_output_write(PPACKOUTPUT output, byte* buffer, size_t size)
{
}
void pack_output_close_entry(PPACKOUTPUT output)
{
}



#ifdef __cplusplus
}
#endif