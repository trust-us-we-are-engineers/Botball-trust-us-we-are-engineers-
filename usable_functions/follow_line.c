void follow_line(int time){ //time it should follow
    int speed=300;
    get_create_lfcliff_amt();//just for testing purposes
    get_create_rfcliff_amt();
    double start_time=seconds()*1000;
    while((seconds()-start_time)>time){ //while time is not reached

        if(get_create_lfcliff_amt()>off_line && get_create_rfcliff_amt()<on_line){//turn clockwise and drive
                                                                                 // when left middel sensor is on the line
            create_spin_CW(speed);
            msleep(speed*0.1);
            create_drive_straight(speed);
        }
        else if(get_create_rfcliff_amt()>off_line &&  get_create_lfcliff_amt()<on_line){//turn against the clock and drive backwards
                                                                                        //when right middel sensor is on the line
            create_spin_CCW(speed);
            msleep(speed*0.1);
            create_drive_straight(speed);
        }
        else{// when no sensor is on the line
            create_drive_straight(speed);

        }
        msleep(speed*0.2);// time driven
    }
}