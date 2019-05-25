#include <module.hpp>
#include <claw.hpp>

namespace r2d2::end_effectors {
    module_c::module_c(base_comm_c &comm, end_effector_c *end_effector) 
        : base_module_c(comm), end_effector(end_effector) {
            if(end_effector == nullptr){
                return;
            }
            switch(end_effector->get_type()){
                case end_effector_type::CLAW:
                    comm.listen_for_frames(
                        { frame_type::END_EFFECTOR_CLAW }
                    );
                break;
                default:
                    comm.listen_for_frames(
                        { frame_type::NONE }
                    );
                break;
            }
        }

    void module_c::process() {
        while (comm.has_data()) {
            auto frame = comm.get_data();
            //process the frame

            if(frame.request) {
                continue;
            }

            if (end_effector == nullptr) {
                continue;
            }

            switch(end_effector->get_type()){
                case end_effector_type::CLAW:
                    auto claw = dynamic_cast<claw_c*>(end_effector);
                    const auto close = frame.as_frame_type<
                        frame_type::END_EFFECTOR_CLAW
                    >().close;
                    if(close){
                        claw->close();
                    } else {
                        claw->open();
                    }
                break;
                default:
                
                break;
            }
        }
    }
}