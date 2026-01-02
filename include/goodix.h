#pragma once
#include <stdint.h>

#define GOODIX_WIDTH  56
#define GOODIX_HEIGHT 176

struct goodix_device;

/* Open Goodix fingerprint device */
int goodix_open(struct goodix_device **dev);

/* Close device and free resources */
void goodix_close(struct goodix_device *dev);
