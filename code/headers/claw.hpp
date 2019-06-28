#pragma once

#include <hwlib.hpp>
#include <pwm.hpp>
#include <end_effector.hpp>

namespace r2d2::end_effectors {
    class claw_c : public end_effector_c {
    public:
        /**
         * This is the constructor for the claw
         * 
         * @param pot_pin A hwlib adc pin to read the potmeter 
         * inside the servo of the claw
         * 
         * @param pwm_pin A r2d2 pwm lib pin used to send a pwm 
         * signal to the servo inside the claw
         */
        claw_c(hwlib::adc &pot_pin, r2d2::pwm_lib::pwm_c &pwm_pin);
         
        /**
         * This function is used to open the claw
         */
        void open_claw();

        /**
         * This function is used to close the claw in steps
         * When something is stuck inside the claw the claw will stop closing
         */
        void close_claw();

        /**
         * This function resets the end effector to its default state
         * For the claw this means opening the claw
         */
        void reset() override;
        
        /**
         * This function is used to process incoming frames
         * 
         * @param comm The comm used by the module
         */
        void process(base_comm_c &comm) override;

        /**
         * This function is called on initialization 
         * and should be used to set which frames to listen to
         * 
         * @param comm The comm used by the module
         */
        void set_listen_frame_types(base_comm_c &comm) override;

    private:
        /**
         * This function calculates the difference between
         * the current pot reading and what the pot reading should be
         * 
         * @warning This function waits for 50 ms
         * The wait we use is a busy wait this means
         * that we cant switch tasks during this wait
         * 
         * @param current_pwm The current pwm (duty cycle)
         * is used to calculate what the current pot reading should be
         */
        int16_t calc_pot_difference(uint8_t current_pwm);

        /**
         * This is used to store the pot pin
         */
        hwlib::adc &pot;

        /**
         * This is used to store the pwm pin
         */
        r2d2::pwm_lib::pwm_c &pwm;

        /**
         * The offset that the lowest (open) reading has
         */
        constexpr static uint16_t pot_offset = 1250;

        /**
         * The amount the pot reading changes for each step
         */
        constexpr static uint8_t pot_per_pwm_step = 132;

        /**
         * The amount of times the pot value should be read each scan
         * to calculate an average pot value
         */
        constexpr static uint8_t pot_scans = 50;

        /**
         * The pwm value (duty cycle) that corresponds to the claw being open
         */
        constexpr static uint8_t open_pwm = 13;

        /**
         * The pwm value (duty cycle) that corresponds to the claw being closed
         */
        constexpr static uint8_t closed_pwm = 33;

        /**
         * This is the value used to determine if there is collision
         * If the current pot value is has a offset of more than 100 with the
         * expected pot value, the claw will stop closing
         */
        constexpr static uint8_t grip_threshold = 100;
    };
}