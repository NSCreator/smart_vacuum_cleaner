#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <FastLED.h>
#include <IRremote.h>

#define BLYNK_PRINT Serial
#define OLED_RESET         4
#define R_channel          0  
#define G_channel          1  
#define B_channel          2  
#define pwm_Frequency   5000 // pwm frequency  
#define pwm_resolution     8 // 8 bit resolution

#define sensor1       27
#define sensor2       18
#define wheels_led    14
#define front_led     19
#define buzzer        26
#define input1_pb     35
#define input2_IR     34
#define LEDG          33
#define LEDR          32
#define LEDB          25
#define bluetooth      5
#define motor         16
#define LED_PIN       17
#define NUM_LEDS       3 

#define RXp2 3
#define TXp2 1
 
int temp1,motor_app_data, bt_app_data, Front_rgb_led_app_data, Front_led_app_data, wheels_led_app_data,qwe,temp;
int b2=0,r, g, b, x, y, z,b1=0, sensor1_d, sensor2_d, motor_on_off_data, bt_out_data, wifi_inp, disp_inp, c, c_app;
char rC;
char auth[] = "xkevKTbSwiAfFTw3ooO5tUlpUyn_CRu5";  //Authentication Code sent by Blynk to Mail ID
char ssid[]="Sujith";
char pass[]="12345678";
String s_1_inp, s_2_inp, motor_s_app_data, BT__data_inp, terminal_out_data;
String Front_led_s_data, wheels_led_s_data, rgbb_d_inp, rgbf_d_inp;
bool pb; 
uint8_t hue = 0;

WidgetTerminal terminal(V1);
Adafruit_SSD1306 display( 128, 64, &Wire, OLED_RESET);
CRGB leds[NUM_LEDS];

