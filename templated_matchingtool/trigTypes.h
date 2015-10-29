#ifndef TRIGTYPES_H
#define TRIGTYPES_H
struct trigA{
  trigA(double pt = 10,double eta = 11,double phi = 12) : m_pt(pt),m_eta(eta),m_phi(phi) {}
  double pt()const{return m_pt;}
  double eta()const{return m_eta;}
  double phi()const{return m_phi;}
  double m_pt;
  double m_eta;
  double m_phi;
};
struct trigB{
  trigB(double pt = 20,double eta = 21,double phi = 22) : m_pt(pt),m_eta(eta),m_phi(phi) {}
  double pt()const{return m_pt;}
  double eta()const{return m_eta;}
  double phi()const{return m_phi;}
  double m_pt;
  double m_eta;
  double m_phi;
};
struct trigC{
  trigC(double pt = 30,double eta = 31,double phi = 32) : m_pt(pt),m_eta(eta),m_phi(phi) {}
  double pt()const{return m_pt;}
  double eta()const{return m_eta;}
  double phi()const{return m_phi;}
  double m_pt;
  double m_eta;
  double m_phi;
};
struct trigD{
  trigD(double pt = 40,double eta = 41,double phi = 42) : m_pt(pt),m_eta(eta),m_phi(phi) {}
  double pt()const{return m_pt;}
  double eta()const{return m_eta;}
  double phi()const{return m_phi;}
  double m_pt;
  double m_eta;
  double m_phi;
};
#endif