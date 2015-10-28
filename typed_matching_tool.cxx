//g++ -std=c++11 -o typed_matching_tool typed_matching_tool.cxx
#include <iostream>
#include <vector>

struct IParticle{};

struct typeA : public IParticle{
  typeA(double pt) : m_pt(pt) {}
  double ptA()const{return m_pt;}
  void hello(){std::cout << "pt: " << ptA() << std::endl;}
  double m_pt;
};
struct typeB : public IParticle{
  typeB(double pt) : m_pt(pt) {}
  double ptB()const{return m_pt;}
  void hello(){std::cout << "pt: " << ptB() << std::endl;}
  double m_pt;
};
struct typeC : public IParticle{
  typeC(double pt) : m_pt(pt) {}
  double ptC()const{return m_pt;}
  void hello(){std::cout << "pt: " << ptC() << std::endl;}
  double m_pt;
};
struct typeD : public IParticle{
  typeD(double pt) : m_pt(pt) {}
  double ptD()const{return m_pt;}
  void hello(){std::cout << "pt: " << ptD() << std::endl;}
  double m_pt;
};

struct trigA{
  trigA(double pt = 0) : m_pt(pt) {}
  double pt()const{return m_pt;}
  double m_pt;
};
struct trigB{
  trigB(double pt = 0) : m_pt(pt) {}
  double pt()const{return m_pt;}
  double m_pt;
};
struct trigC{
  trigC(double pt = 0) : m_pt(pt) {}
  double pt()const{return m_pt;}
  double m_pt;
};
struct trigD{
  trigD(double pt = 0) : m_pt(pt) {}
  double pt()const{return m_pt;}
  double m_pt;
};

namespace Registry{
  template<typename T> struct typeMap;
  template<> struct typeMap<typeA>{typedef trigA type;};
  template<> struct typeMap<typeB>{typedef trigB type;};
  template<> struct typeMap<typeC>{typedef trigC type;};
};


//general purpose storage for a single type
template<typename T> using Storage = std::vector<T>;
//recursing case
template <typename... RECOTYPES>
struct RecoCombo;

template <typename FIRST, typename... REST>
struct RecoCombo<FIRST,REST...> : public Storage<FIRST>, public RecoCombo<REST...> {
  //define list of types for later reference
  typedef std::tuple<FIRST,REST...> typelist;

  RecoCombo(){
  }

  RecoCombo(std::initializer_list<FIRST> first, std::initializer_list<REST>... rest) : RecoCombo<REST...>(rest...){
    push_collection(first);
  }

  template<typename T>
  void push_collection(const std::vector<T>& v){
    auto& s = *(static_cast<Storage<T>*>(this));
    s.insert(s.end(),v.begin(),v.end());    
  }

  template<typename T>
  void push_collection(const std::initializer_list<T>& vl){
    std::vector<T> v = vl;
    push_collection(v);
  }

  template<typename T>
  void push_back(T t){
    std::cout << "pushing" << std::endl;
    static_cast<Storage<T>*>(this)->push_back(t);
  }
  template<typename T>
  const Storage<T>& get() const {
    return *(static_cast<const Storage<T>*>(this));
  }
};
//base case
template <typename T>
struct RecoCombo<T> : public Storage<T> {
  RecoCombo(const std::initializer_list<T> list){
    std::vector<T> v = list;
    this->insert(this->begin(),v.begin(),v.end());
  }
};

template<typename... RECO>
RecoCombo<RECO...> make_reco(std::initializer_list<RECO>... initlists){
  return RecoCombo<RECO...>(initlists...);
}

struct MatchMetrics{
  double distance(const typeA& reco, const trigA& trig){
    std::cout << "A-type metric reco: " << reco.ptA() << " trig: " << trig.pt() << std::endl;
    return 0;
  }

  double distance(const typeB& reco, const trigB& trig){
    std::cout << "B-type metric reco: " << reco.ptB() << " trig: " << trig.pt() << std::endl;
    return 0;
  }

