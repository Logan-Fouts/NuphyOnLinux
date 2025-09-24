#include "mode_selecter.h"

typedef struct key_data
{
    uint8_t *key_hex;
    int settings_ix;

} key_data;

int update_key(libusb_control_info *info, u_int8_t *key);
int get_keycode_index_for_fn(int fn_number);