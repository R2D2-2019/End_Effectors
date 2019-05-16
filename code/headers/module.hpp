#pragma once

#include <base_module.hpp>

namespace r2d2::end_effectors {
    class module_c : public base_module_c {
    public:
        /**
         * @param comm 
         */
        module_c(base_comm_c &comm)
            : base_module_c(comm) {
            comm.listen_for_frames(
                {frame_type::ALL}

            );
        }
    
        /**
         * Let the module process data.
         */ 
        void process() override;
    };
}