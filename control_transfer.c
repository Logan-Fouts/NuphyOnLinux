#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>
#include <string.h>
#include "control_transfer.h"

int control_transfer(libusb_control_info *info, u_int8_t *action_code)
{
    if (!action_code)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int transferred = libusb_control_transfer(
        info->handle,
        0x21,
        0x09,
        0x0306,
        info->wIndex,
        action_code,
        info->wLength,
        3000);

    if (transferred < 0)
    {
        fprintf(stderr, "Error during control transfer: %s\n", libusb_error_name(transferred));
    }
}