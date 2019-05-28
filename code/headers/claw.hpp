#pragma once

#include <hwlib.hpp>
#include <pwm.hpp>
#include <end_effector.hpp>

namespace r2d2::end_effectors {
    class claw_c : public end_effector_c {
    public:
        claw_c(hwlib::target::pin_adc pot_pin = hwlib::target::pin_adc(hwlib::target::ad_pins::a0),
         r2d2::pwm_lib::pwm_c pwm_pin = r2d2::pwm_lib::pwm_c(0));
         
        void open_claw();

        void close_claw();

        void reset() override;

        void process(base_comm_c &comm) override;

        void set_listen_frame_types(base_comm_c &comm) override;

    private:
        int32_t calc_pot_difference(uint8_t current_pwm);

        hwlib::target::pin_adc pot;

        r2d2::pwm_lib::pwm_c pwm;

        constexpr static uint16_t pot_offset = 1250;
        constexpr static uint8_t pot_per_pwm_step = 132;
        constexpr static uint8_t pot_scans = 50;
        constexpr static uint8_t open_pwm = 13;
        constexpr static uint8_t closed_pwm = 33;
    };
}