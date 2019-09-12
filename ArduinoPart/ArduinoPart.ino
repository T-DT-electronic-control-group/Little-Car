
typedef unsigned int DATA;

int state=HIGH;
DATA send_data=15;
DATA rx_data;


void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,state);
}

void loop() 
{
  #if 0
  Serial.print(15);
  if(Serial.available()>0)
  {
    rx_data=Serial.read();
    Serial.println(rx_data);
    Serial.println("a");
    if(rx_data==0x01||rx_data==0x02)
    {
      state=!state;
      digitalWrite(13,state);
      Serial.println("success");
    }
    delay(10);
  }
  #endif

  digitalWrite(13,HIGH);
  delay(100);
  Serial.print("abcd\r\n");
  Serial.write("abcd\r\n");
  digitalWrite(13,LOW);
  delay(100);
  
  
}
