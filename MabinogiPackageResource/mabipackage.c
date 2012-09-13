#include "mabipackage.h"

#include "mt.h"
#include "zlib.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

typedef struct __s_pack_header
{
	char signature[8];	// 'P' 'A' 'C' 'K' 0x02 0x01 0x00 0x00
	unsigned long d1;	// 1
	unsigned long sum;	// �ļ�����
	FILETIME ft1;
	FILETIME ft2;
	char path[480];		// 'd' 'a' 't' 'a' '\' 0x00 ...

} _s_pack_header;

typedef struct __s_pack_list_header 
{
	unsigned long sum;				// �ļ�����
	unsigned long list_header_size;	// �ļ�ͷ�б��С(�����˿հ�����)
	unsigned long blank_size;		// �ļ��б��������֮��Ŀհ������С 
	unsigned long data_section_size;		// ��������С
	char zero[16];

} _s_pack_list_header;

typedef struct __s_pack_item_name
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
} _s_pack_item_name;

typedef struct __s_pack_item_info
{
	unsigned long seed;
	unsigned long zero;
	unsigned long offset;
	unsigned long compress_size;
	unsigned long decompress_size;
	unsigned long is_compressed;
	FILETIME ft[5];
} _s_pack_item_info;

#pragma pack()
///////////////////////////////////////////////////////////
void _encrypt(char * pBuffer, size_t size, size_t seed )
{
	// ����
	s_mersenne_twister_status mt;
	size_t i;
	unsigned long rseed = (seed << 7) ^ 0xA9C36DE1;
	init_genrand(&mt, rseed);
	for (i = 0; i < size;i++)
	{
		pBuffer[i] = (char)(pBuffer[i]  ^ genrand_int32(&mt));
	}
}

void _decrypt(char * pBuffer, size_t size, size_t seed )
{
	s_mersenne_twister_status mt;
	size_t i;
	unsigned long rseed = (seed << 7) ^ 0xA9C36DE1;
	init_genrand(&mt, rseed);
	for (i = 0; i < size;i++)
	{
		pBuffer[i] = (char)(pBuffer[i]  ^ genrand_int32(&mt));
	}
}
///////////////////////////////////////////////////////////
PPACKINPUT pack_input(LPCTSTR file_name) 
{
	// c���Թ淶���ȶ����ڲ�����
	size_t tmp;
	_s_pack_header header;
	_s_pack_list_header list_header;
	void *p_list_buffer;
	char *p_tmp;
	size_t i;
	PPACKENTRY p_entry;
	_s_pack_item_name * p_item_name;
	size_t size;
	_s_pack_item_info * p_info;

	// ��������ֵ
	PPACKINPUT input = (PPACKINPUT) malloc(sizeof(s_pack_input_stream));
	memset(input, 0, sizeof(s_pack_input_stream));
	input->_pos = -1;

	// ���ļ�
#ifdef _UNICODE
	input->_file = _wfopen(file_name, L"rb");
#else
	input->_file = fopen(file_name, "rb");
#endif
	tmp = fread(&header, sizeof(header), 1, input->_file);
	if (tmp != 1)
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


	tmp = fread(&list_header, sizeof(list_header), 1, input->_file);
	if (tmp != 1)
	{
		fprintf(stderr, "%s(%d)-%s:%s", __FILE__, __LINE__ , __FUNCTION__, "read list header error.");
		pack_input_close(input);
		return 0;
	}

	// ���ص��ڴ�
	p_list_buffer = malloc(list_header.list_header_size);
	tmp = fread(p_list_buffer, list_header.list_header_size, 1, input->_file);
	if (tmp != 1)
	{
		fprintf(stderr, "%s(%d)-%s:%s", __FILE__, __LINE__ , __FUNCTION__, "read list content error.");
		pack_input_close(input);
		return 0;
	}

	p_tmp = (char *) p_list_buffer;
	input->_entry_count = list_header.sum;
	input->_entries = (s_pack_entry *) malloc(sizeof(s_pack_entry) * list_header.sum);
	for (i = 0; i < list_header.sum; i++)
	{
		// ׼������
		p_entry = &input->_entries[i];

		p_item_name = (_s_pack_item_name *) p_tmp;
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

		// ������ʵ����������ܣ�����ĿǰӦ��û����ô����Ŀ¼
		if ( p_item_name->len_or_type <= 0x04 )
		{
			strcpy(p_entry->name, p_item_name->sz_ansi_name);
		}
		else // 0x05
		{
			strcpy(p_entry->name, p_item_name->sz_ansi_name2);
		}

		// ָ���Խ���ƶ�����
		p_tmp += size;

		p_info = (_s_pack_item_info *) p_tmp;
		// ƫ���Ǵ��ļ�ͷ��ʼ��
		p_entry->offset = p_info->offset + sizeof(_s_pack_header) + sizeof(_s_pack_list_header) + list_header.list_header_size;
		p_entry->seed = p_info->seed;
		p_entry->compress_size = p_info->compress_size;
		p_entry->decompress_size = p_info->decompress_size;
		p_entry->is_compressed = p_info->is_compressed;
		memcpy(p_entry->ft, p_info->ft, sizeof(FILETIME) * 5);

		// ָ�붨λ����һ��
		p_tmp += sizeof(_s_pack_item_info);
	}
	free(p_list_buffer);

	return input;
}

