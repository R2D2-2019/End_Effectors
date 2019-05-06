#include "hwlib.hpp"

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    auto pwm = hwlib::target::pin_out(hwlib::target::pins::d9);
    auto pot = hwlib::target::pin_adc(hwlib::target::ad_pins::a2);
    pwm.write(0);
    for (;;) {
        pwm.write(1);
        hwlib::wait_us(2400);
        pwm.write(0);
        hwlib::wait_ms(1000);

        hwlib::cout << "wait 2400 " << pot.read() << '\n';

        pwm.write(1);
        hwlib::wait_us(1000);
        pwm.write(0);
        hwlib::wait_ms(1000);

        hwlib::cout << "wait 1000 " << pot.read() << '\n';
    }
}