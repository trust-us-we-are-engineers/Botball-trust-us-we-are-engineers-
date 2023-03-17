#include <kipr/wombat.h>

/* storage for (small boy) functions

	motors		Pt 0 = left wheel
    			Pt 1 = right wheel                
                Pt 2 = lower shield
                
	servos		Pt 0 = higher shield
    			Pt 1 = left gripper
                Pt 2 = right gripper
                Pt 3 = liftable shield

	digitals	Pt 0 = large touch (back)
    			Pt 1 = light sensor
                Pt 2 = large touch (low right)
                Pt 3 = large touch (low left)
    
    analog		Pt 0 = right small tophat
    			Pt 1 = left small tophat
                Pt 2 = right big tophat
                Pt 3 = left big tohpat
*/

#define distance_turn5			55
#define distance_turn10			110
#define distance_turn20			220
#define distance_turn25			275
#define distance_turn30			330
#define distance_turn45			500
#define distance_turn50			550
#define distance_turn60			665
#define distance_turn75			830
#define distance_turn90			1000
#define distance_turn180		2000
#define distance_turn360		4000
#define distance_between_balls	2000

#define speed_forward			1200		
#define speed_backward			-1200		
#define speed_turn				1000
#define speed_sorting			500
#define speed_sorting_fast		400

#define black					1700

#define low_shield				800
#define high_shield				100

#define open_left_gripper		200
#define close_left_gripper		1500
#define open_right_gripper		1700
#define close_right_gripper		200

#define higher_shield_right		1900
#define higher_shield_left		370
#define higher_shield_middle	1080



void drive (int distance, int speed)	// forward/backward
{
    cmpc(0);
    
    while (abs(gmpc(0)) < distance)
    {
        mav(0,speed);
        mav(1,speed);
    }
    
    mav(0,0);
    mav(1,0);
    msleep(20);   
}


void backward_to_touch ()	// backward, til the touch has the value = 1
{
    while (digital(0) != 1)
    {
        mav(0,speed_backward);
        mav(1,speed_backward);
    }
    if (digital(0) == 1)   // when the touch value = 1, driving forward
    {
        mav(0,speed_forward);
        mav(1,speed_forward);
        msleep(200);        
    }   
}


void drive_to_line (int speed)		
{
     while (analog(0) < black || analog(1) < black)
        {
        if(analog(0) < black && analog(1) > black)		// slight right movement, to get on line
        {
        	mav(0,0);
        	mav(1,speed);
        	msleep(5);
        }
        else if(analog(1) < black && analog(0) > black)		// slight left movement, to get on line
        {
        	mav(0,speed);
        	mav(1,0);
        	msleep(5);
        }
        else 			// moving forward/backward, surching for a line
        {
        	mav(0,speed);
        	mav(1,speed);
        }
        msleep(5);
    }
    
    mav(0,0);
    mav(1,0);
    msleep(20);    
}


void turn_right (int distance)		
{
    cmpc(1);
    
    while (abs(gmpc(1)) < distance)
    {
        mav(0,speed_turn);
        mav(1,-speed_turn);       
    }
    
    mav(0,0);
    mav(1,0);
    msleep(20);
}  


void turn_left (int distance)
{
    cmpc(0);
    
    while (abs(gmpc(0)) < distance)
    {
        mav(0,-speed_turn);
        mav(1,speed_turn);       
    }
    
    mav(0,0);
    mav(1,0);
    msleep(20);
}


void lower_shield ()		// lowers shield (used that balls can't escape)
{
	enable_servo(3);
    
    while(get_servo_position(3) < low_shield) 
    {
        set_servo_position(3, low_shield);
        msleep(800);
    }
    
    disable_servos();
    
}

                       
void lift_shield ()			// lifts shield (used for startbox and sorting)
{
	enable_servo(3);
    
    while(get_servo_position(3) > high_shield) 
    {
        set_servo_position(3, high_shield);
        msleep(800);
    }
    
    disable_servo(3);
}


void open_gripper ()			// opens (back)gripper
{
	enable_servo(1);
    enable_servo(2);
    
    if(get_servo_position(1) > open_left_gripper || get_servo_position(2) < open_right_gripper) 
    {
        set_servo_position(1,open_left_gripper);
    	set_servo_position(2,open_right_gripper);
        
        msleep(1000);

    }
    
    disable_servos();
}


