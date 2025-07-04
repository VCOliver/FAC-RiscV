#ifndef VUTILS_H
#define VUTILS_H

#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

// typedef union {
//     struct {
//         uint32_t raw : 24;      // Raw 24-bit value
//         uint32_t     : 8;       // Upper 8 bits (explicitly unused)
//     };
//     struct {
//         uint32_t char0 : 6;     // First base64 character (6 bits)
//         uint32_t char1 : 6;     // Second base64 character (6 bits)  
//         uint32_t char2 : 6;     // Third base64 character (6 bits)
//         uint32_t char3 : 6;     // Fourth base64 character (6 bits)
//     } base64;
//     struct {
//         uint8_t byte0;          // First byte
//         uint8_t byte1;          // Second byte
//         uint8_t byte2;          // Third byte
//     } bytes;
// } data24_t;

static inline int32_t to_valid_int32(const char* str) {
    char* endptr;
    errno = 0;

    long long num = strtoll(str, &endptr, 10);

    // Check for errors
    if (errno == ERANGE) {
        printf("Number out of range! (64bit Overflow)\n");
    } else if (endptr == str) {
        printf("No digits found!\n");
    } else if (*endptr != '\0' && *endptr != '\n') {
            printf("Extra characters after number: %s\n", endptr);
    } else if (num > INT32_MAX) { 
        printf("Number out of range! (32bit Overflow)\n");
    }

    return (int32_t)num;
}

int32_t read_int(void);
void read_string(char* buf, size_t size);

void print_int(int32_t num);
void print_int_hex(uint8_t *bytes, size_t length);

#endif
