#ifdef STANDALONE

#include <stdio.h>   // Standard input/output definitions
#include "position_controller.h"


int main(){
    Position_Controller p("/dev/ttyUSB1", 921600);

    chrono::milliseconds k(10000);
    this_thread::sleep_for(k);

    p.toggle_offboard_control(true);

    int i = 0;
    
    int x = 25;
    int y = 125;
    int z = 250;
    
    while (i < 5){
        i++;
        p.update_current_position(x + i*10, y+ i*10, z+ i*10, 0);
        p.update_desired_position(x + i*5, y+ i*5, z+ i*5, 0);
        chrono::milliseconds j(5000);
        this_thread::sleep_for(j);
    }

    p.toggle_offboard_control(false);

    p.shutdown();
    return 0;
}

#endif