// ÿ������һ��
void _grow_entry_array(PPACKOUTPUT output)
{
	output->_entry_malloc_size *= 2;
	output->_entries = (PPACKENTRY) realloc(output->_entries, output->_entry_malloc_size);
}

PPACKOUTPUT pack_output(LPCTSTR file_name) 
{
	PPACKOUTPUT output = (PPACKOUTPUT) malloc(sizeof(s_pack_output_stram));
	memset(output, 0, sizeof(s_pack_output_stram));
	output->_pos = -1;

	// ��ʼ��һ���ռ䣬��ֹ���������ڴ�
	output->_entry_malloc_size = sizeof(s_pack_entry) * 100;
	output->_entries = (PPACKENTRY) malloc(output->_entry_malloc_size);
#ifdef _UNICODE
	output->_file = _wfopen(file_name, L"wb");
#else
	output->_file = fopen(file_name, "wb");
#endif
	return 0;
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

		// �ͷ�entry����
		if (input->_entries)
		{
			free(input->_entries);
			input->_entries = 0;
		}

		if (input->_buffer)
		{
			free(input->_buffer);
			input->_buffer = 0;
		}

		free(input);
	}
}
void pack_output_close(PPACKOUTPUT output)
{
}

void pack_inpu_reset(PPACKINPUT input)
{
	input->_ptr = input->_buffer;
}
size_t pack_input_get_entry_count(PPACKINPUT input)
{
	return input->_entry_count;
}
PPACKENTRY pack_input_get_entry(PPACKINPUT input, size_t index)
{
	return &input->_entries[index];
}
PPACKENTRY pack_input_read_for_entry(PPACKINPUT input, size_t index)
{
	s_pack_entry * p_entry;
	char *p_buffer;
	unsigned long dest_len;

	input->_pos = index;

	p_entry = &input->_entries[input->_pos];
	// ����ǰ���ݽ��н��� ��ѹ
	// �ȶ����ݵ��ڴ�
	p_buffer = (char *) malloc(p_entry->compress_size);
	// ���ļ���ȡ
	fseek(input->_file, p_entry->offset, SEEK_SET);
	_decrypt(p_buffer, p_entry->compress_size, p_entry->seed);
	
	// ׼���û�����
	if (input->_buffer)
	{
		free(input->_buffer);
		input->_buffer = 0;
	}
	input->_buffer = (byte *)malloc(p_entry->decompress_size);
	dest_len = p_entry->decompress_size;
	uncompress(input->_buffer, &dest_len, (byte *)p_buffer, p_entry->compress_size);
	input->_ptr = input->_buffer;

	free(p_buffer);
	return p_entry;
}
size_t pack_input_read(PPACKINPUT input, byte* buffer, size_t size)
{
	s_pack_entry * p_entry;
	size_t remain_size;
	size_t result;
	if (input->_pos < 0 || input->_pos >= input->_entry_count)
	{
		return EOF;
	}
	p_entry = &input->_entries[input->_pos];
	remain_size = p_entry->decompress_size + input->_buffer - input->_ptr;
	result = remain_size >= size ? size : remain_size;
	memcpy(buffer, input->_ptr, result);
	input->_ptr += result;
	return result;
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