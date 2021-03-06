#ifndef DEZYNE_RUNTIME_HH
#define DEZYNE_RUNTIME_HH

#include "meta.hh"
#include "locator.hh"

#include "pump.hh"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <tuple>

namespace dezyne
{
void trace_in(std::ostream&, port::meta const&, const char*);
void trace_out(std::ostream&, port::meta const&, const char*);

inline void apply(const dezyne::meta* m, const std::function<void(const dezyne::meta*)>& f)
{
  f(m);
  for (auto c : m->children)
  {
    apply(c, f);
  }
}

inline void check_bindings(const dezyne::meta* c)
{
  apply(c, [](const dezyne::meta* m){
      std::for_each(m->ports_connected.begin(), m->ports_connected.end(), [](const std::function<void()>& p){p();});
    });
}

inline void dump_tree(std::ostream& os, const dezyne::meta* c)
{
  apply(c, [&](const dezyne::meta* m){
      os << path(m) << ":" << m->type << std::endl;
    });
}

struct runtime
{
  std::map<void*, std::tuple<bool, void*, std::queue<std::function<void()> >, bool> > queues;

  bool external(void*);
  bool& handling(void*);
  void*& deferred(void*);
  std::queue<std::function<void()> >& queue(void*);
  bool& performs_flush(void* scope);
  void flush(void*);
  void defer(void*, void*, const std::function<void()>&);
  template <typename T>
  struct scoped_value
  {
    T& current;
    T initial;
    scoped_value(T& current, T value)
    : current(current)
    , initial(current)
    { current = value; }
    ~scoped_value()
    {
      current = initial;
    }
  };
  template <typename L, typename = typename std::enable_if<std::is_void<typename std::result_of<L()>::type>::value>::type>
  void handle(void* scope, L&& l)
  {
    bool& handle = handling(scope);
    if(handle) throw std::logic_error("component already handling an event");
    {scoped_value<bool> sv(handle, true);
      l();}
    flush(scope);
  }
  template <typename L, typename = typename std::enable_if<!std::is_void<typename std::result_of<L()>::type>::value>::type>
  inline auto handle(void* scope, L&& l) -> decltype(l())
  {
    bool& handle = handling(scope);
    if(handle) throw std::logic_error("component already handling an event");
    decltype(l()) r;
    {scoped_value<bool> sv(handle, true);
      r = l();}
    flush(scope);
    return r;
  }
  runtime();
private:
  runtime(const runtime&);
  runtime& operator = (const runtime&);
};

template <typename F, typename ... Args>
auto shell(dezyne::pump& pump, F&& f, Args&& ...args) -> decltype(f())
{
  return pump.and_wait(std::bind(f,std::forward<Args>(args)...));
}

template <typename C>
struct call_helper
{
  C* c;
  std::ostream& os;
  const dezyne::port::meta& meta;
  const char* event;
  std::string reply;
  call_helper(C* c, const dezyne::port::meta& meta, const char* event)
  : c(c)
  , os(c->dzn_locator.template get<typename std::ostream>())
  , meta(meta)
  , event(event)
  , reply("return")
  {
    trace_in(os, meta, event);
    if(c->dzn_rt.handling(c))
    {
      c->dzn_locator.template get<dezyne::pump>().collateral_block();
    }
  }
  template <typename L, typename = typename std::enable_if<std::is_void<typename std::result_of<L()>::type>::value>::type>
  void operator()(L&& l)
  {
    c->dzn_rt.handle(c, l);
  }
  template <typename L, typename = typename std::enable_if<!std::is_void<typename std::result_of<L()>::type>::value>::type>
  auto operator()(L&& l) -> decltype(l())
  {
    auto r = c->dzn_rt.handle(c, l);
    reply = to_string(r);
    return r;
  }
  ~call_helper()
  {
    trace_out(os, meta, reply.c_str());
  }
};

template <typename C, typename L>
auto call_in(C* c, L&& l, const dezyne::port::meta& meta, const char* event) -> decltype(l())
{
  call_helper<C> helper(c, meta, event);
  return helper(l);
}

template <typename C, typename L>
void call_out(C* c, L&& l, const dezyne::port::meta& meta, const char* event)
{
  auto& os = c->dzn_locator.template get<typename std::ostream>();
  trace_out(os, meta, event);
  c->dzn_rt.defer(meta.provides.address, c, l);
}
}
#endif //DEZYNE_RUNTIME_HH
