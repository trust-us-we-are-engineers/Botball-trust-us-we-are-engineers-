void follow_line_until(int time,bool left,int how_often){// time driven after the last linecrossing,
                                                        // if the left or the right sensor should be checked,
                                                        // how much lines should be crossed
    int speed=300;
    bool exit=false;
    int counter=0;
    while(exit){
        if(get_create_lcliff_amt()<on_line && left){// if outer left sensor activates
            counter++;
            if (counter==how_often){// if line-count is reached
                create_drive_straight(speed);
                msleep(time);
                exit=true;
            }
        }
        if(get_create_rcliff_amt()<on_line && !left){//if outer left sensor activates
            counter++;

            if (counter==how_often){// if line-count is reached
                create_drive_straight(speed);
                msleep(time);
                exit=true;
            }
        }
        //follow the line code
        if(get_create_lfcliff_amt()>off_line && get_create_rfcliff_amt()<on_line){
            create_spin_CW(speed);
            msleep(speed*0.1);
            create_drive_straight(speed);
        }
        else if(get_create_rfcliff_amt()>off_line &&  get_create_lfcliff_amt()<on_line){
            create_spin_CCW(speed);
            msleep(speed*0.1);
            create_drive_straight(speed);
        }
        else{
            create_drive_straight(speed);

        }



    }}
