#include <iostream>
#include <fstream>
#include "HierarchicalList.h"

/* Добавить элемент в определённую позицию.
   Считываем значимость элемента.
   Сравниваем по очереди со значимостями уже присутвуующих элементов
   Выявить индекс элемента большей значимости или такой же и вставить перед ним.
   Если такого нету вставить в конец.
*/

HierarchicalList::HierarchicalList(std::string folder, std::string file) 
							: HierarchicalList() {
  read(folder+"/"+file);
  
}

void HierarchicalList::add_element(int r, std::string c) {
  Element e{c,r};
  add_element(e);  
}
   
void HierarchicalList::add_element(Element& e) { 
  if (!hlist.empty()) {
    int i{0};
    for (Element& he : hlist) {
      if (he.get_rate() > e.get_rate()) {
        hlist.insert(hlist.begin() + i, e);
        return;
      }
      ++i;
    }   
  }
  hlist.push_back(e);
}


/* !! ToDo: Check arguments and optimize functions */
void HierarchicalList::set_rate(int pos, int rate) {
  if (pos >=0 && pos < hlist.size() && rate != hlist[pos].get_rate()) {
    
    int new_pos;
    new_pos = get_position_rate_first(rate);

    Element e;
    e = get_element(pos);
    e.set_rate(rate);

    if (new_pos >= hlist.size()) { 
      hlist.push_back(e); 
      //hlist.erase(hlist.begin() + pos);
    }
    else {
      hlist.insert(hlist.begin() + new_pos, e); 
      //hlist.erase(hlist.begin() + pos + 1);
    }
    
    if (new_pos > pos) {
      hlist.erase(hlist.begin() + pos);
    }
    else {
      hlist.erase(hlist.begin() + pos + 1);
    } 
    /* std::cout << "SET: pos = " << pos << ", new_pos = " << new_pos
              << ", rate = " << rate << std::endl; */

  }
}

//Do nothing if wrong position. Write about this?
void HierarchicalList::set_content(int pos, std::string c) {
  if (pos >=0 && pos < hlist.size()) {
    hlist[pos].set_content(c);
  }
  else {
    std::cout << "Wrong position" << std::endl;
  }
}

void HierarchicalList::up_rate(int pos) {
  int current_rate = hlist[pos].get_rate();
  int desired_rate = --current_rate;
  set_rate(pos, desired_rate);
}

void HierarchicalList::down_rate(int pos) {
  int current_rate = hlist[pos].get_rate();
  int desired_rate = ++current_rate;
  set_rate(pos, desired_rate);

}

/* User should check range of position before calling */
void HierarchicalList::remove(int pos) {
  hlist.erase(hlist.begin() + pos);
}

/*???*/
int HierarchicalList::get_position_rate_first(int r) {
  if (r>=0) {
    int i{0};
    for (Element &e : hlist) {
      if (e.get_rate() >= r) return i;
      ++i;
    }
    return i;
  }
  return -1;
}

/*???*/
int HierarchicalList::get_position_rate_last(int r) {
  if (r>=0) {
    int i{0};
    int last_rate{-1};
    for (Element &e : hlist) {
      if (e.get_rate() > r && last_rate == r) return i-1;
      last_rate = e.get_rate();
      ++i;
    }
    if (hlist.back().get_rate() == r) return i-1;    
  }
  return -1;

}


std::vector<Element> HierarchicalList::get_elements_with_rate(int r) {
  std::vector<Element> output;
  for(Element& e : hlist) {
    if (e.get_rate() == r) {
      output.push_back(e);
    }
  }
  return output;
}


std::vector<Element> HierarchicalList::operator[](int index) {
  return get_elements_with_rate(index);
}

void HierarchicalList::clean() {
  hlist.clear();
}

bool HierarchicalList::write() {
  std::string ofile;
  ofile = LIST_FOLDER + name + ".lst";
  std::cout << "Writing file <" << ofile << "> ";
  std::ofstream ost{ofile};
  if (!ost) {
    std::cout << "FAILED." << std::endl;
    return false;
  }
  ost << name << std::endl;
  for (Element& e : hlist) {
    ost << e << std::endl;
  }
  std::cout << "DONE." << std::endl;
  return true;
}

bool HierarchicalList::read(std::string f) {
   std::cout << "Reading from file <" << f <<"> ";
   std::ifstream ifs{f};
   if (!ifs) {
     std::cout << "FAILED." << std::endl;
     return false;
   }
   std::string n;
   if (ifs >> n) {
     name = n;
     for (Element e; ifs >> e;) {
       add_element(e);
     }
     std::cout << "DONE." << std::endl;
   }
   else {
     std::cout << "FAILED." << std::endl;
     return false;
   }
   return true;
}

void HierarchicalList::print() {
  std::cout << "<" << name << ">:" << std::endl << std::endl;
  for (int i = 0; i < hlist.size(); ++i) {
    std::cout << "\t{" << i <<"} " << hlist[i] << std::endl;
  }
  std::cout << std::endl <<  "Number of elements: " 
        << hlist.size() << std::endl;
}

std::istream& operator>>(std::istream& is, HierarchicalList& hl) {
  std::string n;
  is >> n;
  hl.set_name(n);
  Element e;
  while (is >> e) {
    hl.add_element(e);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const HierarchicalList& hl) {
  os << hl.get_name() << std::endl;
  for (int i = 0; i < hl.size(); ++i) {
    os << hl.get_element(i) << std::endl;
  }
  return os;
}

