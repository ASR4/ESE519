#define leftfront1  A0
#define leftfront2  A1
#define leftfront3  A2
#define leftside1  A3
#define leftside2  A4
#define leftside3  A5

#define rightfront1  D2
#define rightfront2  D3
#define rightfront3  D4
#define rightside1  D5
#define rightside2  D6
#define rightside3  D7

#define ALLSOLENOIDMASK 0x07
#define SHOULDERMASK 0x08
#define CREEPYMASK 0x10
#define HUGMASK 0x10
#define SOFTROBOMASK 0x00

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



}

int readPressure() {
    int value;
    Wire.requestFrom(28,sizeof(value));
    value = Wire.read();
    return value;
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
        bulletshots();
    } else if (cmd == "hugging") {
        hugMe();
    }
    //call of duty actions
    else if (cmd == "Act1") {
        //start vibrators on right
        Particle.publish("mZone","ft_rt_ht_vi,bk_rt_vi,2000");
        digitalWrite(rightside1,HIGH);
        digitalWrite(rightside2,HIGH);
        digitalWrite(rightside3,HIGH);
        delay(2000);
        digitalWrite(rightside1,LOW);
        digitalWrite(rightside2,LOW);
        digitalWrite(rightside3,LOW);
    }
    else if (cmd=="Act2") {
        //left side everything
        Particle.publish("mZone","ft_lt_ht_vi,ft_lt_vt_vi,bk_lt_vi,ft_lt_sl,ft_lt_cu,ft_rt_cu,1600");
        digitalWrite(leftside1,HIGH);
        digitalWrite(leftside2,HIGH);
        digitalWrite(leftside3,HIGH);
        digitalWrite(leftfront1,HIGH);
        digitalWrite(leftfront2,HIGH);
        digitalWrite(leftfront3,HIGH);
        Wire.beginTransmission(0x38);
        Wire.write(ALLSOLENOIDMASK+SHOULDERMASK);
        Wire.endTransmission();
        delay(1000);
        Wire.beginTransmission(0x38);
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
    }
    else if (cmd=="Act4")
    {
        //Danger, all vib, sol, cuffs
        Particle.publish("mZone","ft_lt_ht_vi,ft_lt_vt_vi,bk_lt_vi,ft_lt_sl,ft_lt_cu,ft_rt_cu,500");
        digitalWrite(leftside1,HIGH);
        digitalWrite(leftside2,HIGH);
        digitalWrite(leftside3,HIGH);
        digitalWrite(leftfront1,HIGH);
        digitalWrite(leftfront2,HIGH);
        digitalWrite(leftfront3,HIGH);
        digitalWrite(rightside1,HIGH);
        digitalWrite(rightside2,HIGH);
        digitalWrite(rightside3,HIGH);
        digitalWrite(rightfront1,HIGH);
        digitalWrite(rightfront2,HIGH);
        digitalWrite(rightfront3,HIGH);
        Wire.beginTransmission(0x38);
        Wire.write(ALLSOLENOIDMASK+SHOULDERMASK);
        Wire.endTransmission();
        Wire.beginTransmission(0x39);
        Wire.write(ALLSOLENOIDMASK+SHOULDERMASK);
        Wire.endTransmission();
        delay(400);
        digitalWrite(leftside1,LOW);
        digitalWrite(leftside2,LOW);
        digitalWrite(leftside3,LOW);
        digitalWrite(leftfront1,LOW);
        digitalWrite(leftfront2,LOW);
        digitalWrite(leftfront3,LOW);
        digitalWrite(rightside1,LOW);
        digitalWrite(rightside2,LOW);
        digitalWrite(rightside3,LOW);
        digitalWrite(rightfront1,LOW);
        digitalWrite(rightfront2,LOW);
        digitalWrite(rightfront3,LOW);
        Wire.beginTransmission(0x38);
        Wire.write(0);
        Wire.endTransmission();
        Wire.beginTransmission(0x39);
        Wire.write(0);
        Wire.endTransmission();
        
    }
    else if (cmd=="Act5")
    {
        //death, all solenoids
        Particle.publish("mZone","ft_lt_sl,ft_rt_sl,600");
        Wire.beginTransmission(0x38);
        Wire.write(ALLSOLENOIDMASK);
        Wire.endTransmission();
        Wire.beginTransmission(0x39);
        Wire.write(ALLSOLENOIDMASK);
        Wire.endTransmission();
        delay(100);
        Wire.beginTransmission(0x38);
        Wire.write(0);
        Wire.endTransmission();
        Wire.beginTransmission(0x39);
        Wire.write(0);
        Wire.endTransmission();
        delay(100);
        Wire.beginTransmission(0x38);
        Wire.write(ALLSOLENOIDMASK);
        Wire.endTransmission();
        Wire.beginTransmission(0x39);
        Wire.write(ALLSOLENOIDMASK);
        Wire.endTransmission();
        delay(100);
        Wire.beginTransmission(0x38);
        Wire.write(0);
        Wire.endTransmission();
        Wire.beginTransmission(0x39);
        Wire.write(0);
        Wire.endTransmission();
        delay(100);
        Wire.beginTransmission(0x38);
        Wire.write(ALLSOLENOIDMASK);
        Wire.endTransmission();
        Wire.beginTransmission(0x39);
        Wire.write(ALLSOLENOIDMASK);
        Wire.endTransmission();
        delay(100);
        Wire.beginTransmission(0x38);
        Wire.write(0);
        Wire.endTransmission();
        Wire.beginTransmission(0x39);
        Wire.write(0);
        Wire.endTransmission();
        delay(100);
    }
    else if (cmd=="Act8")
    {
        //Flashbang sensation
        Particle.publish("mZone","ft_lt_ht_vi,ft_rt_ht_vi,bk_st_ro,300");
        digitalWrite(leftfront1,HIGH);
        digitalWrite(leftfront2,HIGH);
        digitalWrite(leftfront3,HIGH);
        digitalWrite(rightfront1,HIGH);
        digitalWrite(rightfront2,HIGH);
        digitalWrite(rightfront3,HIGH);
        Wire.beginTransmission(0x38);
        Wire.write(SOFTROBOMASK);
        Wire.endTransmission();
        
        delay(300);
        Wire.beginTransmission(0x38);
        Wire.write(0);
        Wire.endTransmission();
        digitalWrite(leftfront1,LOW);
        digitalWrite(leftfront2,LOW);
        digitalWrite(leftfront3,LOW);
        digitalWrite(rightfront1,LOW);
        digitalWrite(rightfront2,LOW);
        digitalWrite(rightfront3,LOW);
    }
    return 0;
}

