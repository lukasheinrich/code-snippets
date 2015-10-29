#ifndef METRICOVERRIDE_H
#define METRICOVERRIDE_H


template<typename T, typename RECO, typename TRIG>
struct supports_metric{
  typedef char yes[1]; typedef char no[2];
  template <typename SIG,SIG> struct has_sig;
  template<typename C> static yes& test(has_sig<double (C::*) (const RECO&, const TRIG&) const,&C::distance>*);
  template<typename C> static no& test(...);
  static const bool value = sizeof(test<T>(0)) == sizeof(yes);  
};

template<typename OVER,typename DEFAULT>
struct Override{
  Override(const OVER& o, const DEFAULT& d) : m_over(o), m_default(d){};
  template<typename R,typename T>
  typename std::enable_if<supports_metric<OVER,R,T>::value,double>::type distance(const R& r,const T& t){return m_over.distance(r,t);}

  template<typename R,typename T>
  typename std::enable_if<!supports_metric<OVER,R,T>::value && supports_metric<DEFAULT,R,T>::value,double>::type distance(const R& r,const T& t){return m_default.distance(r,t);}

  const OVER& m_over;
  const DEFAULT& m_default;
};

template<typename OVER,typename DEFAULT>
Override<OVER,DEFAULT> make_override(const OVER& o, const DEFAULT& d){return Override<OVER,DEFAULT>(o,d);}
#endif