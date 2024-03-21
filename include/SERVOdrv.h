#ifndef SERVODRV_H
#define SERVODRV_H

#define SERVODATA DDB1 // DATA PIN
#define TIMERINTERRUPT (39999u)
#define MINANGLE (999u) //500 uSEC
#define MAXANGLE (4999u) //2500 uSEC
#define MIDANGLE (2999u) //1500 uSEC
#define OFFSET (0u) //OFFSET VALUE FOR MANUAL CALIBRATION

void servo_init();
void angle_update(uint16_t angle, char dir);

#endif