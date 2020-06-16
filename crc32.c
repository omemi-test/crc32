#ifndef _CCRC32_C
#define _CCRC32_C

#define _CRT_SECURE_NO_WARNINGS     //Disables fopen() security warning on Microsoft compilers.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>
#include <stdbool.h>

#include "crc32.h"

/* CRC32 for Minimal Memory Use
 *
 * This function provides dynamic memory allocation support for
 * limited memory usage like embedded systems.
 *
 * @param crc[in]  : Inital value of 0x00UL for first calculation or
 *                   calculated CRC in order to further calculation
 *                   of following data
 * @param p_buf[in] : Pointer to the start of the data
 * @param len[in]   : Length of the data
 *
 * @return          : Calculated CRC32
 *
 */
uint32_t crc32(uint32_t crc, unsigned char *p_buffer, size_t len)
{
    // Normal = 0x04C11DB7u;
    // Reversed = 0xedb88320;

    crc = ~crc;

    int k;
    while (len--) {
        crc ^= *p_buffer++;
        for (k = 0; k < 8; k++)
            crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
    }
    return ~crc;
}

/*
 * CRC32 Generation of a File
 *
 * This function reads a file in buffer_size chunks and calculates CRC32
 * Useful for limited memory usages like embedded systems.
 *
 * @param crc_out[in|out]   : Pointer to the 32-bit result storage variable
 * @param file_name[in]     : File Name
 * @param buffer_size[in]   : Length of the data
 *
 * @return                  : 0, Success
 *                            1, Failed to open file for read access.
 *                            2, Out of memory
 */
uint8_t crc32_file(uint32_t * crc_out, char * file_name, size_t buffer_size)
{
    // CRC as null (will be inverted inside of the function)
    //
    *crc_out = 0x0UL;

    FILE * file_handler = NULL;
    unsigned char * data_buffer = NULL;
    size_t bytes_read = 0;

    if((file_handler = fopen(file_name, "rb")) == NULL)
    {
        // Failed to open file for read access.
        return 1;
    }

    if (!buffer_size)
    {
        fseek(file_handler, 0, SEEK_END); // seek to end of file
        buffer_size = ftell(file_handler);
        fseek(file_handler, 0, SEEK_SET); // seek back to beginning of file
    }

    while (!data_buffer)
    {
        if(!(data_buffer = (unsigned char *)malloc(buffer_size))) //Allocate memory for file buffering.
        {
            if ((buffer_size < 2))
            {
                // Out of memory.
                fclose(file_handler);
                return 2;
            }
            else
            {
                buffer_size /= 2;
            }
        }
        else
        {
            break;
        }
    }

    while((bytes_read = fread(data_buffer, sizeof(char), buffer_size, file_handler)))
    {
        *crc_out = crc32(*crc_out, data_buffer, bytes_read);
    }

    free(data_buffer);
    fclose(file_handler);

    return 0;
}


#endif
