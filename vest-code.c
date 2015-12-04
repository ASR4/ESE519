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
    Wire.begin();
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
    Wire.beginTransmission(32);
    Wire.write(0xFF);
    Wire.endTransmission();

}

int picker (String command)
{
    doTickle();
    
    return 0;
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
    digitalWrite(leftside3,HIGH);
    delay(length);
    digitalWrite(leftside3,LOW);
    delay(shortlength);
    digitalWrite(rightside1,HIGH);
    delay(length);
    digitalWrite(rightside1,LOW);
    delay(shortlength);
    digitalWrite(rightside2,HIGH);
    delay(length);
    digitalWrite(rightside2,LOW);
    delay(shortlength);
    digitalWrite(rightside3,HIGH);
    delay(length);
    digitalWrite(rightside3,LOW);
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
    if (zone=="front_left_horz_vibrators"){
        digitalWrite(leftfront1,HIGH);
        digitalWrite(leftfront2,HIGH);
        digitalWrite(leftfront3,HIGH);
        delay(length);
        digitalWrite(leftfront1,LOW);
        digitalWrite(leftfront2,LOW);
        digitalWrite(leftfront3,LOW);
    } if(zone=="front_left_vert_vibrators" || zone=="back_left_vibrators"){
        digitalWrite(leftside1,HIGH);
        digitalWrite(leftside2,HIGH);
        digitalWrite(leftside3,HIGH);
        delay(length);
        digitalWrite(leftside1,LOW);
        digitalWrite(leftside2,LOW);
        digitalWrite(leftside3,LOW);
    } else if(zone=="front_right_horz_vibrators"){
        digitalWrite(rightfront1,HIGH);
        digitalWrite(rightfront2,HIGH);
        digitalWrite(rightfront3,HIGH);
        delay(length);
        digitalWrite(rightfront1,LOW);
        digitalWrite(rightfront2,LOW);
        digitalWrite(rightfront3,LOW);
    } else if(zone=="front_right_vert_vibrators" || zone=="back_right_vibrators"){
        digitalWrite(rightside1,HIGH);
        digitalWrite(rightside2,HIGH);
        digitalWrite(rightside3,HIGH);
        delay(length);
        digitalWrite(rightside1,LOW);
        digitalWrite(rightside2,LOW);
        digitalWrite(rightside3,LOW);
    } else if (zone=="front_left_sole") {
        
    } else if (zone=="front_right_sole") {
        
    } else if (zone=="front_left_cuff") {
        
    } else if (zone=="front_right_cuff") {
        
    } else if (zone=="air_channel") {
        
    } else if (zone=="back_soft_robotics") {
        
    }
    
        
    
    return 0;
    
}
