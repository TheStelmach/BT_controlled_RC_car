#ifndef SERVODRV_H
#define SERVODRV_H

#define SERVODATA DDB1 // DATA PIN
#define TIMERINTERRUPT (19999u)
#define MINANGLE (499u) //500 uSEC
#define MAXANGLE (2499u) //2500 uSEC
#define MIDANGLE (1499u) //1500 uSEC
#define OFFSET (0u) //OFFSET VALUE FOR MANUAL CALIBRATION

void servo_init();

#endif