const unsigned char myBitmap [] PROGMEM = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xfc, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xe0, 0x0f, 0x9f, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xf0, 0x0f, 0x9f, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xf0, 0x0f, 0x9f, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xf8, 0x0f, 0x9e, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xf8, 0x0f, 0x9c, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xfc, 0x0f, 0x98, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xfe, 0x0f, 0x98, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xfe, 0x0f, 0x98, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xdf, 0x0f, 0x98, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xcf, 0x0f, 0x88, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xcf, 0x8f, 0x8a, 0x7e, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xc7, 0xcf, 0x02, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xc7, 0xce, 0x20, 0xff, 0xc0, 0x1f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xc3, 0xee, 0x38, 0x7f, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xc3, 0xe3, 0x20, 0x0f, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xc1, 0xf3, 0xc0, 0x07, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xc0, 0xd3, 0x80, 0x03, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xc0, 0x12, 0x00, 0x03, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xc0, 0x2e, 0x18, 0x03, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xc0, 0x1c, 0x1c, 0x07, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xc0, 0x03, 0x1f, 0xbf, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xc0, 0x1f, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xc0, 0x1f, 0x1f, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xc0, 0x0f, 0x1f, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x0f, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void setup() {
  pinMode( sensor1,   OUTPUT);
  pinMode( sensor2,   OUTPUT);
  pinMode( wheels_led,OUTPUT);
  pinMode( front_led, OUTPUT);
  pinMode( buzzer,    OUTPUT);
  pinMode( bluetooth, OUTPUT);
  pinMode( motor,     OUTPUT);
  pinMode( input1_pb,  INPUT);
  pinMode( input2_IR,  INPUT);
  pinMode( LEDR,      OUTPUT);
  pinMode( LEDG,      OUTPUT);
  pinMode( LEDB,      OUTPUT);
  digitalWrite( sensor1, 1);
  digitalWrite( sensor2, 1);
  WiFi.begin( ssid, pass); 
  Blynk.config( auth );  //WIFI Name and Password
  FastLED.addLeds<WS2812B, LED_PIN, GRB>( leds, NUM_LEDS);
  FastLED.setBrightness( 100 );

  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  ledcAttachPin( LEDR, R_channel);  
  ledcAttachPin( LEDG, G_channel);  
  ledcAttachPin( LEDB, B_channel);   
  ledcSetup( R_channel, pwm_Frequency, pwm_resolution);  
  ledcSetup( G_channel, pwm_Frequency, pwm_resolution);  
  ledcSetup( B_channel, pwm_Frequency, pwm_resolution);
  
  Front_led_s_data="OFF"; wheels_led_s_data="OFF"; rgbb_d_inp="OFF"; rgbf_d_inp="OFF";
  s_1_inp="OFF"; s_2_inp="OFF"; motor_s_app_data="OFF"; BT__data_inp="OFF"; c=0;
  Front_rgb_led_app_data = 1;qwe=1,temp=9;
  if(!display.begin( SSD1306_SWITCHCAPVCC, 0x3C ))  // Address 0x3C for most of these displays, if doesn't work try 0x3D
  { Serial.println( F( "SSD1306 allocation failed" )); for(;;); }
  
  display.clearDisplay(); //for Clearing the display
  display.setTextColor( SSD1306_WHITE );
  display.drawBitmap( 0, 0, myBitmap, 128, 64, WHITE);  
  // display.drawBitmap( x position, y position, bitmap data, bitmap width, bitmap height, color);
  display.display();
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(300);
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(300);
  display.clearDisplay();
  delay(2500);
  display.setCursor( 15, 18); display.setTextSize(2);            
  display.print(F("NS Ideas"));
  display.setCursor( 21, 43); display.setTextSize(1);            
  display.print(F("...Presents..."));
  display.display(); 
  delay(2000);
  display.clearDisplay();
  display.setCursor( 34, 1); display.setTextSize(2);            
  display.print(F("SMART"));
  display.setCursor( 27, 23); display.setTextSize(2);   
  display.print(F("VACCUM"));
  display.setCursor( 21, 44); display.setTextSize(2);   
  display.print(F("CLEANER"));
  display.display();
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(3000);
  display.clearDisplay();
  display.setCursor( 5, 5); display.setTextSize(1);            
  display.print(F("Initializing......"));
  display.setCursor( 27, 22); display.setTextSize(1);            
  display.print(F("Arduino Nano"));
  display.setCursor( 30, 32); display.setTextSize(1);            
  display.print(F("All Sensors"));
  display.setCursor( 21, 42); display.setTextSize(1);            
  display.print(F("WI-FI Settings"));
  display.setCursor( 8, 52); display.setTextSize(1);            
  display.print(F("Bluetooth Settings"));
  display.display();
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0); 
  delay(1500);   
  display.clearDisplay();
  display.setCursor( 0, 20); display.setTextSize(1);            
  display.print(F("Calculating gyro offset, do not move MPU6050 or VACCUM CLEANER"));
  display.display();
  delay(2000);
}
void menu( int mode_disp_data){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor( 30, 0);
  display.print("Select Mode"); 
  if ( mode_disp_data == 0 ) { display.setCursor( 5, 14); display.print(">>  Rest"); } 
  else { display.setCursor( 30, 14); display.print("Rest"); }
  if ( mode_disp_data == 1 ) { display.setCursor( 5, 24); display.print("> 1.Auto"); }
  else { display.setCursor( 18, 24); display.print("1.Auto"); }
  if ( mode_disp_data == 2 ) { display.setCursor( 5, 34); display.print("> 2.Object Tracking"); }
  else { display.setCursor( 18, 34); display.print("2.Object Tracking"); } 
  if ( mode_disp_data == 3 ) { display.setCursor( 5, 44); display.print("> 3.Line Tracking "); }
  else { display.setCursor( 18, 44); display.print("3.Line Tracking"); } 
  if ( mode_disp_data == 4 ) { display.setCursor( 5, 54); display.print("> 4.Manual"); } 
  else { display.setCursor( 18, 54); display.print("4.Manual"); }
  display.display();
}
void mode_( int mode_disp_data, int wifi_disp_data){
  display.clearDisplay();
  display.setTextSize(3);
  if ( mode_disp_data == 0 ) { display.setCursor( 30, 16); display.print("REST"); } 
  if ( mode_disp_data == 1 ) { display.setCursor( 30, 16); display.print("AUTO"); } 
  if ( mode_disp_data == 2 ) { display.setTextSize(2);
                               display.setCursor( 29, 5); display.print("OBJECT");
                               display.setCursor( 14, 28); display.print("TRACKING");}
  if ( mode_disp_data == 3 ) { display.setTextSize(2);
                               display.setCursor( 35, 5); display.print("LINE");
                               display.setCursor( 14, 28); display.print("TRACKING");}
  if ( mode_disp_data == 4 ) { display.setCursor( 11, 16); display.print("MANUAL"); } 
  if ( wifi_disp_data == 1 ) { display.setTextSize(1);display.setCursor( 3, 55); 
                               display.print("...WIFI-CONNECTED...");
   }
  else if(wifi_disp_data==0){  display.setTextSize(1);display.setCursor(5,55); 
                               display.print(".WIFI-NOT CONNECTED.");
   }
  display.display();
} 
void display_oled_disp1( String s1_disp_data, String s2_disp_data, String Motor_disp_data, String Motor_display_data){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor( 44, 0);   display.print("STATUS");
  display.setCursor( 3, 18);   display.print("MOTOR");
  display.setCursor( 90, 18);  display.print(":");
  display.setCursor( 100, 18); display.print(Motor_disp_data);
  display.setCursor( 3, 29);   display.print("BLUETOOTH");
  display.setCursor( 90, 29);  display.print(":");
  display.setCursor( 100, 29); display.print(Motor_display_data);
  display.setCursor( 3, 40);   display.print("SENSOR 1");
  display.setCursor( 90, 40);  display.print(":");
  display.setCursor( 100, 40); display.print(s1_disp_data);
  display.setCursor( 3, 51);   display.print("SENSOR 2");
  display.setCursor( 90, 51);  display.print(":");
  display.setCursor( 100, 51); display.print(s2_disp_data);
  display.display();      
}
void display_oled_disp2( String frontLED_disp_data, String downLED_disp_data, String rgbBack_disp_data, String rgbFront_disp_data ){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor( 44, 0);   display.print("STATUS");
  display.setCursor( 3, 18);   display.print("FRONT LED'S");
  display.setCursor( 90, 18);  display.print(":");
  display.setCursor( 100, 18); display.print(frontLED_disp_data);
  display.setCursor( 3, 29);   display.print("WHEEL'S LED");
  display.setCursor( 90, 29);  display.print(":");
  display.setCursor( 100, 29); display.print(downLED_disp_data);
  display.setCursor( 3, 40);   display.print("RGB BACK");
  display.setCursor( 90, 40);  display.print(":");
  display.setCursor( 100, 40); display.print(rgbBack_disp_data);
  display.setCursor( 3, 51);   display.print("RGB FRONT");
  display.setCursor( 90, 51);  display.print(":");
  display.setCursor( 100,51);  display.print(rgbFront_disp_data);
  display.display();      
}
void switch_on_off(bool sensor1_out_data,bool sensor2_out_data,bool wheels_led_out_data,bool front_led_out_data,bool bluetooth_out_data,bool motor_out_data){
  digitalWrite( sensor1, sensor1_out_data);
  digitalWrite( sensor2, sensor2_out_data);
  digitalWrite( wheels_led, wheels_led_out_data);
  Blynk.virtualWrite( V35, wheels_led_out_data);
  digitalWrite( front_led, front_led_out_data);
  Blynk.virtualWrite( V34, front_led_out_data);
  digitalWrite( bluetooth, bluetooth_out_data);
  Blynk.virtualWrite( V32, bluetooth_out_data);
  digitalWrite( motor, motor_out_data);
  Blynk.virtualWrite( V31, motor_out_data);
}
void RGB_Color( int i, int j, int k) {  
  ledcWrite( R_channel, i);   
  ledcWrite( G_channel, j);  
  ledcWrite( B_channel, k);   
}   
void rgb_led1(){//for wifi not connected
  for(int i = 0; i < NUM_LEDS; i++) { leds[i] = CRGB::Red; FastLED.show();
    delay(100); leds[i] = CRGB::Black;
  }
  for(int i = NUM_LEDS - 1; i >= 0; i--) { leds[i] = CRGB::Red; FastLED.show();
    delay(100); leds[i] = CRGB::Black;
  }
}
void rgb_led2(){//mode changed
for (int i = 0; i < NUM_LEDS; i++) { leds[i] = CHSV(hue + (i * 10), 255, 255); }
  EVERY_N_MILLISECONDS(15){ hue++; } FastLED.show();
}
void rgb_led4(){//for wifi connected
  for(int i = 0; i < NUM_LEDS; i++) { leds[i] = CRGB::Green; FastLED.show();
    delay(100); leds[i] = CRGB::Black; }
  for(int i = NUM_LEDS - 1; i >= 0; i--) { leds[i] = CRGB::Green; FastLED.show();
    delay(100); leds[i] = CRGB::Black;  }
}
void rgb_led5(){//auto
  for(int i = 0; i < NUM_LEDS; i++) { leds[i] = CRGB::Orange; FastLED.show();
    delay(100); leds[i] = CRGB::Black; }
  for(int i = NUM_LEDS - 1; i >= 0; i--) { leds[i] = CRGB::Orange; FastLED.show();
    delay(100); leds[i] = CRGB::Black;  }
}
void rgb_led6(){//odject tracking mode
  for(int i = 0; i < NUM_LEDS; i++) {    leds[i] = CRGB::Gray; FastLED.show();
    delay(100); leds[i] = CRGB::Black;  }
  for(int i = NUM_LEDS - 1; i >= 0; i--) {leds[i] = CRGB::Gray; FastLED.show();
    delay(100); leds[i] = CRGB::Black;  }
}
void rgb_led7(){//line tracking mode
  for(int i = 0; i < NUM_LEDS; i++) {    leds[i] = CRGB::Yellow; FastLED.show();
    delay(100); leds[i] = CRGB::Black;  }
  for(int i = NUM_LEDS - 1; i >= 0; i--) {    leds[i] = CRGB::Yellow; FastLED.show();
    delay(100); leds[i] = CRGB::Black;  }
}
void rgb_led8(){//rest stop
  for(int i = 0; i < NUM_LEDS; i++) { leds[i] = CRGB::White; FastLED.show();
    delay(100); leds[i] = CRGB::Black;  }
  for(int i = NUM_LEDS - 1; i >= 0; i--) {leds[i] = CRGB::White; FastLED.show();
    delay(100); leds[i] = CRGB::Black;  }
}
BLYNK_WRITE(V31){
  motor_app_data = param.asInt();
  motor_on_off_data = motor_app_data;
  if( motor_app_data == 1 ) motor_s_app_data = "ON";
  else motor_s_app_data = "OFF";
}
BLYNK_WRITE(V32){
  bt_app_data = param.asInt();
  bt_out_data = bt_app_data;
  if( bt_app_data == 1 ){ BT__data_inp = "ON"; bt_out_data = 1; }
  else {BT__data_inp = "OFF"; bt_out_data = 0; }
}
BLYNK_WRITE(V33){
  Front_rgb_led_app_data = param.asInt();
}
BLYNK_WRITE(V34){
  Front_led_app_data = param.asInt();
  if( Front_led_app_data == 1 ) Front_led_s_data = "ON";
  else Front_led_s_data = "OFF";
}
BLYNK_WRITE(V35){
  wheels_led_app_data = param.asInt();
  if( wheels_led_app_data == 1 ) wheels_led_s_data = "ON";
  else wheels_led_s_data = "OFF";
}
BLYNK_WRITE(V11){
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  RGB_Color(r,g,b);
  if((r>0)||(g>0)||(b>0)){ rgbb_d_inp = "ON";}
  else rgbb_d_inp = "OFF";
}
BLYNK_WRITE(V1){
  terminal_out_data = param.asStr();
  if( terminal_out_data == "stop" ){ c=0; }
  else if( terminal_out_data == "r"){ c=0; }
  else if( terminal_out_data == "a"){ c=1; }
  else if( terminal_out_data == "o"){ c=2; }
  else if( terminal_out_data == "m"){ c=4; }
  else if( terminal_out_data == "l"){ c=3; }
  else if( terminal_out_data == "b"){ c=4; }
  else if( terminal_out_data == "rest"){ c=0; }
  else if( terminal_out_data == "auto"){ c=1; }
  else if( terminal_out_data == "object tracking"){ c=2; }
  else if( terminal_out_data == "line tracking"){ c=3; }
  else if( terminal_out_data == "manual"){ c=4; }
  else if( terminal_out_data == "object"){ c=2; }
  else if( terminal_out_data == "obj"){ c=2; }
  else if( terminal_out_data == "line"){ c=3; }
  else if( terminal_out_data == "bluetooth"){ c=4; }
  else if( terminal_out_data == "manual"){ c=4; }
 temp1 = c;
}
BLYNK_WRITE(V3){ c_app = param.asInt(); c = c_app; }

