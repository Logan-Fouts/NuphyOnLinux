#include <stdint.h>

typedef struct key
{
    char key_value[32];
    uint8_t key_code[1032];
    int key_value_ix;
} key;

extern struct key keymap[];
key get_key_by_index(int index);