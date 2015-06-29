
void stash()
{

rollers (127,700);
wait1Msec(1000);

	SensorValue[rDrive]=0;
	SensorValue[lDrive]=0;

//liftTime(127,2000);

liftDown(1000,127);                            //lift
lift(30);

bar(1);                                     //fling

driving(700,127,127);                      //1st ball
rollers(-127,700);
wait1Msec(500);
driving(750,-127,-127);

wait1Msec(2000);

driving(600,127,127);
bar(0);                                   //pull in
driving(300,127,127);
driving(900,-127,-127);

liftDown(-127,0);

wait1Msec(2000);

driving(700,127,127);
driving(700,-127,-127);

wait1Msec(8000);
/*
drivingRolling(200,127,127,127);
driving(300,127,127);

lifting(127,48);

driving(100,127,127);

rollers(127,1000);

driving(600,-127,-127);

wait1Msec(1500);
*/


}
