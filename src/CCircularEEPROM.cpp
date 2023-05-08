#include "CCircularEEPROM.h"

void CCircularEEPROM::CC_Scan(){
  uint16_t a;
  Serial.println("↓¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯↓ ");
  Serial.println("INFO");
  Serial.print("Starting cell: ");
  Serial.print(cstart);
  Serial.print(" || Ending cell: ");
  Serial.println(cend);
  Serial.print("Reserved cells ");
  Serial.print(Start);
  Serial.print("-");
  Serial.print(Start+1);
  Serial.print(" || Usable size: ");
  Serial.println(cend-cstart+1);

  Serial.println("INDEXES");

  Serial.print("Find: ");
  Serial.print(Find);
  Serial.print(" Bind: ");
  Serial.print(Bind);
  Serial.print(" ind: ");
  Serial.println(ind);

  Serial.println(" ");
  Serial.println("STORAGE");

  for(a=cstart;a<=cend;a++){
    Serial.print(a);
    Serial.print(": ");
    Serial.println(char(EEPROM.read(a)));
  }
  Serial.println("↑________________________________________↑");
}

uint16_t CCircularEEPROM::Get_Index(char mode='a'){
  
  if(mode!='a'){
    byte byte1 = EEPROM.read(Start);
    byte byte2 = EEPROM.read(Start+1);
    return ((byte1 << 8) + byte2);}
  else{
    return ind;
  }
}

uint16_t CCircularEEPROM::Get_Findex(){
  return Find;
}

uint16_t CCircularEEPROM::Get_Bindex(){
  return Bind;
}

void CCircularEEPROM::Backward_Retrieve(char *Backward_Word,uint16_t d=0){

  Serial.println("BACKWARD RETRIEVE");

  d=(d==0)?Bind:d;
  d=(d==cstart-1)?cend:d;
  char letter;
  if(letter=EEPROM.read(d)!='\0' | d>cend | d<cstart ){
    Serial.println("WRONG STARTING POINT..select a cell with '\\0'.");
    Backward_Word[0]='\0';
    return;
  }
  
  Find=d;
  
  uint16_t x=0;
  
  bool flag=true;
  d=(d==cstart)?cend:d-1;
  letter=EEPROM.read(d);

  while(letter=='\0'){
    
    d=(d==cstart)?cend:d-1; 
    letter=EEPROM.read(d);
  }
  
  do{
    letter=EEPROM.read(d);
    d=(d==cstart)?cend:d-1;
  }while(letter!='\0');

  d=(d==cend)?cstart:d+1;
  uint16_t point=d;
  d=(d==cend)?cstart:d+1;
  //d=(d==1022)?2:d+2;
 
  x=0;

  flag=true;

   do{
    letter=EEPROM.read(d);
    Backward_Word[x]=letter;
    x++;
    d=(d==cend)?cstart:d+1;
  }while(letter!='\0');
  d=(d==cstart)?cend:d-1;

  Bind=point;
  return;
}

void CCircularEEPROM::Forward_Retrieve(char* Forward_Word,uint16_t d=0){

  Serial.println("FORWARD RETRIEVE");

  d=(d==0)?Find:d;
  d=(d==cend+1)?cstart:d;
  char letter;
  uint16_t x=0;
  
  if(letter=EEPROM.read(d)!='\0' | d>cend | d<cstart){
    Serial.println("WRONG STARTING POINT..select a cell with '\\0'.");
    Forward_Word[0]='\0';
    return;
  }
  
  Bind=d;
  d=(d==cend)?cstart:d+1;
  
  letter=EEPROM.read(d);

  while(letter=='\0'){
    
    d=(d==cend)?cstart:d+1;
    letter=EEPROM.read(d);
  }

   do{
    letter=EEPROM.read(d);
    Forward_Word[x]=letter;
    x++;
    d=(d==cend)?cstart:d+1;
  }while(letter!='\0');
  d=(d==cstart)?cend:d-1;
  
  Find=d;
  return;
}

uint16_t CCircularEEPROM::Save_Msg(char* temp){

  Serial.println("Saving data..");

  uint16_t a=0;
  bool flag=true;
  bool flag1=true;
  if(!temp[a]){
    Serial.println("NO DATA TO SAVE!");
    return (Bind);
  }

  do{
    ind=(ind==cend+1)?cstart:ind;
    EEPROM.update(ind,(temp[a]));
    flag=(temp[a]==EEPROM.read(ind))?true:false;
    Serial.print(ind);
    Serial.print(": ");
    Serial.println(temp[a]);
    
    ind++;
    a++;
  }while(temp[a-1]!='\0' && flag);

  if(!flag){
    Serial.println("SAVE ERROR 1");
    while(1);
  }
  ind=(ind==cend+1)?cstart:ind;
  Find=(ind==cstart)?cend:ind-1;
  Bind=Find;
  Serial.println(" ");
  return(Bind);
  
}
void CCircularEEPROM::save_index(){
    bool flag;
    byte byte1 = ind >> 8;
    byte byte2 = ind & 0xFF;
    EEPROM.update(Start, byte1);
    EEPROM.update(Start+1, byte2);

    byte1 = EEPROM.read(Start);
    byte2 = EEPROM.read(Start+1);
    flag=(((byte1 << 8) + byte2)==ind)?true:false;

    if(!flag){
      Serial.println("SAVE ERROR 2");
      while(1);
    }
}
void CCircularEEPROM::Reset(){ 
  bool flag;
  EEPROM.update(cstart,' ');
  flag=(' '==EEPROM.read(cstart))?true:false;
  if(!flag){
  Serial.println("RESET ERROR 3");
  while(1);
  }
  uint16_t a=cstart+1;
  
  char letter;
  Serial.println("RESET");
    do{
    EEPROM.update(a,'\0');
    flag=('\0'==EEPROM.read(a))?true:false;
    a++;
  }while(a!=cend+1 && flag);

  ind=cstart;
  Find=cend;
  Bind=Find;


  if(flag){

    byte byte1 = ind >> 8;
    byte byte2 = ind & 0xFF;

    EEPROM.update(Start, byte1);
    EEPROM.update(Start+1, byte2);

    byte1 = EEPROM.read(Start);
    byte2 = EEPROM.read(Start+1);
    flag=(((byte1 << 8) + byte2)==ind)?true:false;

    if(!flag){
      Serial.println("RESET ERROR 2");
      while(1);
    }
  }else{
    Serial.println("RESET ERROR 1");
    while(1);
  }

}

CCircularEEPROM::CCircularEEPROM(uint16_t start, uint16_t endd, bool _new=false){
  
  if(endd-start<=2 | endd>EEPROM.length() | start>EEPROM.length()){
    Serial.println("WRONG INPUT VARIABLES FOR CCircularEEPROM INITIALIZATION");
    while(1);
  } 

  Start=start;
  cend=endd;
  cstart=start+2;
    
  if(_new){
    ind=cstart;
    Find=cend;
    Bind=cend;
    Reset();
  }else{
    ind=Get_Index('s');
    Find=(ind==cstart)?cend:ind-1;
    Bind=Find;
  }
  //CC_Scan();
 
}


