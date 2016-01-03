#include "timer.hh"

#include "locator.hh"
#include "runtime.hh"
#include "pump.hh"

namespace dezyne
{
  timer::timer(const locator& l)
  : rt(l.get<runtime>())
  , port()
  {
	static size_t g_id = 0;
	size_t id = g_id++;
	port.in.create = [&,id]{l.get<pump>().handle(id, 100, port.out.timeout); };
	port.in.cancel = [&,id]{l.get<pump>().remove(id); };
  }
}
