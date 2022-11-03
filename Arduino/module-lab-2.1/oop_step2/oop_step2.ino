class Instrument {
public:
  virtual void play() = 0;
 
protected:
  void makeSound(String s){
     Serial.println("Il suono e' "+s);
  }
};

class Percussion: public Instrument {
public:
  
  void play(){
    makeSound("toc");
  }  
};

class Piano: public Instrument {
public:
  void play(){
    makeSound("ding");
  }  
};

Instrument* list[2];

void setup(){
   Serial.begin(9600); 
   list[0] = new Piano();
   list[1] = new Percussion();
}

void loop(){
  ((Piano*)list[0])->play();
  
  for (int i = 0; i < 2; i++){
    list[i]->play();
  }
  delay(1000);
}
