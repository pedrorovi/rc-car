#include "ina219_factory.h"

#include "INA219.h"
#include "i2c.h"

INA219* ina = nullptr;
I2C* i2c = nullptr;

INA219_interface* getINA219Interface() {
    if (ina == nullptr) {
        i2c = new I2C();
        if (!i2c->begin()) {
            return nullptr;
        }
        ina = new INA219(i2c);
    }
    return ina;
}
