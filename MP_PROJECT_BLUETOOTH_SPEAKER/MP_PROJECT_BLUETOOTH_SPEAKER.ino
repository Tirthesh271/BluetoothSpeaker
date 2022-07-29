
#include "BluetoothA2DPSink.h"
#include <analogWrite.h>

BluetoothA2DPSink a2dp_sink;

int threshold = 0;
const int red = 18;
const int green = 19;
const int blue =21;

int audioOutput = 0;
void setup() {
  const i2s_config_t i2s_config = {
      .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
      .sample_rate = 44100, // corrected by info from bluetooth
      .bits_per_sample = (i2s_bits_per_sample_t) 16, /* the DAC module will only take the 8bits from MSB */
      .channel_format =  I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = (i2s_comm_format_t)I2S_COMM_FORMAT_STAND_MSB,
      .intr_alloc_flags = 0, // default interrupt priority
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = false
  };
  a2dp_sink.set_i2s_config(i2s_config);  
  a2dp_sink.start("InternalDAC");  

    Serial.begin(115200);
      pinMode(red, OUTPUT); // set all the pins as output
      pinMode(green, OUTPUT);
      pinMode(blue, OUTPUT);
      pinMode(4,INPUT);
      }


void loop() {
  audioOutput = analogRead(2); 
  Serial.println(audioOutput);

//  audioOutput = map(audioOutput, 1700, 1857, 0, 255);
audioOutput=(audioOutput)%256;
Serial.println(audioOutput);
  
// Serial.println(audioOutput);
if(audioOutput > threshold) // check if audio signal goes above threshold
 {
//   int a = random(1, 6); // store a random number
   int a=audioOutput;
   if(a<20){
      digitalWrite(green, HIGH);
     digitalWrite(blue, HIGH);
     digitalWrite(red, HIGH);    
    }
   if(a <=43 ) // glow red
   {
//     digitalWrite(red, HIGH);
     analogWrite(red, audioOutput);
     digitalWrite(green, LOW);
     digitalWrite(blue, LOW);
   }
   if(43<a &&  a<=86) // glow green
   {
     digitalWrite(red, 0);
     analogWrite(green, audioOutput);
     digitalWrite(blue, 0);
   }
   if(86<a &&  a<=129) // glow orange
   {
     analogWrite(red, audioOutput);
     analogWrite(green, audioOutput);
     digitalWrite(blue, 0);
   }
   if(129<a &&  a<=172) // glow cyan
   {
     digitalWrite(red, 0);
     analogWrite(green, audioOutput);
     analogWrite(blue, audioOutput);
   }
   if(172<a &&  a<=215) // glow purple
   {
     analogWrite(red, audioOutput);
     digitalWrite(green, 0);
     analogWrite(blue, audioOutput);
   }
   if(215<a &&  a<=255) // glow blue
   {
     digitalWrite(red, 0);
     digitalWrite(green, 0);
     digitalWrite(blue, 1);
   }
   delay(20); // wait for 20ms
 }
 else
 digitalWrite(red, LOW); // if audio signal is less than 20, set all the pins low
 digitalWrite(green, LOW);
 digitalWrite(blue, LOW);
 // again reach the top and start
}
