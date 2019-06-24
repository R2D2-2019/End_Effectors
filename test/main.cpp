#define CATCH_CONFIG_MAIN

#include <claw.hpp>
#include <end_effector.hpp>
#include <module.hpp>


#include <catch.hpp>
#include <ostream>

using namespace r2d2;


TEST_CASE("Default settings from claw"){
    // Standard values for the claw, these need to be valid in order for the claw to work.

    REQUIRE(pot_offset == 1250);
    REQUIRE(pot_per_pwm_step == 132);
    REQUIRE(pot_scans == 50);
    REQUIRE(open_pwm == 13);
    REQUIRE(closed_pwm == 34);
}

TEST_CASE("Default pins"){
    REQUIRE(pot == hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
    REQUIRE(pwm == R2D2::pwm_lib::pwm_c(0));
}

TEST_CASE("Test the potentiometer"){
    // This mock_adc will return the given mock_adc_value when calling the read() function.
    auto mock_adc_pin = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
    
    // This read function will read the potentiometer values, if it gives no values back it is not connected.
    auto pot_value = mock_adc_pin.read();

    REQUIRE(pot_value > 0);
}

TEST_CASE("Claw positions"){}