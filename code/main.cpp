#include "hwlib.hpp"
#include <pwm.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
 
    auto pwm_0 = R2D2::pwm_lib::pwm_c(0);
    auto pot = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);

    int stand = 0;
    bool second = false;
    bool done = false;

    for(;;) {
        if(!done) {
            int potvalue = 0;

            int calc = 132 * stand + 1250;
            for(int i = 0; i < 10; i++) {
                potvalue += pot.read();
                hwlib::wait_ms(10);
            }
            potvalue /= 10;
            if (potvalue < (calc-100) || potvalue > (calc+100)){
                hwlib::cout << "ik heb iets vast\n";
                stand--;
                if(second){
                    done = true;
                }
                second = true;
            }
            else {
                stand++;
                hwlib::cout << "ik ga verder\n";
            }
        }
        pwm_0.change_duty_cycle(stand+13);
        hwlib::wait_ms(500);
    }
}