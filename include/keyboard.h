#include <stdint.h>

struct key
{
    char key_value[32];
    uint8_t key_code[1032];
    int key_value_ix;
};