#ifndef HIERARCHICAL_LIST_H
#define HIERARCHICAL_LIST_H

#include <vector>
#include "Element.h"

#define LIST_FOLDER "./lists/"

class HierarchicalList {

  private:
    std::vector<Element> hlist;
    std::string name;
  public:
    HierarchicalList() : name{"UNDEFINED_NAME"} { }
    HierarchicalList(std::string n) : name{n} { }
    HierarchicalList(std::string folder, std::string file);
    
    std::string get_name() const { return name; }
    void set_name(std::string n) { name = n; }
    void add_element(Element& e);
    void add_element(std::string c, int r);
    /*void add_element_to_end(Element& e);
    void add_element_to_begin(Element& e);
    void add_element_to_position(Element& e, int pos);
    void add_element_to_end_shifted(Element& e);
    void add_element_to_begin_shifted(Element& e);
    void add_element_to_position_before(Element& e, int pos);
    void add_element_to_position_after(Element& e, int pos);
    */
    void swap_elements(int pos1, int pos2); 
    int size() const { return hlist.size(); }
    void print();
    bool write();
    void clean();
    bool read(std::string f);
    void up_rate(int pos);
    void down_rate(int pos);    
    void set_rate(int pos, int rate);
    void remove(int pos);
    int get_position_rate_first(int r);
    int get_position_rate_last(int r);
   
    Element& get_element(int pos) { return hlist[pos]; }
    Element get_element(int pos) const { return hlist[pos]; }
    std::vector<Element> get_elements_with_rate(int r);
    std::vector<Element> operator[](int index);
};

std::istream& operator>>(std::istream& is, HierarchicalList& hl);
std::ostream& operator<<(std::ostream& os, const HierarchicalList& hl);

#endif /*HierarchicalList.h*/
