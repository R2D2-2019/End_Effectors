#include <module.hpp>
    
namespace r2d2::end_effectors {
    void module_c::process(){
        while(comm.has_data()){
            auto frame = comm.get_data();
            //process the frame
        }
    }
}