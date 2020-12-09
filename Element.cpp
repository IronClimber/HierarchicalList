#include "Element.h"

Element::Element() : rate{UNDEFINED_RATE}, content{UNDEFINED_CONTENT} { }
Element::Element(int r) : rate{r}, content{UNDEFINED_CONTENT} {
  if(r<0) throw Invalid{};
}
Element::Element(std::string s) : rate{UNDEFINED_RATE}, content{s} { }
Element::Element(std::string s, int r) : rate{r}, content{s} {
  if(r<0) throw Invalid{};
}

bool Element::up_rate() {
  if (rate>1) {--rate; return true;}
  return false;
}

bool Element::down_rate() {
  if (rate>=0) {++rate; return true;}
  return false;
}

bool Element::set_rate(int r) { 
  if(r>0) {rate = r; return true;}
  return false; 
}

bool operator==(const Element& e1, const Element& e2) {
  if(e1.get_rate()==e2.get_rate() && e1.get_content()==e2.get_content()) {
    return true;
  }
  return false;
}
bool operator!=(const Element& e1, const Element& e2) {
  return !(e1==e2);
}

std::ostream& operator<<(std::ostream& os, const Element& e) {
  return os << "[" << e.get_rate() << "] "
            << e.get_content();
}

std::istream& operator>>(std::istream& is, Element& e) {
  int r;
  std::string n;
  char ch1, ch2;
  is >> ch1 >> r >> ch2;
  if (ch1 != '[' && ch2 != ']') {
    is.clear(std::ios_base::failbit);
    return is;
  }
  getline(is, n);
  char c{' '};
  int i{0};
  while (isspace(c)) {
    c = n[i];
    ++i;
  }
  std::string s = n.substr(i-1);
  e = Element(s, r);
  return is;
}

void Element::operator=(const Element& other) {
  set_rate(other.get_rate());
  set_content(other.get_content());
}

