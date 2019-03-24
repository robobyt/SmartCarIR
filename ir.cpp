#include "pxt.h"
#include <map>
#include <vector>
#include "ReceiverIR.h"
using namespace pxt;

enum class RemoteButton {
      Red = 0,
      Red_Yellow = 1,
      Yellow = 4,
      Green = 2,
      Green_Blink = 5,
      Stop = 6,
      Crosswalk = 3,
      Power = 69,
      Up = 64,
      Left = 7,
      Right = 9,
      Down = 25,
      NUM0 = 22,
      NUM1 = 12,
      NUM2 = 24,
      NUM3 = 94,
      NUM4 = 8,
      NUM5 = 28,
      NUM6 = 90,
      NUM7 = 66,
      NUM8 = 82,
      NUM9 = 74
};

//% color=#DF013A weight=20 icon="\uf1eb"
namespace infrared { 
  mbed::Timer tsb; 
  uint8_t buf[32];
  uint32_t now;
  ReceiverIR *rx;
  bool alreadyInit=0;
  RemoteIR::Format fmt = RemoteIR::UNKNOWN;
  map<RemoteButton, std::vector<Action>> actions;
  map<RemoteButton, uint32_t> lastact;
  int msg;
  int IRcallbackNum;

 void cA(std::vector<Action> runner){for(int i=0;i<runner.size();i++){runAction0(runner[i]);} }

  void onReceivable(){
    int x = rx->getData(&fmt, buf, 32 * 8);
    now = tsb.read_ms();
    if(now - lastact[(RemoteButton)buf[2]] < 100) return;
    lastact[(RemoteButton)buf[2]] = now;
    msg=(int)buf[2];
    cA(actions[(RemoteButton)buf[2]]);
  }

  void monitorIR(){
    while(1){
      while(rx->getState() != ReceiverIR::Received){ 
        fiber_sleep(50);
      }
      onReceivable();
    }
  }

  //%
  void initIR(){
     if(alreadyInit==1){
            return;
        }
    alreadyInit=1;
    rx = new ReceiverIR(PA_7);
    tsb.start(); //interrupt timer for debounce
    create_fiber(monitorIR);
  }

  /**
  * button pushed.
  */
  //% group="IR"
  //% blockId=ir_received_left_event
  //% block="on |%btn| remote button pressed"
  void onPressEvent(RemoteButton btn, Action body) {
    initIR();
    actions[btn].push_back(body);
  }

  /**
  * initialises local variablesssss
  */
  //% group="IR"
  //% blockId=IR_read block="read IR"
  int getParam(){
    initIR();
    return msg;
  }
}
