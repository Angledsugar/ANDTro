#include <DynamixelWorkbench.h>
#include <IMU.h>

#define BAUDRATE              57600
#define BAUDRATE_TO_DXL     1000000
#define LEFT_FRONT_ID             1
#define RIGHT_FRONT_ID            2
#define LEFT_BACK_ID              3
#define RIGHT_BACK_ID             4 

DynamixelWorkbench dxl_wb;
cIMU IMU;

uint8_t   err_code;
uint8_t   led_tog = 0;
uint8_t   led_pin = 13;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(BAUDRATE);
    //while(!Serial); // Open a Serial Monitor
    IMU.begin();
    pinMode( 22, OUTPUT );
    pinMode( 23, OUTPUT );
    pinMode( 24, OUTPUT );
    pinMode( 25, OUTPUT );
    dxl_wb.begin("", BAUDRATE_TO_DXL);
    dxl_wb.ping(LEFT_FRONT_ID);
    dxl_wb.ping(RIGHT_FRONT_ID);
    dxl_wb.ping(LEFT_BACK_ID);
    dxl_wb.ping(RIGHT_BACK_ID);

    dxl_wb.wheelMode(LEFT_FRONT_ID);
    dxl_wb.wheelMode(RIGHT_FRONT_ID);
    dxl_wb.wheelMode(LEFT_BACK_ID);
    dxl_wb.wheelMode(RIGHT_BACK_ID);
}

void loop() {
  static uint32_t tTime[3];
  static uint32_t imu_time = 0;
  
  if( (millis()-tTime[0]) >= 500 )
  {
    tTime[0] = millis();

    digitalWrite( led_pin, led_tog );
    led_tog ^= 1;
  }

  tTime[2] = micros();
  if( IMU.update() > 0 ) imu_time = micros()-tTime[2];



  if( (millis()-tTime[1]) >= 50 )
  {
    tTime[1] = millis();

    /*Serial.print(imu_time);
    Serial.print(" ");
    Serial.print(IMU.rpy[0]);
    Serial.print(" ");
    Serial.print(IMU.rpy[1]);
    Serial.print(" ");
    Serial.println(IMU.rpy[2]);*/
  }
  
  if(Serial.available()){
    char c = Serial.read();
    
    if( c == 'w'){ //Go
      digitalWrite(22, LOW);
      //delay(500);
      //go();
    }

    else if( c == 'x'){ //Back
      digitalWrite(23, LOW);
      //delay(500);
      //back();
    }

    else if( c == 'a'){ //Left
      digitalWrite(24, LOW);
      Serial.print("A\n");
      //delay(500);
      //left();
    }

    else if( c == 'd'){ //Right
      digitalWrite(25, LOW);
      //delay(500);
      //right();
    }
    
    else if( c == 's'){ //Stops
      //c = '0';
      Serial.print("Stop\n");
      digitalWrite(22, HIGH);
      digitalWrite(23, HIGH);
      digitalWrite(24, HIGH);
      digitalWrite(25, HIGH);
      //delay(500);
      //stops();
    }
  }
}

void go() {
    dxl_wb.goalVelocity(LEFT_FRONT_ID, 150);
    dxl_wb.goalVelocity(RIGHT_FRONT_ID, -150);
    dxl_wb.goalVelocity(LEFT_BACK_ID, 150);
    dxl_wb.goalVelocity(RIGHT_BACK_ID, -150);
    delay(2000);
}

void back(){
    dxl_wb.goalVelocity(LEFT_FRONT_ID, -150);
    dxl_wb.goalVelocity(RIGHT_FRONT_ID, 150);
    dxl_wb.goalVelocity(LEFT_BACK_ID, -150);
    dxl_wb.goalVelocity(RIGHT_BACK_ID, 150);
    delay(2000);
}

void right(){
    // put your main code here, to run repeatedly:
    dxl_wb.goalVelocity(LEFT_FRONT_ID, 150);
    dxl_wb.goalVelocity(RIGHT_FRONT_ID, 150);
    dxl_wb.goalVelocity(LEFT_BACK_ID, -150);
    dxl_wb.goalVelocity(RIGHT_BACK_ID, -150);
    delay(2000);
}

void left(){
    // put your main code here, to run repeatedly:
    dxl_wb.goalVelocity(LEFT_FRONT_ID, -150);
    dxl_wb.goalVelocity(RIGHT_FRONT_ID, -150);
    dxl_wb.goalVelocity(LEFT_BACK_ID, 150);
    dxl_wb.goalVelocity(RIGHT_BACK_ID, 150);
    delay(2000);
}

void stops(){
    // put your main code here, to run repeatedly:
    dxl_wb.goalVelocity(LEFT_FRONT_ID, 0);
    dxl_wb.goalVelocity(RIGHT_FRONT_ID, 0);
    dxl_wb.goalVelocity(LEFT_BACK_ID, 0);
    dxl_wb.goalVelocity(RIGHT_BACK_ID, 0);
    delay(2000);
}

//bool goalVelocity(uint8_t id, float velocity, const char **log = NULL);
//bool wheelMode(uint8_t id, int32_t acceleration = 0, const char **log = NULL);
