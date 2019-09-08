typedef unsigned char DATA;

DATA send_data;
DATA rx_data;
int message;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available()>0)
  {
    rx_data=Serial.read();
    Serial.println(rx_data);
    message=Serial.write("I have recived you message");
    delay(5);
  }
  send_data = rx_data;
  Serial.write(send_data);
  delay(5);
}
