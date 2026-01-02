#pragma once
#include <libusb-1.0/libusb.h>

struct goodix_device {
    libusb_context *ctx;
    libusb_device_handle *handle;
    uint8_t ep_in;
    uint8_t ep_out;
};

/* USB helpers */
int goodix_bulk_write(struct goodix_device *dev,
                      const uint8_t *buf,
                      int len);

int goodix_bulk_read(struct goodix_device *dev,
                     uint8_t *buf,
                     int len);
