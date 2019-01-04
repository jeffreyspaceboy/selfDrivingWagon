

/* Receiver code for the Arduino Radio control with PWM output
 * Install the NRF24 library to your IDE
 * Upload this code to the Arduino UNO, NANO, Pro mini (5V,16MHz)
 * Connect a NRF24 module to it:
 
    Module // Arduino UNO,NANO
    
    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12

This code receive 1 channels and prints the value on the serial monitor
Please, like share and subscribe : https://www.youtube.com/c/ELECTRONOOBS
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int rightTurn = 4;
int leftTurn = 5;
int motor = 6;

const uint64_t pipeIn = 0xE8E8F0F0E1LL;     //Remember that this code is the same as in the transmitter
RF24 radio(9, 10);  //CSN and CE pins

// The sizeof this struct should not exceed 32 bytes
struct packet_t {
  int up_down; 
  int left_right; 
};

packet_t received_data;

/**************************************************/

void setup()
{
  Serial.begin(9600);
  //We reset the received values
  received_data.left_right = 512;
  received_data.up_down = 522;
 
  //Once again, begin and radio configuration
  radio.begin();
  //radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  
  //We start the radio comunication
  radio.startListening();
  pinMode(rightTurn, OUTPUT);
  pinMode(leftTurn, OUTPUT);
  pinMode(motor, OUTPUT);

}

/**************************************************/

unsigned long last_Time = 0;

//We create the function that will read the data each certain time
void receive_the_data()
{
  unsigned long delta = 0;
  unsigned long current = 0;
  while ( radio.available() ) {
    radio.read(&received_data, sizeof(packet_t));
    last_Time = millis(); //Here we receive the data
  }

  current = millis();
  if (current > last_Time) {
    delta = current - last_Time;
  }
  if (delta > 1500) {
    Serial.println("Radio Unavailable > 1500ms");
    received_data.left_right = 512;
    received_data.up_down = 522;
  }
}

/**************************************************/

void loop()
{
  int speed = 0;
  //Receive the radio data
  receive_the_data();
#if 0
  Serial.print("L/R = ");
  Serial.print(received_data.left_right);
  Serial.print(", U/D = ");
  Serial.println(received_data.up_down);
#endif

  if (received_data.left_right > 550) {
    Serial.println("left");
    digitalWrite(leftTurn, HIGH);
    digitalWrite(rightTurn, LOW);    
  } else if (received_data.left_right < 480) {
    Serial.println("right");
    digitalWrite(rightTurn, HIGH);
    digitalWrite(leftTurn, LOW);
  } else {
    digitalWrite(rightTurn, LOW);
    digitalWrite(leftTurn, LOW);
  }
  
  if (received_data.up_down > 512) {
    speed = 0;
  } else {
    speed = 1023 - (received_data.up_down * 2);
  }
  
  if (speed < 10) {
    Serial.println("speed = 0");
    analogWrite(motor, 0);
  } else {
    Serial.print("speed = ");
    Serial.println(speed, DEC);
    analogWrite(motor, speed * 2);
  }
}//Loop end
