typedef unsigned int DATA;


DATA send_data=15;
DATA rx_data;
int message;

void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}

void loop() 
{
  
  if(Serial.available()>0)
  {
    rx_data=Serial.read();
    Serial.println(rx_data);
    message=Serial.write("I have recived your message");
    delay(10);
  }
  Serial.write(send_data);
  
}
