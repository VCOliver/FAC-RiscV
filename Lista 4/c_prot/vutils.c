#include "vutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int32_t read_int(void) {
    char buf[11] = {0}; // Max characters in int32 numbers
    ssize_t nbytes = read(STDIN_FILENO, buf, sizeof(buf)-1);
    if (nbytes <= 0) {
        const char err_msg[] = "Warning: no bytes read in STDIN_FILENO\n";
        write(STDERR_FILENO, err_msg, sizeof(err_msg));
        return 0;
    }
    buf[nbytes] = '\0';

    return to_valid_int32(buf);
}

void read_string(char* buf, size_t size) {
    ssize_t nbytes = read(STDIN_FILENO, buf, size - 1);
    if (nbytes <= 0) {
        const char err_msg[] = "Warning: no bytes read in STDIN_FILENO\n";
        write(STDERR_FILENO, err_msg, sizeof(err_msg));
        return;
    }
    buf[nbytes] = '\0'; // Null-terminate the string
}

void print_int(int32_t num){
	char buf[11] = {0};
    snprintf(buf, sizeof(buf), "%d", num);
    write(STDOUT_FILENO, buf, sizeof(buf)-1);
    char newline = '\n';
    write(STDOUT_FILENO, &newline, 1);	
}

void print_int_hex(uint8_t *bytes, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", bytes[i]);
    }
    printf("\n");
}