void close_gripper ()			// closes (back)gripper
{    
    enable_servo(1);
    enable_servo(2);
    
    if(get_servo_position(1) < close_left_gripper || get_servo_position(2) > close_right_gripper) 
    {
        set_servo_position(1,close_left_gripper);
    	set_servo_position(2,close_right_gripper);
        
        msleep(1000);
    }
    
    disable_servos();
}    


void close_gripper_by_touch () 			// (used for wireshark)
{
  	while (digital(0) != 1)
    {
        mav(0,speed_backward);
       	mav(1,speed_backward);
    }
    if (digital(0) == 1)   	// when the touch value = 1, closing gripper
    {
       	alloff();
        close_gripper();
        msleep(300);
    }   
}


void follow_line (int distance)
{
    cmpc(0);
    cmpc(1);
    
    while (abs(gmpc(0)) < distance && abs(gmpc(1)) < distance)
    {
		if(analog(2) > black && analog(3) > black)   // following the line, when both sensors on the line 
       	{
   	        mav(0,speed_forward);
   	       	mav(1,speed_forward);
            msleep(50);
       	}
       	else if(analog(2) > black && analog(3) < black)   // turning right, when right sensor on the line
       	{
           	mav(0,speed_turn);
            mav(1,-speed_turn);
           	msleep(50);
       	}
       	else if(analog(2) < black && analog(3) > black)   // turning left, when left sensor on the line
       	{
           	mav(0,-speed_turn);
            mav(1,speed_turn);
            msleep(50);
       	}
	   	else   // moving backwards, when no sensors on the line
       	{
            mav(0,speed_backward);
           	mav(1,speed_backward);
            msleep(50);        
       	}   
    }
    
    mav(0,0);
    mav(1,0);
    msleep(20);
}


void sorting_right ()			// higher shield - position right
{    
    enable_servo(0);
    
    while (digital(3) != 1) 
    {
    	mav(2,speed_sorting);
    	msleep(10);
        
    	if (get_servo_position != higher_shield_right)
    	{
			set_servo_position(0, higher_shield_right);
        	msleep(400);       
    	}
    } 
       	
    disable_servo(0);
}   


void sorting_left ()			// higher shield - position left
{    
    enable_servo(0);
    
    while (digital(2) != 1) 
	{
    	mav(2,-speed_sorting);
    	msleep(10);
        
        if (get_servo_position != higher_shield_left)
    	{
			set_servo_position(0, higher_shield_left);
        	msleep(400);       
    	}
    }
   	
    disable_servo(0);
}



void sorting_neutral ()			// shields go back to the middle
{
    if (get_servo_position < higher_shield_middle || digital(3) == 1)		// when latest sorting position was right
    {
        enable_servo(0);
        
        cmpc(2);  
        mtp(2,-speed_sorting,-340);  
        bmd(2);
        
        if (get_servo_position != higher_shield_middle)
    	{
			set_servo_position(0, higher_shield_middle);
        	msleep(800);       
    	}
        
        disable_servo(0);
   
    }
   	else if (get_servo_position > higher_shield_middle || digital(2) == 1)		// when latest sorting position was left
    {
        enable_servo(0);
        
        cmpc(2);
        mtp(2,speed_sorting,340); 
        bmd(2);
        
        if (get_servo_position != higher_shield_middle)
    	{
			set_servo_position(0, higher_shield_middle);
        	msleep(800);       
    	}
        
        disable_servo(0);
    }   
}    


void start ()			// moves servos and motors, to get the robot in the right mood for the starting box 
{ 
    sorting_left();			// to get a reference point
    sorting_neutral();
    lift_shield();
    open_gripper();		
}    




int main()
{
/*    start();
    backward_to_touch();
    turn_left(distance_turn5);
    sorting_left();
    drive(1400,speed_forward);
	sorting_right();
    backward_to_touch();
    turn_right(distance_turn10);
    drive_to_line(speed_forward);
    drive(600, speed_forward);
    lower_shield();
    turn_right(distance_turn90);
    sorting_left();
    lift_shield();
    drive(2000, speed_forward);
*/
    
	return 0;
}

