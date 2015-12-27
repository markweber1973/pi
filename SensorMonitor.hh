#ifndef SENSORMONITOR_HH
#define SENSORMONITOR_HH

#include <iostream>

#include "ISensorMonitor.hh"
#include "ISensor.hh"


namespace dezyne {
  struct locator;
  struct runtime;
}


struct SensorMonitor
{
  dezyne::meta dzn_meta;
  dezyne::runtime& dzn_rt;
  dezyne::locator const& dzn_locator;
#ifndef ENUM_SensorMonitor_State
#define ENUM_SensorMonitor_State 1
  struct State
  {
    enum type
    {
      Disabled, Enabled
    };
  };
#endif // ENUM_SensorMonitor_State
  State::type state;
  std::function<void ()> out_sensorMonitorProvided;
  ISensorMonitor sensorMonitorProvided;
  ISensor sensorRequired;

  SensorMonitor(const dezyne::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;

  private:
  void sensorMonitorProvided_enable();
  void sensorMonitorProvided_disable();
  void sensorRequired_triggered();
};

#endif // SENSORMONITOR_HH
