typedef unsigned int DATA;

int state=HIGH;
DATA send_data=15;
DATA rx_data;
int message;

void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,state);
}

void loop() 
{
  
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
    //message=Serial.write("I have recived your message");
    delay(10);
  }
  //Serial.write(send_data);
  
}
