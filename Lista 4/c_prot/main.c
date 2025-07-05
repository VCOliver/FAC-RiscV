#include <stdio.h>
#include <string.h>
#include "vutils.h"

const char BASE64[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

int get_len(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    if (str[len - 1] == '\n') {
        len--; // Remove newline character if present
    }
    return len;
}

int search_base64_index(const char ch){
    // Handle padding character
    if (ch == '=') {
        return 0;
    }
    
    int b64_len = sizeof(BASE64);
    int i = 0;
    for(i=0; i < b64_len; i++){
        if( ch == BASE64[i]){
            break;
        }
    }
    return i;
}

typedef union {
    uint32_t raw;
    struct{
        uint32_t v24 : 24;
        uint32_t     :  6;
    };
    struct {
        uint8_t bytes[3];
        uint8_t _padding;
    };
} uint24_t;

uint8_t *base64_to_byte(const char* buf, int len){
    int padding = 0;
    if (len >= 2 && buf[len-1] == '=') padding++;
    if (len >= 1 && buf[len-2] == '=') padding++;
    int output_len = (len / 4) * 3 - padding;
    
    uint8_t *bytes = (uint8_t*)malloc(output_len);
    uint8_t *index = (uint8_t*)malloc(len);
    
    for(int i=0; i<len; i++){
        index[i] = search_base64_index(buf[i]);
    }
    
    
    for (int i=0; i<len; i+=4){
        uint24_t temp;
        // Correct bit arrangement for base64 decoding
        temp.v24 = (index[i] << 18) | (index[i+1] << 12) | (index[i+2] << 6) | index[i+3];
        uint8_t *next_byte_ptr = bytes + (i/4)*3;
        
        // Copy bytes in correct order (big-endian)
        if ((i/4)*3 < output_len) next_byte_ptr[0] = temp.bytes[2];
        if ((i/4)*3 + 1 < output_len) next_byte_ptr[1] = temp.bytes[1];
        if ((i/4)*3 + 2 < output_len) next_byte_ptr[2] = temp.bytes[0];
    }
    
    free(index);
    return bytes;
}

int main(void){
    char buf[48] = {0};
    read_string(buf, sizeof(buf));
    int len = get_len(buf);
    if (len % 4 != 0) {
        printf("Error: Input length is not a multiple of 4.\n");
        return 1;
    }

    // Calculate output length considering padding
    int padding = 0;
    if (len >= 2 && buf[len-1] == '=') padding++;
    if (len >= 1 && buf[len-2] == '=') padding++;
    int output_len = (len / 4) * 3 - padding;

    uint8_t *bytes = base64_to_byte(buf, len);

    // Use the updated print_int_hex function to print the decoded bytes
    print_int_hex(bytes, output_len);

    free(bytes);
    return 0;
}