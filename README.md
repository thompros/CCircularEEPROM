# CCircularEEPROM
Circular queue data structure using Arduino's EEPROM 

Data: char arrays

## Problem to be solved
A sensor provides data every X seconds. We want to store its N last data. If we stored this data into the RAM (of an arduino) then we would probably run out of memory. 

Solution: create an object of the CCircularEEPROM class and thus the N data are stored there continously.

## Schematic Diagram

![schem](https://user-images.githubusercontent.com/131445812/236678293-0fdcb670-87dc-410a-a17d-baaf2beda8e8.jpg)



## Download
Download zip file and then unzip it inside of directory: C:\Users\ ... \Documents\Arduino\libraries 


## Initialization

- Open CCircularEEPROM.h file
- Declare the number of circular queue instances and the boundaries for each one
- After you saved these informations, Open Arduino IDE, go to: file -> Examples -> CCircularEEPROM -> INITIALIZE_CCircularEEPROM_objects.ino
- Upload this sketch to your Arduino board

> **Note:** If you don't change **'CCircularEEPROM.h'** file, then 1 circular queue of 510 data bytes is initialized + 2 status bytes (fixed), allocating 512 bytes of Arduino's eeprom.

## Object Methods


   
1. Constructor
    ```ruby
    CCircularEEPROM(uint16_t start, uint16_t endd, bool _new=false); 
    ```
    ```start```, ```endd``` arguments define the length of the CCEEPROM queue. Set ```_new``` argument as ```true``` at initialization  of a new instance. In this way you reset any data may had been stored between [start , endd] and the index ```ind``` points at the first data cell. If a CCEEPROM object is declared using argument ```_new=false``` (when the CCEEPROM structure was initialized in previous sketch) the object's current index ```ind``` retrieves its initial value from status cells.

2. Functions
   ```ruby
    uint16_t Save_Msg(char* temp);
    ```
     It is used to store a word in the CCEEPROM. The argument ```char* temp ``` is used to acces the char array where data (word) is temporarily stored in RAM. This function resets the indexes ```Find``` (Forward word index) and ```Bind``` (Backward word index) (both now pointing at the position into which the null character of the CCEPROM-inserted word is stored -this value is returned-). After each word registration the function also updates the value of index ```ind``` pointing ```+ 1``` position from indexes ```Bind, Find```.
     
    ```ruby
    uint16_t Get_Index(char mode='a');
    ```
     Calling it without argument, returns the current position of index ```ind``` value. This value is stored into a ```uint16_t``` variable which is stored (typically) into RAM memory. Powering-off arduino and powering it on again, a call to this function returns the last one index ```ind``` value which was saved into the status cells of CCEEPROM structure. Call this function with any argument except ```'a'``` to figure out what is the stored value of index ```ind``` in the status cells.
     
    ```ruby
    void save_index();
    ```
     It is used in order to save, into the status cells of the CCEEPROM structure, the current index ```ind``` value. In this way we can update the status cells, making sure that no data will be lost if arduino board loses power. The update of status cells every time a call to ```Save_Msg(char* temp);``` taking place, will reduce the lifespan of eeprom status cells (about 100.000 W-cycles). 
     
    ```ruby
    void Backward_Retrieve(char* Backward_Word,uint16_t d=0);
    ```
     It is used to fill a char array with saved word, reading it backwards from index ```ind```position. The argument ```char* Backward_Word``` is used to access and modify the char array data, (loads CCEPROM data cells -word bytes- into RAM saved char array). The argument ```uint16_t d=0``` can be filled with another value indicating the desired position of CCEEPROM data (word) retrieval (not to retrieve the word backwards from index ```ind``` position). Every time we use this function the ```ind``` index remains the same (cause it is the header), but the ```Find, Bind``` update correspondingly (between their values there is a stored word).
    
    ```ruby
    uint16_t Get_Bindex();
    ```
     Returns the position of the ```Bind``` index. (Bind=Backward word index)
    ```ruby
    void Forward_Retrieve(char* Forward_Word,uint16_t d=0);
    ```
     It is used to fill a char array with saved words, reading them forwards from index ```ind```position. The argument ```char* Forward_Word``` is used to access and modify the char array data, (loads CCEPROM data cells -word bytes- into RAM saved char array). The argument ```uint16_t d=0``` can be filled with another value indicating the desired position of CCEEPROM data retrieval (not to retrive the word forward from index ```ind``` position). Every time we use this function the ```ind``` index remains the same (cause it is the header), but the ```Find, Bind``` update correspondingly (between their values there is a stored word).
    ```ruby
    uint16_t Get_Findex();
    ```
     Returns the position of the ```Find``` index. (Find=Forward word index)
    ```ruby
    void CC_Scan();
    ```
     Outputs in the Serial monitor the memory map of the CCEEPROM object
    ```ruby
    void Reset();  
    ```
     Resets-clearing all data cells and status cells of CCEEPROM object.
     
## NOTES
- Upload INITIALIZE_CCircularEEPROM_objects.ino sketch to initialize your desired CCEEPROM structure(s).
- After INITIALIZATION, you may use GLOBAL CCEEPROM object(s) (with the same parameters as it was initialazed) in your sketch.
- You may use interrupt driven routines where you call 
    ```ruby
    uint16_t Save_Msg(char* temp);
    ```
  for saving data.
- Save the index ```ind``` when necessary.
- Knowing the number of W-cycles of arduino eeprom cells (100.000) and the frequency of writing data into the CCEEPROM structure, you can calculate when one entire cycle is completed (indicates one W-cycle for all data cells) and also make a aproximation of lifespan for the CCEEPROM structure.
- When the data saving process fails, a message is displayed in Serial Monitor and the code halts (entered an infinate while loop).
- With the use of C++ / C library functions you can convert other data types (floats, integers etc) into character tables and then import them into the CCEEPROM structure.
    
    
    
   
   
     


