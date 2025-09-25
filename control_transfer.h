typedef struct libusb_control_info
{
    libusb_device_handle *handle;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
    int timeout;
} libusb_control_info;

int control_transfer(libusb_control_info *info, uint8_t *action_code);