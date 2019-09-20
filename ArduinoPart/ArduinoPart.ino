
typedef unsigned short DATA;

DATA send_data=15;
DATA rx_data;

char compare[]="abcd";
char comdata[]="";

int i=0;
int t=0;
int mark;


void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  
}

void loop() 
{

  #if 0
  
  digitalWrite(13,HIGH);
  delay(100);
  Serial.print("abcd\r\n");
  Serial.write("abcd\r\n");
  digitalWrite(13,LOW);
  delay(100);
  
  #endif

  #if 0

  if(Serial.available())
  {
    String comdata="";
    while(Serial.available()>0)
    {
      if(char(Serial.read()!='\r'&&Serial.read()!='\n'))
      {
        comdata=comdata+char(Serial.read());
        delay(2);
      }
    }
    i=0;
    for(t=0;t<comdata.length();t++)
    {
      if(comdata[i]==compare[i])
      {
        mark=1;
      }
      else
      {
        mark=0;
        break;
      }
      i++;
    }
    
  }
  if(mark=1)
  {
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(500);
  }
  #endif

  if(Serial.available())
  {
    rx_data=Serial.read();
    if(rx_data==15)
    {
      mark=1;
    }
    else mark=0;
  }
  if(mark==1)
  {
    digitalWrite(13,HIGH);
    delay(200);
    digitalWrite(13,LOW);
    delay(200);
  }
}
