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
    
    int32_t claw_c::calc_pot_difference(uint8_t current_pwm) {
        uint32_t pot_value;
        uint32_t expected_pot;
        int32_t difference;
        pot_value = 0;
        expected_pot = pot_per_pwm_step * (current_pwm-open_pwm) + pot_offset;
        for(uint8_t i = 0; i < pot_scans; i++) {
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
        for(uint8_t current_pwm = open_pwm; current_pwm <= closed_pwm; current_pwm++) {
            if(!collision) {
                pwm.set_duty_cycle(current_pwm);
                hwlib::wait_ms(80);
                difference = calc_pot_difference(current_pwm);
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