#define hand1 D7
#define hand2 D4
#define tricep1 D6
#define tricep2 D2
#define lowtri D3
#define elbow1 D5
#define elbow2 D1


void setup() {
    pinMode(hand1,OUTPUT);
    pinMode(hand2,OUTPUT);
    pinMode(tricep1,OUTPUT);
    pinMode(tricep2,OUTPUT);
    pinMode(lowtri,OUTPUT);
    pinMode(elbow1,OUTPUT);
    pinMode(elbow2,OUTPUT);
    Particle.function("function",picker);
    Particle.function("zone",activateZone);
}

void loop() {
    // doCreepy();
    // delay(1000);
    // for (int i=0;i<5;i++) {
    //     doAll();
    //     delay(500);
    // }
        
    
}

int picker(String command) {
    if(command=="creepy")
        doCreepy();
    else
        doAll();
    return 0;
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
    if(zone=="hand"){
        digitalWrite(hand1,HIGH);
        digitalWrite(hand2,HIGH);
        delay(length);
        digitalWrite(hand1,LOW);
        digitalWrite(hand2,LOW);
    } else if(zone=="tricep"){
        digitalWrite(tricep1,HIGH);
        digitalWrite(tricep2,HIGH);
        delay(length);
        digitalWrite(tricep1,LOW);
        digitalWrite(tricep2,LOW);
    } else if(zone=="elbow"){
        digitalWrite(elbow1,HIGH);
        digitalWrite(elbow2,HIGH);
        delay(length);
        digitalWrite(elbow1,LOW);
        digitalWrite(elbow2,LOW);
    }
        
    
    return 0;
    
}

void doCreepy(){
    digitalWrite(hand1,HIGH);
    digitalWrite(hand2,HIGH);
    delay(200);
    digitalWrite(hand1,LOW);
    digitalWrite(hand2,LOW);
    delay(20);
    digitalWrite(tricep1,HIGH);
    digitalWrite(tricep2,HIGH);
    delay(200);
    digitalWrite(tricep1,LOW);
    digitalWrite(tricep2,LOW);
    delay(20);
    digitalWrite(elbow1,HIGH);
    digitalWrite(elbow2,HIGH);
    delay(200);
    digitalWrite(elbow1,LOW);
    digitalWrite(elbow2,LOW);
}

void doAll(){
    digitalWrite(hand1,HIGH);
    digitalWrite(hand2,HIGH);
    digitalWrite(elbow1,HIGH);
    digitalWrite(elbow2,HIGH);
    digitalWrite(tricep1,HIGH);
    digitalWrite(tricep2,HIGH);
    delay(200);
    digitalWrite(hand1,LOW);
    digitalWrite(hand2,LOW);
    digitalWrite(tricep1,LOW);
    digitalWrite(tricep2,LOW);
    digitalWrite(elbow1,LOW);
    digitalWrite(elbow2,LOW);
}
