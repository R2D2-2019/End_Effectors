#include <hwlib.hpp>
#include <pwm.hpp>
#include <claw.hpp>

#include <comm.hpp>
#include <module.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    r2d2::comm_c comm;

    auto pot_pin = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
    auto pwm_pin = r2d2::pwm_lib::pwm_c(0);

    auto end_effector = r2d2::end_effectors::claw_c(pot_pin, pwm_pin);

    auto module = r2d2::end_effectors::module_c(comm, &end_effector);

    for(;;) {
        module.process();
        hwlib::wait_ms(100);
    }
}