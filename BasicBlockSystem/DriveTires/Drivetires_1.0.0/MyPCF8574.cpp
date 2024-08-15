#include "MyPCF8574.h"

uint8_t MyPCF8574::read8() {
    uint8_t value = 0;
    for (int i = 0; i < 8; i++) {
        value |= (digitalRead(i) << i);
    }
    return value;
}
