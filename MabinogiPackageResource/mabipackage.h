#pragma once

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pack_entry {
	char name[MAX_PATH];
	FILETIME ft[5];
} *PPACKENTRY;
typedef struct pack_input_stream {
	size_t _pos;	// ��ǰ�����entry index
	byte *_base;	// ��ǰ��ȡ���ֽ���������
	byte *_ptr;		// ��ǰ��ȡ���ֽ�ָ��
	byte *_end;		// ��ǰ��ȡ���ֽ�������յ�
} *PPACKINPUT;
typedef struct pack_output_stram {

} *PPACKOUTPUT;


PPACKINPUT pack_input(char *file_name);
PPACKOUTPUT pack_output(char *file_name);

void pack_input_close(PPACKINPUT input);
void pack_output_close(PPACKOUTPUT output);

void pack_inpu_reset(PPACKINPUT input);
PPACKENTRY pack_input_get_next_entry(PPACKINPUT input);
size_t pack_input_read(PPACKINPUT input, byte* buffer, size_t size);

void pack_output_put_next_entry(PPACKOUTPUT output, PPACKENTRY entry);
void pack_output_write(PPACKOUTPUT output, byte* buffer, size_t size);
void pack_output_close_entry(PPACKOUTPUT output);

#ifdef __cplusplus
}
#endif