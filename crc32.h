#ifndef _CCRC32_H
#define _CCRC32_H
///////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>

uint8_t crc32_file(uint32_t * crc_out, char * file_name, size_t buffer_size);
uint32_t crc32(uint32_t crc, unsigned char *p_buffer, size_t len);


///////////////////////////////////////////////////////////////////////////////
#endif
