// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "SensorMonitor.hh"

#include "locator.hh"
#include "runtime.hh"


SensorMonitor::SensorMonitor(const dezyne::locator& dezyne_locator)
: dzn_meta{"","SensorMonitor",0,{},{[this]{sensorMonitorProvided.check_bindings();},[this]{sensorRequired.check_bindings();},[this]{ledRequired.check_bindings();}}}
, dzn_rt(dezyne_locator.get<dezyne::runtime>())
, dzn_locator(dezyne_locator)
, state(State::Disabled)
, sensorMonitorProvided{{{"sensorMonitorProvided",this,&dzn_meta},{"",0,0}}}
, sensorRequired{{{"",0,0},{"sensorRequired",this,&dzn_meta}}}
, ledRequired{{{"",0,0},{"ledRequired",this,&dzn_meta}}}
{
  dzn_rt.performs_flush(this) = true;
  sensorMonitorProvided.in.enable = [&] () { return dezyne::call_in(this, [&]{return sensorMonitorProvided_enable();}, this->sensorMonitorProvided.meta, "enable"); };
  sensorMonitorProvided.in.disable = [&] () { return dezyne::call_in(this, [&]{return sensorMonitorProvided_disable();}, this->sensorMonitorProvided.meta, "disable"); };
  sensorRequired.out.triggered = [&] () { return dezyne::call_out(this, [=]{return sensorRequired_triggered();}, this->sensorRequired.meta, "triggered"); };

}

void SensorMonitor::sensorMonitorProvided_enable()
{
  if (this->state == State::Disabled)
  {
    {
      this->sensorRequired.in.enable();
      this->state = State::Enabled;
    }
  }
  else if (this->state == State::Enabled)
  {
    dzn_locator.get<dezyne::illegal_handler>().illegal();
  }
}

void SensorMonitor::sensorMonitorProvided_disable()
{
  if (this->state == State::Disabled)
  {
    dzn_locator.get<dezyne::illegal_handler>().illegal();
  }
  else if (this->state == State::Enabled)
  {
    {
      this->sensorRequired.in.disable();
      this->state = State::Disabled;
    }
  }
}

void SensorMonitor::sensorRequired_triggered()
{
  if (this->state == State::Disabled)
  {
    dzn_locator.get<dezyne::illegal_handler>().illegal();
  }
  else if (this->state == State::Enabled)
  {
    {
      this->sensorMonitorProvided.out.triggerDetected();
      this->state = State::Enabled;
    }
  }
}


void SensorMonitor::check_bindings() const
{
  dezyne::check_bindings(&dzn_meta);
}
void SensorMonitor::dump_tree(std::ostream& os) const
{
  dezyne::dump_tree(os, &dzn_meta);
}