void doCreepy()
{
    Particle.publish("mZone","neck_ar,200");
    Wire.beginTransmission(0x38);
    Wire.write(CREEPYMASK);
    Wire.endTransmission();
    delay(200);
    Wire.beginTransmission(0x38);
    Wire.write(0);
    Wire.endTransmission();
}

void activateShoulders()
{
    Particle.publish("mZone","ft_lt_cu,ft_rt_cu,200");
    Wire.beginTransmission(33);
    Wire.write(SHOULDERMASK);
    Wire.endTransmission();
    delay(200);
    Wire.beginTransmission(33);
    Wire.write(0);
    Wire.endTransmission();
}

void bulletshots()
{
    
}

void hugMe()
{
    Particle.publish("mZone","ar_ch,3000");
    Wire.beginTransmission(32);
    Wire.write(HUGMASK);
    Wire.endTransmission();
    delay(3000);
    Wire.beginTransmission(32);
    Wire.write(0);
    Wire.endTransmission();
}

void doTickle()
{
    int shortlength = 20, length=200;
    Particle.publish("mZone","ft_lt_vt_vi,bk_lt_vi,ft_lt_vt_vi,bk_lt_vi,1300");
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
        Wire.beginTransmission(0x38);
        Wire.write(ALLSOLENOIDMASK);
        Wire.endTransmission();
        delay(length);
        Wire.beginTransmission(0x38);
        Wire.write(0);
        Wire.endTransmission();
    } else if (zone=="ft_rt_sl") {
        Wire.beginTransmission(0x39);
        Wire.write(ALLSOLENOIDMASK);
        Wire.endTransmission(); 
        delay(length);
        Wire.beginTransmission(0x39);
        Wire.write(0);
        Wire.endTransmission();
    } else if (zone=="ft_lt_cu") {
        Wire.beginTransmission(0x38);
        Wire.write(SHOULDERMASK);
        Wire.endTransmission(); 
        delay(length);
        Wire.beginTransmission(0x38);
        Wire.write(0);
        Wire.endTransmission();
    } else if (zone=="ft_rt_cu") {
        Wire.beginTransmission(0x39);
        Wire.write(SHOULDERMASK);
        Wire.endTransmission();
        delay(length);
        Wire.beginTransmission(0x39);
        Wire.write(0);
        Wire.endTransmission();        
    } else if (zone=="ar_ch") {
        Wire.beginTransmission(0x39);
        Wire.write(HUGMASK);
        Wire.endTransmission();
        delay(length);
        Wire.beginTransmission(0x39);
        Wire.write(0);
        Wire.endTransmission();
    } else if (zone=="") { //this is for the neck creepy
    } else if (zone=="bk_st_ro") { //this should go away
        Wire.beginTransmission(0x39);
        Wire.write(SOFTROBOMASK);
        Wire.endTransmission();
        delay(length);
        Wire.beginTransmission(0x39);
        Wire.write(0);
        Wire.endTransmission();
    }
    return 0;
}
