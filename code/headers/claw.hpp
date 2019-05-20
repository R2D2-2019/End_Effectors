#pragma once

#include <hwlib.hpp>
#include <pwm.hpp>

namespace r2d2::end_effectors {
    class claw_c {
    public:
        claw_c(uint8_t pot_pin_number = 0, uint8_t pwm_pin_number = 0);
        void open();
        void close();
    private:
        hwlib::target::pin_adc pot;
        R2D2::pwm_lib::pwm_c pwm;
        const uint16_t pot_offset = 1250;
        const uint8_t pot_per_pwm_step = 132;
        const uint8_t pot_scans = 50;
        const uint8_t open_pwm = 13;
        const uint8_t closed_pwm = 33;
    };
}