#include <module.hpp>
#include <claw.hpp>

namespace r2d2::end_effectors {
    /*module_c::module_c(base_comm_c &comm, end_effector_c *end_effector) 
        : base_module_c(comm), end_effector(end_effector) {
            if(end_effector != nullptr){
                end_effector->set_listen_frame_types(comm);
                comm.listen_for_frames(
                    { frame_type::END_EFFECTOR_TYPE }
                );
            }else{
                comm.listen_for_frames(
                    { frame_type::NONE }
                );
            }
        }

    void module_c::process() {
        if(end_effector != nullptr){
            end_effector->process(comm);
        } else {
            while (comm.has_data()) {
                auto frame = comm.get_data();
                if(frame.request && frame.type == frame_type::END_EFFECTOR_TYPE) {
                    frame_end_effector_type_s ee_type;
                    ee_type.type = end_effector_type::NONE;
                    comm.send(ee_type);
                }
            }
        }
    }*/
}