#include <stdio.h>
#include "goodix.h"

int main(void)
{
    struct goodix_device *dev;

    if (goodix_open(&dev) < 0) {
        printf("Failed to open Goodix device\n");
        return 1;
    }

    printf("Goodix device opened successfully\n");

    goodix_close(dev);
    return 0;
}
