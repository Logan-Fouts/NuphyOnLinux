#include <stdint.h>

typedef struct key_mapping
{
    const char *name;
    uint8_t hex;
} key_mapping;

key_mapping* get_keymap();