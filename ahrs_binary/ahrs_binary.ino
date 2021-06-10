#define DeviceID 0x01
    #define STX 0x02
    #define ETX 0x03
    #define Command 0xF0
    #define ACC 0x33
    #define GYR 0x34
    #define ANG 0x35

    //define은 AHRS [메뉴얼](http://www.devicemart.co.kr/goods/view?no=1310790#goods_file) datasheet 보고 설정. 아래 이미지로 첨부.


    unsigned char buf; //센서에서 들어오는 값을 저장.
    unsigned char buff_arrey[13] = {0,};  //buf를 통해 들어오는 값을 배열로 저장.
    char cs = 0; //checksum 
    int16_t acc_x = 0, acc_y = 0, acc_z = 0, gyr_x = 0, gyr_y = 0, gyr_z = 0, ang_x = 0, ang_y = 0, ang_z = 0; //16비트 크기의 부호있는 정수형 선언.

    void setup() {
  
    Serial.begin(115200); //AHRS_UI Baudrate 동일하게 설정.

    }

    void loop() {

        if (Serial.available()){  
    
            for(int i=0; i<13 ; i++){
        
                Serial.readBytes(&buf,1);
                buff_arrey[i] = buf;

                //버퍼에 들어오는 값을 buf를 통해 buff_arrey 배열에 1~13(0~12)까지 순서대로 저장.
            }          
      
            if (buff_arrey[0] == STX && buff_arrey[2] == DeviceID && buff_arrey[3] == Command && buff_arrey[12] == ETX){

                //buff_arrey 값이 위에 datasheet 대로 설정한 값과 같을경우.
          
                cs = 0; //CheckSumReset

                for (int i = 2; i < 11; ++i){
                    cs += buff_arrey[i];  
                    //buff_arrey 배열의 값을 cs에 추가.
                }
                
                if (cs == buff_arrey[11]){  //cs값이 buff_arrey[11] 과 같으면 정상 패킷.
                
                    switch (buff_arrey[4]){ //buff_arrey[4] = index
                
                        case ACC: //가속도
                            
                            acc_x = (buff_arrey[5] | buff_arrey[6] << 8);  // value1.
                            acc_y = (buff_arrey[7] | buff_arrey[8] << 8);  // value2.
                            acc_z = (buff_arrey[9] | buff_arrey[10] << 8); // value3.
                            Serial.print("ACC  ");
                            Serial.print(acc_x / 1000.0); //가속도 복원시 변환 식
                            Serial.print("  ");
                            Serial.print(acc_y / 1000.0); //가속도 복원시 변환 식
                            Serial.print("  ");
                            Serial.print(acc_z / 1000.0); //가속도 복원시 변환 식
                            break;
                    
                        case GYR: //각속도
                            
                            gyr_x = (buff_arrey[5] | buff_arrey[6] << 8); // value1.
                            gyr_y = (buff_arrey[7] | buff_arrey[8] << 8); // value2.
                            gyr_z = (buff_arrey[9] | buff_arrey[10] << 8); // value3.
                            Serial.print("GYR  ");
                            Serial.print(gyr_x / 10.0); //각속도 복원시 변환 식
                            Serial.print("  ");
                            Serial.print(gyr_y / 10.0); //각속도 복원시 변환 식
                            Serial.print("  ");
                            Serial.print(gyr_z / 10.0); //각속도 복원시 변환 식
                            break;
                    
                        case ANG: //오일러 각도
                            
                            ang_x = (buff_arrey[5] | buff_arrey[6] << 8); // value1.
                            ang_y = (buff_arrey[7] | buff_arrey[8] << 8); // value2.
                            ang_z = (buff_arrey[9] | buff_arrey[10] << 8); // value3.
                            Serial.print("ANG  ");
                            Serial.print(ang_x/100.0); //오일러각 복원시 변환 식
                            Serial.print("  ");
                            Serial.print(ang_y/100.0); //오일러각 복원시 변환 식
                            Serial.print("  ");
                            Serial.print(ang_z/100.0); //오일러각 복원시 변환 식
                            break;
                    }
                }
            }
            Serial.println("");
        }
     }
