#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>

#include "goodix.h"
#include "goodix_internal.h"

#define GOODIX_VID 0x27c6
#define GOODIX_PID 0x55a2

int goodix_open(struct goodix_device **out)
{
    struct goodix_device *dev = calloc(1, sizeof(*dev));
    if (!dev)
        return -1;

    if (libusb_init(&dev->ctx) < 0)
        goto err_free;

    dev->handle = libusb_open_device_with_vid_pid(
        dev->ctx, GOODIX_VID, GOODIX_PID);

    if (!dev->handle)
        goto err_ctx;

    if (libusb_kernel_driver_active(dev->handle, 0) == 1)
        libusb_detach_kernel_driver(dev->handle, 0);

    if (libusb_claim_interface(dev->handle, 0) < 0)
        goto err_handle;

    dev->ep_out = 0x01;  /* bulk OUT */
    dev->ep_in  = 0x82;  /* bulk IN */

    *out = dev;
    return 0;

err_handle:
    libusb_close(dev->handle);
err_ctx:
    libusb_exit(dev->ctx);
err_free:
    free(dev);
    return -1;
}

void goodix_close(struct goodix_device *dev)
{
    if (!dev)
        return;

    libusb_release_interface(dev->handle, 0);
    libusb_close(dev->handle);
    libusb_exit(dev->ctx);
    free(dev);
}

int goodix_bulk_write(struct goodix_device *dev,
                      const uint8_t *buf,
                      int len)
{
    int transferred;
    return libusb_bulk_transfer(
        dev->handle,
        dev->ep_out,
        (unsigned char *)buf,
        len,
        &transferred,
        1000
    );
}

int goodix_bulk_read(struct goodix_device *dev,
                     uint8_t *buf,
                     int len)
{
    int transferred;
    return libusb_bulk_transfer(
        dev->handle,
        dev->ep_in,
        buf,
        len,
        &transferred,
        2000
    );
}
