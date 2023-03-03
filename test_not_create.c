#include <kipr/wombat.h>

/*		 motors for the wheels on Pt 0 & 1
		 motor for the lifting function on Pt 2
         small servo on Pt 0
		 tophat on Pt 2 & 3
         small tophat on Pt 0 & 1
         large touch on Pt 0
*/

#define Threshold_right			3000	// analog Pt 0
#define Threshold_m_right		3000	// analog Pt 2
#define Threshold_m_left		3000 	// analog Pt 3
#define Threshold_left			3000	// analog Pt 1	

#define V_Standard				1200	// speed of the robot for driving (forward, backward)
#define V_on_Line 				1200	// speed of the robot for "follow the line"
#define V_touch_Line 			850		// speed for surching the line
#define V_turn 					1000	// speed of the robot for turning (left, right) 

#define Samplingrate_Line 		100		// samplingrate of the robot for "follow the line"
#define Samplingrate_Standard	50		// samplingrate of the robot for driving (forward, backward)
#define Samplingrate_Turn90		1000	// samplingrate of the robot for turning (left, right)
#define Samplingrate_Turn45		500		// samplingrate of the robot for turning (left, right)

void backward()    
{
	while (digital(0) == 0)   // driving backwards until digital Pt 5 has the value = 1
    {
        msleep(Samplingrate_Standard);  
        mav(0,-V_Standard);
        mav(1,-V_Standard);
    }
    
    if (digital(0) == 1)   // when digital Pt 5 has the value = 1, driving forward
    {
        mav(0,V_Standard);
        mav(1,V_Standard);
        msleep(600);        
    }
}

void forward_til_line()
{
       while(analog(2) < 3000 && analog(3) < 3000)   // driving forward until analog Pt 2 & 3 have the value < 3000
       { 
        	msleep(Samplingrate_Standard);
			mav(0,V_Standard);
        	mav(1,V_Standard);
       }
}

void turn90left()   // ca. 90B0 turn to the left
{
    mav(0,-V_turn);
    mav(1,V_turn);
    msleep(Samplingrate_Turn90);
}

void turn45left()   // ca. 45B0 turn to the left
{
    mav(0,-V_turn);
    mav(1,V_turn);
    msleep(Samplingrate_Turn45);
}

void turn90right()   // ca. 90B0 turn to the right
{
    mav(0,V_turn);
    mav(1,-V_turn);
    msleep(Samplingrate_Turn90);
}

void straight_on_Line()   // follow the line code
{
    int exiter = 0;

    while(exiter == 0)
   	{    
		if(analog(2) > Threshold_m_right && analog(3) > Threshold_m_left)   // following the line, when both sensors on the line 
       	{
   	        mav(0,V_on_Line);
   	        mav(1,V_on_Line);
            msleep(Samplingrate_Line);
       		alloff();
       }
       else if(Threshold_m_right < analog(2) && Threshold_m_left > analog(3))   // turning right, when right sensor on the line
       {
           mav(0,850);
           msleep(Samplingrate_Turn90);
       }
       else if(Threshold_m_right > analog(2) && Threshold_m_left < analog(3))   // turning left, when left sensor on the line
       {
           mav(1,850);
           msleep(Samplingrate_Turn90);
       }
	   else // (Threshold_m_right > analog(2) && Threshold_m_left > analog(3))   // driving backwards, when no sensors on the line
       {
           mav(0,-V_on_Line);
           mav(1,-V_on_Line);
           msleep(Samplingrate_Line);
           alloff();
       }    
   }                 
}



int main()
{ 
    backward();
    turn90left();
    backward();
    turn90right();
    forward_til_line();
    turn45left();
    
   	straight_on_Line();

    alloff();
    return 0;
}



