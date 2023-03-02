#include <kipr/wombat.h>
#include <stdbool.h>
#define off_line 1700
#define on_line 1500
#define off_line_go_to 2000
#define on_line_go_to 1700

void turn_deg(int deg){
    if(deg>0){
        turncw();//turn positive degrees
        sleep(constant*deg);
    }
    else{
        turnccw();// turn negative degrees
        sleep(constant*(-deg));
    }//
// Created by jonas on 25.02.2023.
//
