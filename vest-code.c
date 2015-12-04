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
    // Wire.beginTransmission(32);
    // Wire.write(0xFF);
    // Wire.endTransmission();

}

int picker (String command)
{
    int ind1 = command.indexOf(",");
    String cmd = command.substring(0,ind1);
    int ind2 = command.indexOf(",",ind1+1);
    if (ind2==0) {
        ind2 = command.length();
    }
    int length = command.substring(ind1+1,ind2).toInt();
    int offset = 0;
    if(ind2<command.length()) {
        offset = command.substring(ind2+1,command.length()).toInt();
    }
    
    if(cmd == "tickle") {
        doTickle();
    } else if (cmd == "creepy") {
        doCreepy();  
    } else if (cmd == "shouldermassage") {
        activateShoulders();
    } else if (cmd == "bulletshots") {
        solenoidShot();
    } else if (cmd == "hugging") {
        hugMe();
    }
    //call of duty actions
    else if (cmd == "ACT1") {
        //start vibrators on right
        digitalWrite(rightside1,HIGH);
        digitalWrite(rightside2,HIGH);
        digitalWrite(rightside3,HIGH);
        delay(2000);
        digitalWrite(rightside1,LOW);
        digitalWrite(rightside2,LOW);
        digitalWrite(rightside3,LOW);
        Particle.publish("mZone","ft_rt_ht_vi,bk_rt_vi,2000");
    }
    else if (cmd=="ACT2") {
        //left side everything
        digitalWrite(leftside1,HIGH);
        digitalWrite(leftside2,HIGH);
        digitalWrite(leftside3,HIGH);
        digitalWrite(leftfront1,HIGH);
        digitalWrite(leftfront2,HIGH);
        digitalWrite(leftfront3,HIGH);
        Wire.beginTransmission(32);
        Wire.write(ALLSOLENOIDMASK+SHOULDERMASK);
        delay(1000);
        Wire.write(0);
        Wire.endTransmission();
        digitalWrite(leftside1,LOW);
        digitalWrite(leftside2,LOW);
        digitalWrite(leftside3,LOW);
        digitalWrite(leftfront1,LOW);
        digitalWrite(leftfront2,LOW);
        digitalWrite(leftfront3,LOW);
        delay(500);
        digitalWrite(leftside1,HIGH);
        digitalWrite(leftside2,HIGH);
        digitalWrite(leftside3,HIGH);
        digitalWrite(leftfront1,HIGH);
        digitalWrite(leftfront2,HIGH);
        digitalWrite(leftfront3,HIGH);
        delay(100);
        digitalWrite(leftside1,LOW);
        digitalWrite(leftside2,LOW);
        digitalWrite(leftside3,LOW);
        digitalWrite(leftfront1,LOW);
        digitalWrite(leftfront2,LOW);
        digitalWrite(leftfront3,LOW);
        Particle.publish("mZone","ft_lt_ht_vi,ft_lt_vt_vi,bk_lt_vi,ft_lt_sl,ft_lt_cu,ft_rt_cu,1600")
    }
    return 0;
}

void doCreepy()
{
    Wire.beginTransmission(33);
    Wire.write(CREEPYMASK);
    delay(200);
    Wire.write(0);
    Wire.endTransmission();
}

void activateShoulders()
{
    Wire.beginTransmission(33);
    Wire.write(SHOULDERMASK);
    delay(200);
    Wire.write(0);
    Wire.endTransmission();
}

void bulletshots()
{
    
}

void hugMe()
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
    if (zone=="ft_lt_ht_vi"){
        digitalWrite(leftfront1,HIGH);
        digitalWrite(leftfront2,HIGH);
        digitalWrite(leftfront3,HIGH);
        delay(length);
        digitalWrite(leftfront1,LOW);
        digitalWrite(leftfront2,LOW);
        digitalWrite(leftfront3,LOW);
    } if(zone=="ft_lt_vt_vi" || zone=="bk_lt_vi"){
        digitalWrite(leftside1,HIGH);
        digitalWrite(leftside2,HIGH);
        digitalWrite(leftside3,HIGH);
        delay(length);
        digitalWrite(leftside1,LOW);
        digitalWrite(leftside2,LOW);
        digitalWrite(leftside3,LOW);
    } else if(zone=="ft_rt_ht_vi"){
        digitalWrite(rightfront1,HIGH);
        digitalWrite(rightfront2,HIGH);
        digitalWrite(rightfront3,HIGH);
        delay(length);
        digitalWrite(rightfront1,LOW);
        digitalWrite(rightfront2,LOW);
        digitalWrite(rightfront3,LOW);
    } else if(zone=="ft_rt_vt_vi" || zone=="bk_rt_vi"){
        digitalWrite(rightside1,HIGH);
        digitalWrite(rightside2,HIGH);
        digitalWrite(rightside3,HIGH);
        delay(length);
        digitalWrite(rightside1,LOW);
        digitalWrite(rightside2,LOW);
        digitalWrite(rightside3,LOW);
    } else if (zone=="ft_lt_sl") {
        // Wire.beginTransmission(32);
        // Wire.write(0xFF);
        // Wire.endTransmission();
    } else if (zone=="ft_rt_sl") {
        // Wire.beginTransmission(33);
        // Wire.write(0xFF);
        // Wire.endTransmission();        
    } else if (zone=="ft_lt_cu") {
        // Wire.beginTransmission(32);
        // Wire.write(0xFF);
        // Wire.endTransmission();        
    } else if (zone=="ft_rt_cu") {
        // Wire.beginTransmission(33);
        // Wire.write(0xFF);
        // Wire.endTransmission();        
    } else if (zone=="ar_ch") {
        // Wire.beginTransmission(32);
        // Wire.write(0xFF);
        // Wire.endTransmission();        
    } else if (zone=="bk_st_ro") {
        // Wire.beginTransmission(33);
        // Wire.write(0xFF);
        // Wire.endTransmission();
    }
    
        
    
    return 0;
    
}
