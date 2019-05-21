#pragma once

#include <base_module.hpp>
#include <end_effector.hpp>

namespace r2d2::end_effectors {

    /**
     * This class is the interface for the end_effector module.
     * It handles incoming frames and commands the end effector to do stuff.
     * It has a pointer to the base end_effector class.
     */
    class module_c : public base_module_c {
    private:
        end_effector_c *end_effector;
    public:
        /**
         * The constructor initializes:
         * base_module_c
         * the pointer to the end_effector
         * 
         * @param comm 
         * @param end_effector
         */
        module_c(base_comm_c &comm, end_effector_c *end_effector);
    
        /**
         * Let the module process data.
         */ 
        void process() override;
    };
}