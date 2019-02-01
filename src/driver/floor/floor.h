/*
 * floor.h
 *
 *      Author: Baram
 */

#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <Arduino.h>




class Floor 
{
  public:
    Floor();
    ~Floor();
    
    bool begin(void);
    void update(void);
    
    uint16_t getLeftIn(void);
    uint16_t getLeftOut(void);

    uint16_t getRightIn(void);
    uint16_t getRightOut(void);

  private:
};



#endif