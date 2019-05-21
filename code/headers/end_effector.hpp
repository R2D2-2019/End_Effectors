#pragma once

namespace r2d2::end_effectors {

    /**
     * This enum contains the different end effector types.
     */
    enum end_effector_type {
        CLAW
    };

    /**
     * Class end_effector_c is the abstract base class for all end effectors.
     * It is used by the interface as a listener
     */
    class end_effector_c {
    private:
        end_effector_type type;
    public:
        /**
         * This function can be used to reset the end effector to its default (starting) state
         */
        virtual void reset() = 0;

        /**
         * This function returns the type of the end effector
         * 
         * @return
         */
        end_effector_type get_type() const {
            return type;
        }
    };
}