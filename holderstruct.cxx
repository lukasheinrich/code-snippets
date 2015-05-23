//make with:  g++ -std=c++11 -o holderstruct holderstruct.cxx

#include <string>
#include <map>
#include <memory>
#include <iostream>

#include <boost/variant.hpp>

typedef uint32_t te_id_type;
typedef uint16_t sub_index_type;
typedef uint32_t index_type;
typedef uint32_t class_id_type;      
sub_index_type invalid_sub_index = 999;

struct BaseHolder{
public:
  BaseHolder(class_id_type clid, sub_index_type sti, const std::string& label) :
     m_clid(clid), m_subtypeindex(sti), m_label(label) {
     }
   virtual ~BaseHolder(){}
     
  class_id_type typeClid() const {return m_clid;}
  sub_index_type subTypeIndex() const {return m_subtypeindex;}
  std::string label() const { return m_label;}

private:
  class_id_type m_clid;
  sub_index_type m_subtypeindex;
  std::string m_label;
};


// Emacs -*- c++ -*-
#ifndef TRIGNAVSTRUCTURE_TRIGHOLDERSTRUCTURE
class HolderStructure{
public:
  bool registerHolder(const std::shared_ptr<BaseHolder>& holder);

  template<typename T = BaseHolder>
  T* getHolder(class_id_type clid, boost::variant<sub_index_type,std::string> stiOrLabel){    
    return getCastHolder<T>(m_holderByClidAndIndex[clid][getIndex(clid,stiOrLabel)].get());
  }

  sub_index_type getIndex(class_id_type clid, const boost::variant<sub_index_type,std::string>& stiOrLabel){
    return boost::apply_visitor(HolderStructure::subTypeVisitor(m_lookupSubIndex[clid]), stiOrLabel);    
  }
  
  // HolderType* getHolderForFeature(const TriggerElement::FeatureAccessHelper& fea){
  //   return getHolder(fea.getCLID(),fea.getIndex().subTypeIndex());
  // }

private:
  template<typename T>
  T* getCastHolder(BaseHolder* holder){
    if(!holder){
      return 0;
    }
    auto cast_holder = dynamic_cast<T*>(holder);
    if(!cast_holder){
      std::cout << "cast failed" << std::endl;
    }
    return cast_holder;
  }


  typedef std::map<sub_index_type, std::shared_ptr<BaseHolder> > IndexToHolderMap;
  typedef std::map<std::string, std::shared_ptr<BaseHolder> > LabelToHolderMap;
  typedef std::map<std::string,sub_index_type> LabelToSubIndexMap;
  
  class subTypeVisitor : public boost::static_visitor<sub_index_type>{
  public:
    subTypeVisitor(const LabelToSubIndexMap& lookup):m_lookup(lookup){}
    sub_index_type operator()(sub_index_type sti) const {return sti;}
    sub_index_type operator()(const std::string& label) const {
      auto it = m_lookup.find(label);
      return (it!=m_lookup.end()) ? it->second : invalid_sub_index;
    }
  private:
    const LabelToSubIndexMap& m_lookup;
  };

  std::map<class_id_type, IndexToHolderMap> m_holderByClidAndIndex;
  std::map<class_id_type, LabelToHolderMap> m_holderByClidAndLabel;

  std::map<class_id_type, std::map<sub_index_type, std::string> > m_lookupLabels;

  std::map<class_id_type, LabelToSubIndexMap >  m_lookupSubIndex;



};

bool HolderStructure::registerHolder(const std::shared_ptr<BaseHolder>& holder){ 
  auto clid = holder->typeClid();
  auto subtypeindex = holder->subTypeIndex();
  auto label = holder->label();

  if(getHolder(clid,subtypeindex)){
    std::cout << "ERROR: we already have a pointer like this!" << std::endl;
    return false;
  }

  m_holderByClidAndIndex[clid][subtypeindex] = holder;
  m_holderByClidAndLabel[clid][label] = holder;
  m_lookupLabels[clid][subtypeindex] = label;
  m_lookupSubIndex[clid][label] = subtypeindex;
  return true;
}

#endif


struct IHolder : public BaseHolder{
  using BaseHolder::BaseHolder;
  virtual ~IHolder(){}

  void what(){
    std::cout << "hello we are a derived holder" << std::endl;
  } 

};

template<typename T>
struct TypedHolder : public IHolder {
  using IHolder::IHolder;
  virtual ~TypedHolder(){
    std::cout << "...::deleting myself " << this->typeClid() << "/" << this->label() << "/" << this->subTypeIndex() << std::endl;
  }
  void say(const T& t){
    std::cout << "hello we are a typed holder: " << t << std::endl;
  }
};

std::shared_ptr<IHolder> createHolder(class_id_type clid, sub_index_type sti, const std::string& label){
  return std::shared_ptr<IHolder>(new IHolder(clid,sti,label));
}

template<typename T>
std::shared_ptr<TypedHolder<T> > createTypedHolder(class_id_type clid, sub_index_type sti, const std::string& label){
  return std::shared_ptr<TypedHolder<T> >(new TypedHolder<T>(clid,sti,label));
}

#include <iostream>
#include <assert.h>

int main(){
 
  HolderStructure holderstorage;
  holderstorage.registerHolder(createTypedHolder<double>(12345,0,"zeroth 12345"));
  holderstorage.registerHolder(createTypedHolder<double>(12345,1,"first 12345"));

  holderstorage.registerHolder(createTypedHolder<int>(9876,0,"zeroth 9876"));
  holderstorage.registerHolder(createTypedHolder<int>(9876,1,"first 9876"));

  holderstorage.registerHolder(createTypedHolder<std::string>(4567,0,"zeroth 4567"));


  std::cout << "double register" << std::endl;
  holderstorage.registerHolder(createTypedHolder<std::string>(4567,0,"zeroth 4567"));

  std::cout << "now check" << std::endl;
  
  auto holder1 = holderstorage.getHolder(12345,"first 12345");
  std::cout << holder1->typeClid() << "/" << holder1->label() << "/" << holder1->subTypeIndex() << std::endl;

  holderstorage.getHolder<IHolder>(12345,1)->what();
  holderstorage.getHolder<TypedHolder<double> >(12345,1)->say(3.141);
  holderstorage.getHolder<TypedHolder<int> >(9876,0)->say(3);
  holderstorage.getHolder<TypedHolder<std::string> >(4567,"zeroth 4567")->say("hello");
  
  return 0;
}