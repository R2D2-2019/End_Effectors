#include <claw.hpp>

namespace r2d2::end_effectors {
    claw_c::claw_c(hwlib::target::pin_adc pot_pin, R2D2::pwm_lib::pwm_c pwm_pin)
    : pot(pot_pin),
    pwm(pwm_pin) {
        type = end_effector_type::CLAW;
    }
    
    void claw_c::open() {
        pwm.set_duty_cycle(open_pwm);
    }
    
    int32_t claw_c::calc_pot_difference() {
        uint32_t pot_value;
        uint32_t expected_pot;
        int32_t difference;
        pot_value = 0;
        expected_pot = pot_per_pwm_step * (i-open_pwm) + pot_offset;
        for(uint8_t j = 0; j < pot_scans; j++) {
            pot_value += pot.read();
            hwlib::wait_ms(1);
        }
        pot_value /= pot_scans;
        difference = pot_value - expected_pot;
        return difference;
    }

    void claw_c::close() {
        bool collision = false;
        int32_t difference;
        open();
        hwlib::wait_ms(1000);
        for(uint8_t i = open_pwm; i <= closed_pwm; i++) {
            if(!collision) {
                pwm.set_duty_cycle(i);
                hwlib::wait_ms(20);
                difference = calc_pot_difference();
                if(difference > 100 || difference < -100) {
                    collision = true;
                }
            }
        }
    }

    void claw_c::reset() {
        open();
    }
}