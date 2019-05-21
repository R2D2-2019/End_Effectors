#include <module.hpp>
    
namespace r2d2::end_effectors {
    module_c::module_c(base_comm_c &comm, end_effector_c *end_effector) 
        : base_module_c(comm), end_effector(end_effector) {
            comm.listen_for_frames(
                { frame_type::ALL }
            );
        }

    void module_c::process() {
        while (comm.has_data()) {
            auto frame = comm.get_data();
            //process the frame

            if (end_effector != nullptr) {

            }
        }
    }
}