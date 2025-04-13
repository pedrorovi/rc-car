#include "debug_factory.h"

#include "serial_controller.h"

Debug* debug_singleton = nullptr;
SerialController* serial = nullptr;

Debug* getDebugFactory() {
    if (debug_singleton == nullptr) {
#if TEST_MODE == 1
        serial = new SerialController(SerialPort::UART);
#else
        serial = new SerialController(SerialPort::BLUETOOTH);
#endif
        serial->begin(115200);
        debug_singleton = new Debug(serial);
        debug_singleton->info("Debug factory started");
    }
    return debug_singleton;
}
