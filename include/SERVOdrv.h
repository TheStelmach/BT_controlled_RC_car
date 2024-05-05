// https://github.com/TheStelmach

#ifndef SERVODRV_H
#define SERVODRV_H

#define SERVODATA DDB1 // DATA PIN
#define TIMERINTERRUPT (39999u)
#define MINANGLE (999u) //500 uSec
#define MAXANGLE (4999u) //2500 uSec
#define MIDANGLE (2999u) //1500 uSec
#define OFFSET (0u) //OFFSET VALUE FOR MANUAL CALIBRATION

void servo_init();
void angle_update(uint16_t angle, char dir);

#endif
