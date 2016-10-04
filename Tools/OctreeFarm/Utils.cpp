#include "Utils.h"

Utils::Utils(QObject *parent) : QObject(parent) {

}

int Utils::bitCount8(int value) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if ((value & 1) == 1) {
            count++;
        }
        value >>= 1;
    }

    return count;
}
