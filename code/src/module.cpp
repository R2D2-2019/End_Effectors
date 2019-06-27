#include <module.hpp>
#include <claw.hpp>

namespace r2d2::end_effectors {
    module_c::module_c(base_comm_c &comm, end_effector_c &end_effector) 
        : base_module_c(comm), end_effector(end_effector) {
            end_effector.set_listen_frame_types(comm);
            comm.listen_for_frames(
                { frame_type::END_EFFECTOR_TYPE }
            );
        }

    void module_c::process() {
        end_effector.process(comm);
    }
}