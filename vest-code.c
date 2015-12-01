#define leftfront1  A0
#define leftfront2  A1
#define leftfront3  A2
#define leftside1  A3
#define leftside2  A4
#define leftside3  A5

#define rightfront1  D0
#define rightfront2  D1
#define rightfront3  D2
#define rightside1  D3
#define rightside2  D4
#define rightside3  D5


void setup() {
    pinMode(leftfront1,OUTPUT);
    pinMode(leftfront2,OUTPUT);
    pinMode(leftfront3,OUTPUT);
    pinMode(leftside1,OUTPUT);
    pinMode(leftside2,OUTPUT);
    pinMode(leftside3,OUTPUT);
    pinMode(rightfront1,OUTPUT);
    pinMode(rightfront2,OUTPUT);
    pinMode(rightfront3,OUTPUT);
    pinMode(rightside1,OUTPUT);
    pinMode(rightside2,OUTPUT);
    pinMode(rightside3,OUTPUT);    
    Particle.function("function",picker);
    Particle.function("zone",activateZone);
}

void loop() {

}

int picker (String command)
{
    
}

void doTickle()
{
    int shortlength = 20, length=200;
    digitalWrite(leftside1,HIGH);
    delay(length);
    digitalWrite(leftside1,LOW);
    delay(shortlength);
    digitalWrite(leftside2,HIGH);
    delay(length);
    digitalWrite(leftside2,LOW);
    delay(shortlength);
}

int activateZone(String command)
{
    //pass in a loaded string which contains the zone, 
    //the amount of time to activate the zone for, and
    //in some cases, an offset time
    int ind1 = command.indexOf(",");
    String zone = command.substring(0,ind1);
    int ind2 = command.indexOf(",",ind1+1);
    if (ind2==0) {
        ind2 = command.length();
    }
    int length = command.substring(ind1+1,ind2).toInt();
    int offset = 0;
    if(ind2<command.length()) {
        offset = command.substring(ind2+1,command.length()).toInt();
    }
    
    Serial.printf("Activate %s for %d s in %d s",zone.c_str(),length,offset);
    
    delay(offset);
    char buffer[200];
    sprintf(buffer,"%d",length);
    Particle.publish(zone,buffer);
    if(zone=="leftfront1"){
        digitalWrite(leftfront1,HIGH);
        delay(length);
        digitalWrite(leftfront1,LOW);
    } else if(zone=="leftfront2"){
        digitalWrite(leftfront2,HIGH);
        delay(length);
        digitalWrite(leftfront2,LOW);
    } else if(zone=="leftfront3"){
        digitalWrite(leftfront3,HIGH);
        delay(length);
        digitalWrite(leftfront3,LOW);
    } if(zone=="leftside1"){
        digitalWrite(leftside1,HIGH);
        delay(length);
        digitalWrite(leftside1,LOW);
    } else if(zone=="leftside2"){
        digitalWrite(leftside2,HIGH);
        delay(length);
        digitalWrite(leftside2,LOW);
    } else if(zone=="leftside3"){
        digitalWrite(leftside3,HIGH);
        delay(length);
        digitalWrite(leftside3,LOW);
    } else if(zone=="rightfront1"){
        digitalWrite(rightfront1,HIGH);
        delay(length);
        digitalWrite(rightfront1,LOW);
    } else if(zone=="rightfront2"){
        digitalWrite(rightfront2,HIGH);
        delay(length);
        digitalWrite(rightfront2,LOW);
    } else if(zone=="rightfront3"){
        digitalWrite(rightfront3,HIGH);
        delay(length);
        digitalWrite(rightfront3,LOW);
    } if(zone=="rightside1"){
        digitalWrite(rightside1,HIGH);
        delay(length);
        digitalWrite(rightside1,LOW);
    } else if(zone=="rightside2"){
        digitalWrite(rightside2,HIGH);
        delay(length);
        digitalWrite(rightside2,LOW);
    } else if(zone=="rightside3"){
        digitalWrite(rightside3,HIGH);
        delay(length);
        digitalWrite(rightside3,LOW);
    } 
        
    
    return 0;
    
}
