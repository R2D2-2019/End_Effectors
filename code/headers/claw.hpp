#pragma once

#include <hwlib.hpp>
#include <pwm.hpp>
#include "end_effector.hpp"

namespace r2d2::end_effectors {
    class claw_c : public end_effector_c {
    public:
        claw_c(hwlib::target::pin_adc pot_pin = hwlib::target::pin_adc(hwlib::target::ad_pins::a0),
         R2D2::pwm_lib::pwm_c pwm_pin = R2D2::pwm_lib::pwm_c(0));
        void open();
        void close();
        virtual void reset() override;
    private:
        int32_t calc_pot_difference(uint8_t current_pwm);
        hwlib::target::pin_adc pot;
        R2D2::pwm_lib::pwm_c pwm;
        const uint16_t pot_offset = 1250;
        const uint8_t pot_per_pwm_step = 132;
        const uint8_t pot_scans = 50;
        const uint8_t open_pwm = 13;
        const uint8_t closed_pwm = 33;
    };
}