#ifndef RECOCOMBO_H
#define RECOCOMBO_H

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
#endif