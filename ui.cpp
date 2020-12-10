#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <boost/filesystem.hpp>
#include <string.h>
#include "HierarchicalList.h"

using namespace boost::filesystem;

HierarchicalList hl;
//std::string input_line;
//std::vector<std::string> input;

bool quit{false};
bool stop{true};

//ToDo: interface library
void clean_buffer();
std::vector<std::string> prompt();
bool are_you_sure();
std::vector<std::string> get_names();
std::vector<std::string> split(const std::string &s, char delim);
void select_list();
void delete_list();
bool check_list(std::string n);
void remove_list(std::string n);
void edit_list();
bool set_name();
bool set_file();
void print_lists();
void print_help();
void print_error();
bool save_list();

/* ---------- MAIN ------------ */

int main() {

  while (!quit) {
    hl.clean();
    select_list();
  }

  std::cout << "Good bye!" << std::endl;

  return 0;

}

/* -----------------------------*/

std::vector<std::string> prompt() {
  std::cout << ">>> ";
  std::string istr;
  getline(std::cin, istr);
}

void select_list() {

  std::cout << std::endl;
  std::cout << "Select list, please." << std::endl << std::endl;
  std::cout << ">>> ";

  std::string cmd;

  std::cin >> cmd;

  std::cout << std::endl;

  if      (cmd == "new") {
    if (set_name()) { 
      edit_list(); 
    }    
    return;
  }

  else if (cmd == "open") {
    if (set_file()) { 
      edit_list(); 
    }
    return;
  }

  else if (cmd == "delete") {
    delete_list();
    return;
  }
  else if(cmd == "list") {
    print_lists();
    clean_buffer();  // hack to clear the buffer
    return;
  }

  else if(cmd == "help") {
    print_help();
    clean_buffer();  // hack to clear the buffer
    return;
  }

  else if(cmd == "quit") {
    quit = true;
    clean_buffer();  // hack to clear the buffer
    return;
  }

  print_error();
  return;
}

void edit_list() {

  //Did we stop working with current list?
  stop = false;
  
  while (!stop) {

    std::cout << std::endl;
    hl.print();
    std::cout << std::endl;
    std::cout << ">>> ";

    std::string cmd;

    std::cin >> cmd;
    //clean_buffer();
    std::cout << std::endl;
    
    /* STOP */
    if      (cmd == "stop") {
      clean_buffer();
      std::cout << "Do you want to save changes? ";
      if (are_you_sure()) {
        if (save_list()) { return; } 
      }
      else { return; }
    }

    /* SAVE */
    else if (cmd == "save") {
      clean_buffer();
      save_list();
    }

    /* CLEAN */
    else if (cmd == "clean") {
      clean_buffer();
      hl.clean();
    }  

    /* EDIT */
    // Now only name
    else if (cmd == "edit") {
      
      clean_buffer();
      std::cout << "New name for list: ";
      set_name();
      std::cout << "Don't forget remove old list!" << std::endl;
    } 

    /* DOWN */
    else if (cmd == "down") {
      int n;
      std::cin >> n;
      clean_buffer();
      if (n >= 0 && n < hl.size()) {
        hl.down_rate(n);
      }
      else {
        std::cout << "Wrong element position" << std::endl;
      }
    } 

    /* UP */
    else if (cmd == "up") {
      int n;
      std::cin >> n;
      clean_buffer();
      if (n >= 0 && n < hl.size()) {
        hl.up_rate(n);
      }   
      else {
        std::cout << "Wrong element position" << std::endl;
      }  
    } 

    /* SET */
    else if (cmd == "set") {
      int n, r;
      std::cin >> n >> r;
      //What about errors?
      clean_buffer();
      if (n >= 0 && n < hl.size()) {
        hl.set_rate(n, r);
      }   
      else {
        std::cout << "Wrong element position" << std::endl;
      }  
    } 

    /* ADD */
    else if (cmd == "add") {
      int r;
      std::string c;
      std::cin >> r;

      /*if(!std::cin >> r) {
        std::cout << "Wrong input" << std::endl;
      };*/
      
      if (r >= 0) {
        getline(std::cin, c);
        hl.add_element(c, r);
      }   
      else {
        std::cout << "Wrong rate" << std::endl;
      }
      clean_buffer();
    }

    /* REMOVE */
    else if (cmd == "remove") {
      int n;
      std::cin >> n;
      clean_buffer();
      if (n >= 0 && n < hl.size()) {
        hl.remove(n);
      }
      else {
        std::cout << "Wrong element position" << std::endl;
      }
      
    }
 
    /* HELP */
    else if (cmd == "help") {
      clean_buffer();
      print_help();
    }

    else { 
      clean_buffer(); 
      print_error();
      std::cout << std::endl;
    }
  }

}

int get_int() {
  int n;
  std::cin >> n;
  return n;
}

bool set_name() {
  
  std::string n;
  std::cin >> n;
  clean_buffer();
  for (std::string s : get_names()) {
    if (s == n) {
      std::cout << "ERROR: List with same name already exist. Try other name." << std::endl;
      return false;
    }
  }
  hl.set_name(n);

  return true;

}

//Should I clean list before read? Yes, but where? In this function?
bool set_file() {
  std::string n;
  std::cin >> n;
  clean_buffer();
  for (std::string s : get_names()) {
    if (s == n) {
      std::string file = LIST_FOLDER + n + ".lst";
      std::cout << "Reading from file '" << file << "'..." << std::endl;
      if (hl.read(file)) {
        std::cout << "Read list '" << n <<  "' from file successfully." << std::endl;
        return true;
      }
      else {
        std::cout << "Read list '" << n <<  "' from file FAILED." << std::endl;
        return false;
      }
    }

  }
  std::cout << "There are no list with name '" << n << "'" << std::endl;
  return false;
}

