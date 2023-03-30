void drive_until_line(){
    int speed=300;
    int sleep_time=25;
    while(!(get_create_lcliff_amt()<on_line_go_to && get_create_rcliff_amt()<on_line_go_to)){// while both sensors are not on a black line
        if(get_create_lcliff_amt()<on_line_go_to){//turn clockwise and drive backwards
                                                  //when left outer sensor is on the line
            create_spin_CCW(speed);
            msleep(sleep_time/3);
            create_drive_straight(-speed);
            msleep(sleep_time/6);
        }
        if(get_create_rcliff_amt()<on_line_go_to){//turn against the clock and drive backwards
                                                  //when right outer sensor is on the line
            create_spin_CW(speed);
            msleep(sleep_time/3);
            create_drive_straight(-speed);
            msleep(sleep_time/6);
        }
        else{// when no sensor is seeing no black drive forward
            create_drive_straight(speed);
            msleep(sleep_time/4);
        }
    }}
