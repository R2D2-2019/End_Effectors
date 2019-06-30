#pragma once

#include <base_module.hpp>

namespace r2d2::end_effectors {

    /**
     * Class end_effector_c is the abstract base class for all end effectors.
     * It is used by the interface as a listener
     */
    class end_effector_c {
    protected:
        end_effector_type type;

    public:
        /**
         * This function can be used to reset the end effector to its default
         * (starting) state
         */
        virtual void reset() = 0;

        /**
         * This function is used to process incoming frames
         *
         * @param comm the comm used by the module
         */
        virtual void process(base_comm_c &comm) = 0;

        /**
         *  This function is called on initialization and should be used to set
         * wich frames to listen to
         *
         * @param comm the comm used by the module
         */
        virtual void set_listen_frame_types(base_comm_c &comm) = 0;

        /**
         * This function returns the type of the end effector
         *
         * @return the type of this end effector
         */
        end_effector_type get_type() const {
            return type;
        }
    };
} // namespace r2d2::end_effectors