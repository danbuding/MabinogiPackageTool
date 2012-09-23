#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _s_pack_entry {
	char name[MAX_PATH];
	unsigned long seed;				// �������ӣ�ֻ����input���entry���д�ֵ��output�в���Ҫ����
	unsigned long offset;			// ������ƫ�ƣ�ֻ����input���entry���д�ֵ��output�в���Ҫ����
	unsigned long compress_size;	// ѹ�����С��ֻ����input���entry���д�ֵ��output�в���Ҫ����
	unsigned long decompress_size;	// ��ѹ���С��ֻ����input���entry���д�ֵ��output�в���Ҫ����
	unsigned long is_compressed;	// �Ƿ������ѹ����ֻ����input���entry���д�ֵ��output�в���Ҫ����
	FILETIME ft[5];
} s_pack_entry, *PPACKENTRY;

typedef struct _s_pack_input_stream {
	size_t _pos;	// ��ǰ�����entry index
	byte *_ptr;		// ��ǰ��ȡ���ֽ�ָ��
	byte *_buffer;	// ��ǰentry��ѹ����������
	FILE *_file;
	PPACKENTRY _entries;
	size_t _entry_count;
} s_pack_input_stream, *PPACKINPUT;

typedef struct _s_pack_output_stram {
	unsigned long _seed;
	
	
	size_t _pos;
	FILE *_file;
	TCHAR _file_name[MAX_PATH];
	FILE *_tmp_file;				// ѹ�����ݵ���ʱ�ļ�
	TCHAR _tmp_file_name[MAX_PATH];

	byte *_buffer;
	byte *_ptr;
	size_t _buffer_malloc_count;

	PPACKENTRY _entries;
	size_t _entry_malloc_count;	// �Ѿ������ڴ�ĸ���
} s_pack_output_stram, *PPACKOUTPUT;


PPACKINPUT pack_input(LPCTSTR file_name);
PPACKOUTPUT pack_output(LPCTSTR file_name, unsigned long version);

void pack_input_close(PPACKINPUT input);
void pack_output_close(PPACKOUTPUT output);
/**
 * �������
 */
void pack_output_drop(PPACKOUTPUT output);

void pack_inpu_reset(PPACKINPUT input);
size_t pack_input_get_entry_count(PPACKINPUT input);
PPACKENTRY pack_input_get_entry(PPACKINPUT input, size_t index);
PPACKENTRY pack_input_read_for_entry(PPACKINPUT input, size_t index);
size_t pack_input_read(PPACKINPUT input, byte* buffer, size_t size);

void pack_output_put_next_entry(PPACKOUTPUT output, PPACKENTRY entry);
void pack_output_write(PPACKOUTPUT output, byte* buffer, size_t size);
void pack_output_close_entry(PPACKOUTPUT output);

#ifdef __cplusplus
}
#endif