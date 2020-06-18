/*
 * CRC32 Random Buffer Test
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>
#include <stdbool.h>

// Relative path to header, if working in a project please use absolute path or
// include directory settings
//
#include "../crc32.h"

// Relative path to README File
//
#define FILE_TEST_PATH   "../README.md"

int main(int argc, char * argv[])
{
    int i;
    char * file_name_t;
    if (argc > 1)
        file_name_t = argv[1];
    else
    {
        char file_test[] = FILE_TEST_PATH;
        file_name_t = file_test;
    }

    uint32_t crc_results[8];
    size_t crc_bufs[] = {2048, 1, 12, 55, 1023, 1024, 19, 0};

    for (i = 0; i < 8; i++)
    {
        crc32_file(crc_results+i, file_name_t, crc_bufs[i]);
    }

    uint8_t is_success = 1;
    for (i = 0; i < (8 - 1); i++)
    {
        if (!(crc_results[i] == crc_results[i+1]))
        {
            is_success = 0;
            break;
        }
    }

    if (is_success)
        printf("Success: %08x", crc_results[0]);
    else
    {
        printf("Fail");
    }
    getchar();
}