void loop() {

  if(WiFi.status()!=WL_CONNECTED){ 
    terminal.println("Not connected");
    rgb_led1();
    wifi_inp=0;
    qwe=1;
//    if(b2<=3){
//      digitalWrite(buzzer,1);
//      delay(500);
//      digitalWrite(buzzer,0);
//      delay(500);
//      b1=0;
//      b2++;
//    }
 }
  else { 
    wifi_inp=1;
//    if(b1<=2){
//      digitalWrite(buzzer,1);
//      delay(200);
//      digitalWrite(buzzer,0);
//      delay(200);
//      b1++;
//      b2=0;
//    }
   Blynk.run();
    if((Front_rgb_led_app_data==1)&&(qwe==1)){ rgb_led4(); rgb_led4(); qwe=0;}
    else {
        leds[0] = CRGB::Black; FastLED.show();   
        leds[1] = CRGB::Black; FastLED.show();
        leds[2] = CRGB::Black; FastLED.show();
      }
  }

  //pb = digitalRead(input1_pb);
  //if( pb == HIGH ){ c++; if(c>4) c=0; Blynk.virtualWrite(V3,c);temp1 = c; }
  if(Serial2.available()){
    rC = Serial2.read();
    if( rC == 'a'){c=1;}//auto mode
    else if( rC == 'b'){ c = 2; }//human tracking mode
    else if( rC == 'c'){ c = 3; }//line tracking mode
    else if( rC == 'd'){ c = 4; }//bluetooth mode
    else if( rC == 's'){ c = 0; }//stop
    temp1 = c;
    Blynk.virtualWrite(V3,c);
    if(c>5){ c = 0;}   
  }
  if(c!=temp){
    rgb_led2();
    delay(100);
    rgb_led2();
    delay(100);
    rgb_led2();
    temp1 = c;
    digitalWrite(buzzer,1);
    delay(100);
    digitalWrite(buzzer,0);
    delay(300);
    digitalWrite(buzzer,1);
    delay(100);
    digitalWrite(buzzer,0);
    delay(300);
  } 
  temp = c;
  
  switch(temp1){
    case 0 :  disp_inp = 0;  //rest mode  27
              sensor1_d = 0; sensor2_d = 0; bt_out_data = 0; motor_on_off_data = 0;  
              s_1_inp="OFF"; s_2_inp="OFF"; motor_s_app_data="OFF"; BT__data_inp="OFF";
              terminal.println("REST MODE");
              temp1=5;
              break;
    case 1 :  disp_inp=1;//auto mode
              sensor1_d=1; sensor2_d=0; bt_out_data=0; motor_on_off_data=1;  
              s_1_inp="ON"; s_2_inp="OFF"; motor_s_app_data="ON"; BT__data_inp="OFF";
              terminal.println("AUTO MODE");
              temp1=5;
              break;
    case 2 :  disp_inp=2;//human tracking mode
              sensor1_d=1; sensor2_d=0; bt_out_data=0; motor_on_off_data=1;  
              s_1_inp="ON"; s_2_inp="OFF"; motor_s_app_data="ON"; BT__data_inp="OFF";
              terminal.println("OBJECT TRACKING MODE");
              temp1=5;
              break;
    case 3 :  disp_inp=3;//line tracking mode
              sensor1_d=0; sensor2_d=1; bt_out_data=0; motor_on_off_data=1;  
              s_1_inp="OFF"; s_2_inp="ON"; motor_s_app_data="ON"; BT__data_inp="OFF";
              terminal.println("LINE TRACKING MODE");
              temp1=5;
              break;
    case 4 :  disp_inp=4; //bluetooth mode ||anual
              sensor1_d=0; sensor2_d=0; bt_out_data=1; motor_on_off_data=1;  
              s_1_inp="OFF"; s_2_inp="OFF"; motor_s_app_data="ON"; BT__data_inp="ON";
              terminal.println("BLUETOOTH MODE ");
              temp1=5;
              break;
  } 
  if( c == 0){Serial2.println('e');}//auto mode
  else if( c == 1){ Serial2.println('a'); }
  else if( c == 2){ Serial2.println('b'); }
  else if( c == 3){ Serial2.println('c'); }
  else if( c == 4){ Serial2.println('d'); }
  if(Front_rgb_led_app_data==1){
    rgbf_d_inp= "ON";
    if(c==0)rgb_led8();
    else if( c == 1)rgb_led5();
    else if( c == 2)rgb_led6();
    else if( c == 3)rgb_led7();
    else if( c == 4)rgb_led5();
  }
  else rgbf_d_inp = "OFF";
  switch_on_off(sensor1_d,sensor2_d,wheels_led_app_data,Front_led_app_data,bt_out_data,motor_on_off_data);
  if( z>=0 && z<2 ){ menu(disp_inp); }
  else if( z>=2 && z<5){ mode_(disp_inp,wifi_inp); }
  else if( z>=5 && z<7){ display_oled_disp1(s_1_inp,s_2_inp,motor_s_app_data, BT__data_inp); }
  else if( z>=7 && z<9){ display_oled_disp2(Front_led_s_data,wheels_led_s_data,rgbb_d_inp,rgbf_d_inp); }
  x = millis();
  if( x-y >= 1000 ){ y=x; z++; if( z>9 ){ z=0; } y=x; }
}               
    
                                                                      
