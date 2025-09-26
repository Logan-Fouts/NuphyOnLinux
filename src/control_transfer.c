#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>
#include <string.h>
#include "control_transfer.h"

#define VENDOR_ID 0x05ac
#define PRODUCT_ID 0x024f

int control_transfer(libusb_control_info *info, u_int8_t *action_code)
{
    if (!action_code)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
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
        return 1;
    }

    return 0;
}

libusb_control_info initialize_libusb()
{
    struct libusb_control_info info = {
        .handle = NULL,
        .bRequest = 0x09,
        .wValue = 0x0306,
        .wIndex = 1,
        .wLength = 1032,
        .timeout = 3000};

    if (libusb_init(NULL) < 0)
    {
        fprintf(stderr, "libusb init error\n");
        return info;
    }

    info.handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    if (!info.handle)
    {
        fprintf(stderr, "Cannot open device\n");
        libusb_exit(NULL);
        exit(EXIT_FAILURE);
    }

    if (libusb_kernel_driver_active(info.handle, info.wIndex))
        libusb_detach_kernel_driver(info.handle, info.wIndex);

    libusb_claim_interface(info.handle, info.wIndex);

    return info;
}