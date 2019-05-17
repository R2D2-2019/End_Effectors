#include "hwlib.hpp"
#include <pwm.hpp>
#include "claw_c.hpp"

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
 
    auto klauw = r2d2::end_effectors::claw_c();

    hwlib::wait_ms(1000);
    klauw.close();
}