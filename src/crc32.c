//
//  crc32.c
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "crc32.h"
#include <memory.h>

uint32_t crc32(const uint8_t* bytes, size_t len) {
    static uint32_t* table = NULL;

    if(table == NULL) {
        table = malloc(256 * sizeof(uint32_t));
        for(int i = 0; i < 256; i++) {
            uint32_t c = i;
            for(int j = 0; j < 8; j++) {
                c = (c % 2 == 0) ? (c >> 1) : (0xEDB88320 ^ (c >> 1));
            }
            table[i] = c;
        }
    }

    uint32_t crc = ~0;
    for(int i = 0; i < len; i++) {
        uint32_t byte = bytes[i];
        crc = (crc >> 8) ^ table[(crc ^ byte) & 0xFF];
    }
    return ~crc;
}
