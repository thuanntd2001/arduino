
    const int trig = 12;     // chân trig của HC-SR04
    const int echo = 14;     // chân echo của HC-SR04



    int pos = 0;   
    void setup()
    {
         Serial.begin(9600);     // giao tiếp Serial với baudrate 9600

        pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
        pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
       
    
    }
     
    int doDistance(){
      unsigned int duration; // biến đo thời gian
        int distance;           // biến lưu khoảng cách
        
        /* Phát xung từ chân trig */
        digitalWrite(trig,0);   // tắt chân trig
        delayMicroseconds(2);
        digitalWrite(trig,1);   // phát xung từ chân trig
        delayMicroseconds(5);   // xung có độ dài 5 microSeconds
        digitalWrite(trig,0);   // tắt chân trig
        
        /* Tính toán thời gian */
        // Đo độ rộng xung HIGH ở chân echo. 
        duration = pulseIn(echo,HIGH);  
        // Tính khoảng cách đến vật.
        distance = int(duration/2/29.412);
        
        /* In kết quả ra Serial Monitor */
        return distance;

    }


    void loop()
    {
      int i=doDistance();
    Serial.print("disTrai: ");
    Serial.println(i);

      
    }
