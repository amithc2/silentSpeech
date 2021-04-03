/* ----------------------------------------------------------
       SilentSpeech - Diagnostic Testing Code

       Harris M

       March 29, 2021
   ---------------------------------------------------------- */

/* ----------------------------------------------------------
       LIBRARIES
   ---------------------------------------------------------- */
#include <SPI.h>
#include <SoftwareSerial.h>
#include <FileIO.h>
#include <math.h>
#include "ads1262.h"

unsigned long myTime;

/* ----------------------------------------------------------
       CONSTANTS
   ---------------------------------------------------------- */
#define PGA 1                     // Programmable Gain = 1
#define VREF 2.50                 // Internal reference of 2.048V
#define VFSR VREF/PGA             
#define FSR (((long int)1<<23)-1)  

/* ----------------------------------------------------------
       GLOBALS
   ---------------------------------------------------------- */
ads1262 PC_ADS1262;                     // class
float volt_V=0;
float volt_mV=0;
volatile int i;
volatile char SPI_RX_Buff[10];
volatile long ads1262_rx_Data[10];
volatile static int SPI_RX_Buff_Count = 0;
volatile char *SPI_RX_Buff_Ptr;
volatile int Responsebyte = false;
volatile signed long sads1262Count = 0;
volatile signed long uads1262Count=0;
double resolution;

void setup() {
  // Initialize the ADS1262 data ready and chip select pins 
  pinMode(ADS1262_DRDY_PIN, INPUT);                  //data ready input line
  pinMode(ADS1262_CS_PIN, OUTPUT);                   //chip enable output line
  pinMode(ADS1262_START_PIN, OUTPUT);               // start 
  pinMode(ADS1262_PWDN_PIN, OUTPUT);                // Power down output  

  // Initialize serial port and initialize ADS1262
  Serial.begin(9600);
  PC_ADS1262.ads1262_Init();                      
  Serial.println("ads1262 Initialised successfully....");

//  FileSystem.begin();

  
}

void loop() {
//  File script = FileSystem.open("C:/Users/Harris Mohamed/Documents/College/Projects/silentSpeech/ads1262/diagnostic/test.txt", FILE_WRITE);
  volatile int i,data;

  if((digitalRead(ADS1262_DRDY_PIN)) == LOW)               // monitor Data ready(DRDY pin)
  {  
    SPI_RX_Buff_Ptr = PC_ADS1262.ads1262_Read_Data();      // read 6 bytes conversion register
    Responsebyte = true ; 
  }

  if(Responsebyte == true)
  {
    for(i = 0; i <5; i++)
    {
      SPI_RX_Buff[SPI_RX_Buff_Count++] = *(SPI_RX_Buff_Ptr + i);              
    }
    Responsebyte = false;
  }
  
  if(SPI_RX_Buff_Count >= 5)
  {     
    ads1262_rx_Data[0]= (unsigned char)SPI_RX_Buff[1];  // read 4 bytes adc count
    ads1262_rx_Data[1]= (unsigned char)SPI_RX_Buff[2];
    ads1262_rx_Data[2]= (unsigned char)SPI_RX_Buff[3];
    ads1262_rx_Data[3]= (unsigned char)SPI_RX_Buff[4];
 
    uads1262Count = (signed long) (((unsigned long)ads1262_rx_Data[0]<<24)|((unsigned long)ads1262_rx_Data[1]<<16)|(ads1262_rx_Data[2]<<8)|ads1262_rx_Data[3]);//get the raw 32-bit adc count out by shifting
    sads1262Count = (signed long) (uads1262Count);      // get signed value
    resolution = (double)((double)VREF/pow(2,31));       //resolution= Vref/(2^n-1) , Vref=2.5, n=no of bits
    volt_V      = (resolution)*(float)sads1262Count;     // voltage = resolution * adc count
    volt_mV   =   volt_V*1000;                           // voltage in mV
    Serial.print(millis());
    Serial.print("-> ");
    Serial.print("Readout voltage");
    Serial.print(" : ");
    Serial.print(volt_V);
    Serial.print(" V ,");
    Serial.print(volt_mV);
    Serial.println(" mV");
//
//    myTime = millis();
//
//    script.print(myTime);
//    script.print("-> "); 
//    script.print("Readout voltage");
//    script.print(" : ");
//    script.print(volt_V);
//    script.print(" V ,");
//    script.print(volt_mV);
//    script.println(" mV");
//    script.close();
   }
    
  SPI_RX_Buff_Count = 0;
}

// Function provided by Protocentral 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
