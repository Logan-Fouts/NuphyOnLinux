#include "key_updater.h"
#include <stdio.h>

int update_key(libusb_control_info *info, u_int8_t *key)
{
    int transferred = libusb_control_transfer(
        info->handle,
        0x21,
        0x09,
        0x0306,
        info->wIndex,
        key,
        1032,
        3000);

    if (transferred < 0)
    {
        fprintf(stderr, "Error during control transfer: %s\n", libusb_error_name(transferred));
    }
}

int get_keycode_index_for_fn(int fn_number)
{
    // Hopefully this is the pattern :)
    return 571 + (fn_number - 9) * 4;
}
