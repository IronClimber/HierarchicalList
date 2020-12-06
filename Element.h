#ifndef ELEMENT_H
#define ELEMENT_H


// rate = 0 -> UNDEFINED RATE

#include <string>
#include <iostream>

#define UNDEFINED_RATE 0
#define UNDEFINED_CONTENT "???"

class Element {

  std::string content;
  int rate;

  public:

    Element(std::string s, int r);
    Element(std::string s);
    Element(int r);
    Element();
    
    /* 
       try {
         Element(-3, "fewfwf");
       }
       catch(Element::Invalid) {
         error("Wrong rate");
       }
    */
        
    class Invalid { };

    int get_rate() const { return rate; }
    bool set_rate(int r);
    bool up_rate();
    bool down_rate();    
    void set_content(std::string s) { content = s; }
    std::string get_content() const { return content; }
    
    //operator>
    //operator<
    void operator=(const Element& other);


};

    bool operator==(const Element& e1, const Element& e2);
    bool operator!=(const Element& e1, const Element& e2);
    std::ostream& operator<<(std::ostream& os, const Element& e);
    std::istream& operator>>(std::istream& is, Element& e);
#endif /* Element.h */
