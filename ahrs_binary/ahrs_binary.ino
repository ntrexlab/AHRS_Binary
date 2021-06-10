#define DeviceID 0x01
#define STX 0x02
#define ETX 0x03
#define Command 0xF0
#define ACC 0x33
#define GYR 0x34
#define ANG 0x35

unsigned char buf;
unsigned char buff_arrey[13] = {0,};
char str[100];
char cs = 0;
int16_t acc_x = 0, acc_y = 0, acc_z = 0, gyr_x = 0, gyr_y = 0, gyr_z = 0, ang_x = 0, ang_y = 0, ang_z = 0;

void setup() {
  
  Serial.begin(115200);

}

void loop() {

  if (Serial.available()){
    
    for(int i=0; i<13 ; i++){
        
      Serial.readBytes(&buf,1);
      buff_arrey[i] = buf;
    }    
      
      if (buff_arrey[0] == STX && buff_arrey[2] == DeviceID && buff_arrey[3] == Command && buff_arrey[12] == ETX){
          
          cs = 0; //CheckSumReset
          for (int i = 2; i < 11; ++i){
            cs += buff_arrey[i];
          }
            if (cs == buff_arrey[11]){ 
                
                switch (buff_arrey[4]){
                
                  case ACC:
                    acc_x = (buff_arrey[5] | buff_arrey[6] << 8);
                    acc_y = (buff_arrey[7] | buff_arrey[8] << 8);
                    acc_z = (buff_arrey[9] | buff_arrey[10] << 8);
                    Serial.print("ACC  ");
                    Serial.print(acc_x / 1000.0);
                    Serial.print("  ");
                    Serial.print(acc_y / 1000.0);
                    Serial.print("  ");
                    Serial.print(acc_z / 1000.0);
                    break;
                    
                case GYR:
                    gyr_x = (buff_arrey[5] | buff_arrey[6] << 8);
                    gyr_y = (buff_arrey[7] | buff_arrey[8] << 8);
                    gyr_z = (buff_arrey[9] | buff_arrey[10] << 8);
                    Serial.print("GYR  ");
                    Serial.print(gyr_x / 10.0);
                    Serial.print("  ");
                    Serial.print(gyr_y / 10.0);
                    Serial.print("  ");
                    Serial.print(gyr_z / 10.0);
                    break;
                    
                case ANG:
                    ang_x = (buff_arrey[5] | buff_arrey[6] << 8);
                    ang_y = (buff_arrey[7] | buff_arrey[8] << 8);
                    ang_z = (buff_arrey[9] | buff_arrey[10] << 8);
                    float x = ang_x / 100.0;
                    float y = ang_y / 100.0;
                    float z = ang_z / 100.0;
                    Serial.print("ANG  ");
                    Serial.print(x);
                    Serial.print("  ");
                    Serial.print(y);
                    Serial.print("  ");
                    Serial.print(z);
                    break;
               }
                 
           }
       }
      Serial.println("");
  }
 }