  double distance(const typeC& reco, const trigC& trig){
    std::cout << "C-type metric reco: " << reco.ptC() << " trig: " << trig.pt() << std::endl;
    return 0;
  }
};

struct tool{
  template<typename RECO,typename TRIGGER>
  std::vector<std::vector<double> > makeDistanceMatrix(const std::vector<RECO> recs, const std::vector<TRIGGER>& trigs){
    std::cout << "making distance matrix" << std::endl;
    std::cout << "size of recos: " << recs.size() << std::endl;
    std::cout << "size of trigs: " << trigs.size() << std::endl;
    MatchMetrics m;
    
    for(auto r : recs){
      for(auto t : trigs){
        std::cout << "distance is: " << m.distance(r,t) << std::endl;
      }
    }
    std::vector<std::vector<double> > matrix;
    return matrix;
  }

  template<typename T>
  void matchTypes(const Storage<T>& recos){
    std::cout << "single one " << typeid(T).name() << std::endl;
    std::cout << "recos size is: " << recos.size() << std::endl;

    typedef typename Registry::typeMap<T>::type trigType;
    std::cout << "trigger type is: " << typeid(trigType).name() << std::endl;

    std::vector<trigType> triggerObjs(recos.size());
    auto distance_matrix = makeDistanceMatrix(recos,triggerObjs); 
  }

  template<typename FIRST, typename... REST>
  typename std::enable_if<(sizeof...(REST)>0)>::type matchTypes(const RecoCombo<FIRST,REST...>& rcombo){
    matchTypes<FIRST>(rcombo.template get<FIRST>());
    const RecoCombo<REST...>& restcomb = rcombo;
    matchTypes<REST...>(restcomb);
  }

  template<typename... TYPES>
  void matchReco(const RecoCombo<TYPES...>& rcombo,const std::string& chain){
    matchTypes(rcombo);
  }

  template<typename T>
  void matchReco(const std::initializer_list<T>& initlist,const std::string& chain){
    matchTypes(make_reco(initlist));
  }

  void matchReco(const std::vector<IParticle*> parts,const std::string& chain){
  }
};


template<typename T>
struct makeTrig{typedef typename Registry::typeMap<T>::type type;};

template<typename... RECOTYPES> struct shit{
  typedef std::tuple<typename makeTrig<RECOTYPES>::type...> trigtypes;
};

template<typename... TYPES> struct make_initlists{
  typedef std::tuple<std::initializer_list<TYPES>...> initlists;
};

template<typename T>
struct lambda_init_metric{
  lambda_init_metric(const T& lambda) : m_lambda(lambda){}
  template<typename RECO,typename TRIG>
  double distance(const RECO& r, const TRIG& t){return select(r,t)(r,t);}

  template<typename RECO,typename TRIG> T select(const RECO& r, const TRIG& t){
    return (m_lambda(r,t), m_lambda);
  }

  const T& m_lambda;
};
template<typename T> lambda_init_metric<T> make_metric(T t){return lambda_init_metric<T>(t);}

int main(){
  typeA a(1.3);
  typeA a2(0.3);
  typeB b(5.3);
  typeB b2(1.4);
  typeC c(4.3);
  typeD d(3.6);

  auto pa = &a;
  auto pa2 = &a2;
  auto pb = &b;
  auto pb2 = &b2;
  auto pc = &c;
  auto pd = &d;
  
  auto metric = [](const typeA& reco, const trigA trig) -> double {
    std::cout << "lambda A-type metric reco: " << reco.ptA() << " trig: " << trig.pt() << std::endl;
    return 1.3;
  };
  // std::cout << "metric: " << typeid(any<decltype(metric)>::type).name() << std::endl;

  auto m = make_metric([](const typeA& reco, const trigA trig) {return reco.ptA() + trig.pt();});
  std::cout << m.distance(a,trigA()) << std::endl;

  
  tool t;
  t.matchReco(make_reco({a,a2},{b,b2},{c}),"HLT_one_two");
  t.matchReco({a,a2},"HLT_one_two");
  t.matchReco({pa,pa2,pb,pb2,pc,pd},"HLT_three");
};

