#ifndef LAMBDAINITMETRIC_H
#define LAMBDAINITMETRIC_H

template<typename... LAMBDATYPES> struct lambda_init_metric;
template<typename... TYPES> lambda_init_metric<TYPES...> make_metric(TYPES... t){return lambda_init_metric<TYPES...>(t...);}

template<typename... LAMBDATYPES>
struct lambda_init_metric{
  template<typename RECO,typename TRIG>
  constexpr static bool supports(){return (select<RECO,TRIG>() >=0 );}

  lambda_init_metric(const LAMBDATYPES&... lambdas) : m_lambdas(lambdas...){}
  template<typename RECO,typename TRIG>
  typename std::enable_if<supports<RECO,TRIG>(),double>::type distance(const RECO& r, const TRIG& t) const {
    constexpr static int bla(select<RECO,TRIG>());
    return std::get<bla>(m_lambdas)(r,t);
  }

  template<typename RECO,typename TRIG, int index = sizeof...(LAMBDATYPES)-1>
  constexpr static typename std::enable_if<(index>0),int>::type select() {
    typedef typename std::tuple_element<index,decltype(m_lambdas)>::type element_t;
    typedef std::function<double (const RECO& r, const TRIG& t)> function_t;
    return std::is_constructible<function_t,element_t>::value ? index : select<RECO,TRIG,index-1>();
  }
  
  template<typename RECO,typename TRIG, int index = sizeof...(LAMBDATYPES)-1>
  constexpr static typename std::enable_if<(index==0),int>::type select() {
    return selectBase<RECO,TRIG,0>();
  }

  template<typename RECO,typename TRIG, int index>
  constexpr static int selectBase() {
    typedef typename std::tuple_element<index,decltype(m_lambdas)>::type element_t;
    typedef std::function<double (const RECO& r, const TRIG& t)> function_t;
    return std::is_constructible<function_t,element_t>::value ? index : -1;
  }
  std::tuple<LAMBDATYPES...> m_lambdas;
};

#endif