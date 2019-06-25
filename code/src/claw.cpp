#include <claw.hpp>

namespace r2d2::end_effectors {
    claw_c::claw_c(hwlib::adc &pot_pin, r2d2::pwm_lib::pwm_c pwm_pin)
    : pot(pot_pin), pwm(pwm_pin) {
        type = end_effector_type::CLAW;
    }
    
    void claw_c::open_claw() {
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
            hwlib::wait_ms_busy(1);
        }
        pot_value /= pot_scans;
        difference = pot_value - expected_pot;
        return difference;
    }

    void claw_c::close_claw() {
        bool collision = false;
        int32_t difference;
        open_claw();
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
        open_claw();
    }

    void claw_c::process(base_comm_c &comm) {
        while (comm.has_data()) {
            auto frame = comm.get_data();

            if (frame.request) {
                if (frame.type != frame_type::END_EFFECTOR_TYPE) {
                    continue;
                }
                frame_end_effector_type_s ee_type;
                ee_type.type = end_effector_type::CLAW;
                comm.send(ee_type);
                continue;
            }

            const auto close = frame.as_frame_type<
                frame_type::END_EFFECTOR_CLAW
            >().close;

            if (close) {
                close_claw();
            } else {
                open_claw();
            }
        }
    }

    void claw_c::set_listen_frame_types(base_comm_c &comm) {
        comm.listen_for_frames(
            { frame_type::END_EFFECTOR_CLAW }
        );
    }
}