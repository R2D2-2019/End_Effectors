#include "hwlib.hpp"
#include <pwm.hpp>

#include <comm.hpp>
#include <module.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    r2d2::comm_c comm;
    auto module = r2d2::end_effectors::module_c(comm);

    for(;;) {
        module.process();
        hwlib::wait_ms(100);
    }
}