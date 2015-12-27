#include <stdio.h>
#include "SensorMonitor.hh"
#include <iostream>
#include "runtime.hh"
#include "locator.hh"
#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
void sigterm(int signum) { std::cout << "sigterm"; }
const int pin = 11;

typedef void function_t( void ) ;

std::shared_ptr<SensorMonitor> mySensorMonitor;

void wPiTriggered(void) 
{ 
  std::cout << "wPiTriggered"; 
  mySensorMonitor->sensorRequired.out.triggered();      
}

int main(int argc, char **argv)
{
  std::cout << "START" << std::endl;  
  
  dezyne::locator loc;
  dezyne::runtime rt;
  loc.set(rt); 
  mySensorMonitor = std::make_shared<SensorMonitor>(loc);

  struct sigaction sigact; 
  memset(&sigact, 0, sizeof(struct sigaction));
  sigact.sa_handler = sigterm; 
  sigaction(SIGTERM, &sigact, NULL);
  
  wiringPiSetup();
  wiringPiISR(pin, INT_EDGE_RISING, wPiTriggered);

  mySensorMonitor->sensorMonitorProvided.out.triggerDetected = []{
    std::cout << "sensorMonitorProvided.out.triggerDetected" << std::endl;
  };  

  mySensorMonitor->sensorRequired.in.enable = []{
    std::cout << "sensor enable" << std::endl;
  };  

  mySensorMonitor->sensorRequired.in.disable = []{
    std::cout << "sensor disable" << std::endl;
  };  
  
  mySensorMonitor->sensorMonitorProvided.in.enable();  

  getchar();

  mySensorMonitor->sensorMonitorProvided.in.disable();
   
  std::cout << "END" << std::endl;    
	return 0;
}