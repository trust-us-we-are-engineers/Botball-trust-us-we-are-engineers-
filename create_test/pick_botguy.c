#include <kipr/wombat.h>
#include <stdbool.h>
#include <time.h>
#define off_line 1700
#define on_line 1600
#define off_line_go_to 1800
#define on_line_go_to 1600
#define turn_constant 17.8
void gripper_open(){//opening the gripper
    enable_servo(1);
    set_servo_position(1,547);
    msleep(1500);

}
void gripper_close(){//closing the gripper
    enable_servo(1);
    set_servo_position(1,1600);
    msleep(1500);


}

void move_gripper_to_0(){
    mav(0,600);
    while(digital(0)!=1){

        msleep(1);
    }
    off(0);
    cmpc(0);

}
void turn_deg(int deg){// standard function
    int speed=100;
    if(deg>0){
        create_spin_CW(speed);
        msleep(turn_constant*deg);
    }
    else{
        create_spin_CCW(speed);
        msleep((-turn_constant)*deg);
    }
}
void drive_until_line(){// standard function
    int speed=100;
    int sleep_time=25;
    while(!(get_create_lcliff_amt()<on_line_go_to && get_create_rcliff_amt()<on_line_go_to)){
        if(get_create_lcliff_amt()<on_line_go_to){
            create_spin_CCW(speed);
            msleep(sleep_time/3);
            create_drive_straight(-speed);
            msleep(sleep_time/6);
        }
        if(get_create_rcliff_amt()<on_line_go_to){
            create_spin_CW(speed);
            msleep(sleep_time/3);
            create_drive_straight(-speed);
            msleep(sleep_time/6);
        }
        else{
            create_drive_straight(speed);
            msleep(sleep_time/4);
        }
    }}

void follow_line_until(int time,bool left,int how_often){// standard function
    int speed=200;
    bool exit=false;
    while(!exit){
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
        if(get_create_lcliff_amt()<on_line && left){
            printf("hs");
            create_drive_straight(speed);
            msleep(time);
            exit=true;
        }

        if(get_create_rcliff_amt()<on_line && !left){


            create_drive_straight(speed);
            msleep(time);
            exit=true;
        }
    }





}
void follow_line(int time_m){
    int speed=200;
    double time=time_m/1000;
    get_create_lfcliff_amt();
    get_create_rfcliff_amt();
    double start_time=seconds();
    while((seconds()-start_time)<time){


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
        msleep(speed*0.1);


    }
}
void follow_line_l(int time_m){// standard follow line adapted to stop when the black tape is reached
    int speed=200;
    double time=time_m/1000;
    get_create_lfcliff_amt();
    get_create_rfcliff_amt();
    double start_time=seconds();
    while((seconds()-start_time)<time){


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
        msleep(speed*0.1);
        if(get_create_lcliff_amt()<on_line){//no good coding practise change
            msleep(200);
            break;
        }
    }
}
int main()
{
    create_connect();
    printf("1 %d \n",get_create_lcliff_amt());

    printf("2 %d \n",get_create_lfcliff_amt());

    printf("3 %d \n",get_create_rfcliff_amt());

    printf("4 %d \n",get_create_rcliff_amt());

    move_gripper_to_0();
    follow_line_l(44400);
    turn_deg(-90);
    follow_line(1000);
    turn_deg(180);
    drive_until_line();
    create_drive_straight(-200);
    msleep(400);
    create_stop();
    mtp(0,200,-5500);// make a function for gripper movement
    bmd(0);
    gripper_open();
    create_drive_straight(-200);
    msleep(1100);
    create_stop();
    gripper_close();
    turn_deg(180);

    create_disconnect();


    return 0;
}
