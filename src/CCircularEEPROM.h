#ifndef CCircularEEPROM_H
#define CCircularEEPROM_H
#include <Arduino.h>
#include <EEPROM.h>

#define CC_START_POINT_1 0
#define CC_END_POINT_1 511

//#define CC_START_POINT_2 512
//#define CC_END_POINT_2 1023


class CCircularEEPROM {

  uint16_t Find, Bind, ind;
  uint16_t Start, cstart, cend;

  public:
    CCircularEEPROM(uint16_t start, uint16_t endd, bool _new=false);
    void Backward_Retrieve(char* Backward_Word,uint16_t d=0);
    void Forward_Retrieve(char* Forward_Word,uint16_t d=0);
    void save_index();
    uint16_t Save_Msg(char* temp);
    uint16_t Get_Index(char mode='a');
    uint16_t Get_Findex();
    uint16_t Get_Bindex();
    void Reset();
    void CC_Scan();

};
#endif