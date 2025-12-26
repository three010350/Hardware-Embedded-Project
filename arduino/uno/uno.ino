#define MQ_7 A0
#define MQ_4 A1
#define buzzer 7
#define MH_Tx 5
#define MH_Rx 4

float analysis_co(int);
float analysis_ch4(int);
float Rs;
float Rt;

#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial UnoSerial(3, 2); // RX | TX
SoftwareSerial MH_Z14a(MH_Rx, MH_Tx);
void setup()
{
  //pinMode(3, INPUT);
  //pinMode(2, OUTPUT);
  UnoSerial.begin(57600);
  
  Serial.begin(9600);

  MH_Z14a.begin(9600);
  pinMode(MH_Rx, INPUT);
  pinMode(MH_Tx, OUTPUT);
  byte cmd[9] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x13, 0x88, 0x8F};   //Detection range 5000pmm
  //byte cmd[9] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x07, 0xD0, 0x8F}; //Detection range 2000pmm
  //byte cmd[9] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x27, 0x10, 0x2F}; //Detection range 10,000pmm
  MH_Z14a.write(cmd, 9);

  
  pinMode(buzzer, OUTPUT);
  lcd.begin();
  lcd.backlight();
}
void loop() {
  lcd.begin();
  lcd.backlight();
  digitalWrite(buzzer,HIGH);
  /*Serial.print("hello world");
  UnoSerial.print(i_data);
  UnoSerial.print(" ");
  UnoSerial.print(f_data);
  UnoSerial.print("\n");
  delay(100);*/
  /////////////////////
  int coLevel = analogRead(MQ_7);
  float coPPM=analysis_co(coLevel);
  Serial.print("Carbon monoxide : ");
  Serial.print(coPPM, 2);
  Serial.println("ppm");
  UnoSerial.print(coPPM);
  UnoSerial.print("\n");

  int ch4Level = analogRead(MQ_4);
  float ch4PPM = analysis_ch4(ch4Level);
  Serial.print("Methane gas : ");
  Serial.print(ch4PPM, 2);
  Serial.println("ppm");
  UnoSerial.print(ch4PPM);
  UnoSerial.print("\n");
  /////////////////////////////
  int CO2 = mh_Z14A_function();
  Serial.print("CO2 : ");
  Serial.print(CO2);
  Serial.println("ppm");
  UnoSerial.print(CO2);
  UnoSerial.print("\n");
  //delay(3000);// heat time 3minut
  lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print("CO2:"); //พิมพ์ข้อความ

  lcd.setCursor(4, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print(CO2); //พิมพ์ข้อความ
  ////////////////////////////////////
  lcd.setCursor(9, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print("CO:"); //พิมพ์ข้อความ
  
  lcd.setCursor(12, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print(coPPM); //พิมพ์ข้อความ
  ////////////////////////////////////
  lcd.setCursor(0, 1); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print("CH4:"); //พิมพ์ข้อความ

  lcd.setCursor(4, 1); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print(ch4PPM); //พิมพ์ข้อความ
  //////////////////////////////
  /*if(sensorValue < 195){
    digitalWrite(buzzer,HIGH);
    Serial.println("Buzzer status : ON");
    delay(1000);
    digitalWrite(buzzer,LOW);
    Serial.println("Buzzer status : OFF");
    delay(1000);
  }*/
  if(coPPM > 2000 || CO2 >1400 || ch4PPM>1000)
  {
  lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print("toxic management"); //พิมพ์ข้อความ
  Serial.println("toxic");

  lcd.setCursor(0, 1);
  lcd.print("is required");

  /*digitalWrite(buzzer,LOW);
  delay(1000);*/
  digitalWrite(buzzer,HIGH);
  }
  Serial.print("\n");
  delay(1000);
}

int mh_Z14A_function(){
  byte Z14a[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; //Read CO2
  MH_Z14a.write(Z14a, 9);
  
  byte data_byte[9];

  if(MH_Z14a.available()>0)
  {
    MH_Z14a.readBytes(data_byte, 9);
  }

  if(data_byte[1] == 1){
    return 0;
  }
  else{
    int CO2_ppm = data_byte[2]*256+data_byte[3];
    return CO2_ppm;
  }
}

float xxx;

float analysis_co(int adc){
  float slope = -0.3384580239;
  float A = 10.36034152;
  float Rseries = 1000;
  float V_Rseries = ((float)adc*5)/1023;
  xxx =((5-V_Rseries)/V_Rseries)*Rseries;
  float R0 = 1809.52;
  /*
   * R0 คือ ค่าความต้านทานเซ็นเซอร์ขณะที่แก๊สมีเทนเท่ากับ 1000 ppm
   * ในอากาศที่สะอาด
   * ควรปรับจูนด้วยการสอบเทียบกับเซ็นเซอร์มาตรฐาน
   */
  float Y = xxx/R0;
  float Methane_gas = pow(10,(log10(Y/A)/slope));
  return Methane_gas;
}

float analysis_ch4(int adc){
  float slope = -0.3384580239;
  float A = 10.36034152;
  float Rseries = 1000;
  float V_Rseries = ((float)adc*5)/1023;
  Rt = ((5-V_Rseries)/V_Rseries)*Rseries;
  float R0 = 1809.52;
  /*
   * R0 คือ ค่าความต้านทานเซ็นเซอร์ขณะที่แก๊สมีเทนเท่ากับ 1000 ppm
   * ในอากาศที่สะอาด
   * ควรปรับจูนด้วยการสอบเทียบกับเซ็นเซอร์มาตรฐาน
   */
  float Y = Rt/R0;
  float Methane_gas = pow(10,(log10(Y/A)/slope));
  return Methane_gas;
}