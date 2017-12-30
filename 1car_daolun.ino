#include <Microduino_Motor.h>
#include <U8glib.h>
#define INTERVAL_LCD 

Motor MotorLeft(MOTOR0_PINA, MOTOR0_PINB);
Motor MotorRight(MOTOR1_PINA, MOTOR1_PINB);

const int TrigPin =A0; 
const int EchoPin=A1;
float cm; 

unsigned long lcd_time = millis();                 //OLED刷新时间计时器
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);     //设置OLED型号  
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
/*#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_fub25n)*/
void setup()
{
  Serial.begin(9600);
 // Serial.println("Microduino_Motor!");

  MotorLeft.begin();
  MotorRight.begin();

  pinMode(TrigPin, OUTPUT); 
pinMode(EchoPin, INPUT); 
}

void loop()
{
  Serial.println(analogRead(A6));
  Serial.println(analogRead(A2));
  int sensorValueR = analogRead(A6);
  int sensorValueL = analogRead(A2);
  // print out the value you read:
  //Serial.println(sensorValueR);
  //Serial.println(sensorValueL);
  delay(500);        // delay in between reads for stability


//发一个10ms的高脉冲去触发TrigPin 
digitalWrite(TrigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(TrigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(TrigPin, LOW); 
 
cm = pulseIn(EchoPin, HIGH) / 58.0; //算成厘米 
cm = (int(cm * 100.0)) / 100.0; //保留两位小数 
Serial.print(cm); 
Serial.print("cm"); 
if(cm<10)
{

Serial.println("Break!");
  MotorLeft.setSpeed(90);
  MotorRight.setSpeed(90);
  delay(100);
}
 else
 {
  if((sensorValueR>200)&&(sensorValueL>200))
 
{
    Serial.println("Forward!");
    MotorLeft.setSpeed(90);
    MotorRight.setSpeed(90);
    delay(1);
  }

else if((sensorValueR<200)&&(sensorValueL>200))
{
  Serial.println("zuo zhuan");
  MotorLeft.setSpeed(90);
  MotorRight.setSpeed(120);
  delay(1);
}
else if((sensorValueL<200)&&(sensorValueR>200))
{
  Serial.println("you zhuan");
   MotorLeft.setSpeed(120);
  MotorRight.setSpeed(90);
  //MotorLeft.Brake();
  //MotorRight.Brake();
  delay(1);
  }
else if((sensorValueL<200)&&(sensorValueR<200))
{
   Serial.println("back");
  MotorLeft.setSpeed(-90);
  MotorRight.setSpeed(-90);
  delay(1);
 }
 /*else
{ 
  Serial.println("Free!");
  MotorLeft.setSpeed(FREE);
  MotorRight.setSpeed(FREE);
  delay(1);
}*/ 
u8g.firstPage();
do {
        setFont_L;
        u8g.setPrintPos(0 ,10);
        u8g.print(sensorValueR ,sensorValueL);
        u8g.print(cm);
        u8g.print("cm");
        
    }while( u8g.nextPage() );
}
}
 /*Serial.println("Free!");
  MotorLeft.setSpeed(FREE);
  MotorRight.setSpeed(FREE);
  delay(2000);
} */