/* All about list's files */

std::vector<path> get_files() {
  std::vector<path> vp;
  if (exists(LIST_FOLDER) && is_directory(LIST_FOLDER)) {
    //std::cout << "There are some existing lists:" << std::endl;
    for (directory_entry& x : directory_iterator(LIST_FOLDER)) {
     // std::cout << "\t" << x.path() << std::endl;
      
      vp.push_back(x.path());
    }
  }
  else {
    std::cout << "Something wrong reading directory";
  }
  return vp;
}

std::vector<std::string> get_names() {
  std::vector<std::string> vs;
  std::vector<path> vp{get_files()};
  for (path p : vp) {
    std::vector<std::string> file;
    file = split(p.string(), '/');
    std::string n{file.back().substr(0,file.back().length()-4)}; //Make it better
    vs.push_back(n);
    //std::cout << "\t" << file.back() << std::endl;
  }
  return vs;
}

void print_lists() {
  for (std::string& s : get_names()) {
    std::cout << "\t" << s << std::endl;
  }
}

//Copy from stackoverflow
std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

void delete_list() {

  std::string n;
  std::cin >> n;
  clean_buffer();
  if (check_list(n)) { 
    std::cout << "Do you really want to remove list '" << n << "'? ";
    if (are_you_sure()) {
      remove_list(n);
    }
  }
  else {
    std::cout << "There are no list with name '" << n << "'." << std::endl;    
  }

}

std::string get_path(std::string n) {
  return LIST_FOLDER + n + ".lst";
}

void remove_list(std::string n) {
  path p{get_path(n)};
  if (exists(p)) {
    if(remove(p)) {
      std::cout<<"List succesfully removed.";
    }
  }
  else {
    std::cout << "There are no list with name '" << n << "'." << std::endl;    
  }
}

bool check_list(std::string n) {
  for (std::string s : get_names()) {
    if (s == n) {
      return true;
    }
  }
  return false;
}


void print_help() {
  int c = 12;
  int p = 12;
  std::cout << "HierarchicalList v0.1" << std::endl << std::endl

            << "\tAvaliable commands:" << std::endl << std::endl

            << "\t\t- " << std::left << std::setw(c) << "new" 
                        << std::left << std::setw(p) << "<name>"
                        << std::left << std::setw(p) << "" 
                        << "create new list and edit;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "open"
                        << std::left << std::setw(p) << "<name>"
                        << std::left << std::setw(p) << "" 
                        << "open list and edit;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "delete"
                        << std::left << std::setw(p) << "<name>"
                        << std::left << std::setw(p) << "" 
                        << "delete list;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "list"
                        << std::left << std::setw(p) << "" 
                        << std::left << std::setw(p) << "" 
                        << "list of existing lists;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "help"
                        << std::left << std::setw(p) << ""
                        << std::left << std::setw(p) << ""
                        << "command list;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "quit"
                        << std::left << std::setw(p) << ""
                        << std::left << std::setw(p) << ""
                        << "exit HierarchicalList." << std::endl
            << std::endl;

  std::cout << "\tEdit list commands:" << std::endl << std::endl

            << "\t\t- " << std::left << std::setw(c) << "up"
                        << std::left << std::setw(p) << "<index>"
                        << std::left << std::setw(p) << ""
                        << "up rate of element;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "down"
                        << std::left << std::setw(p) << "<index>"
                        << std::left << std::setw(p) << ""
                        << "down rate of element;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "set"
                        << std::left << std::setw(p) << "<index>"
                        << std::left << std::setw(p) << "<rate>"
                        << "set rate of element;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "add"
                        << std::left << std::setw(p) << "<rate>"
                        << std::left << std::setw(p) << "<content>"
                        << "add element;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "remove"
                        << std::left << std::setw(p) << "<index>"
                        << std::left << std::setw(p) << ""
                        << "remove element;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "save"
                        << std::left << std::setw(p) << ""
                        << std::left << std::setw(p) << ""
                        << "save list to file;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "stop"
                        << std::left << std::setw(p) << ""
                        << std::left << std::setw(p) << ""
                        << "stop working on list;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "help"
                        << std::left << std::setw(p) << ""
                        << std::left << std::setw(p) << ""
                        << "command list;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "clean"
                        << std::left << std::setw(p) << ""
                        << std::left << std::setw(p) << ""
                        << "remove all elements from list;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "edit"
                        << std::left << std::setw(p) << ""
                        << std::left << std::setw(p) << ""
                        << "edit list (set new name)." << std::endl;

}

void print_error() {
  std::cout << "Something go wrong." << std::endl;
}

bool save_list() {
  if (hl.write()) {
    std::cout << hl.get_name() << " saved." << std::endl;
    return true;
  }
  else {
    std::cout << hl.get_name() << " has trouble with saving." << std::endl;
    return false;
  }
}

bool are_you_sure() {

  bool complite{false};
  //while (1) ?
  while (!complite) {

    char ch;

    std::cout << "(y - yes, n - no): ";

    std::cin >> ch;
    clean_buffer();

    if (ch == 'y') { return true; }
    else if (ch == 'n') { return false; }
    else { std::cout << "Wrong answer. Try again."; }
  }
}

void clean_buffer() {
  std::string passline{"empty line"};
  getline(std::cin, passline);  // hack to clear the buffer
}
