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
std::vector<std::string> input;

bool quit{false};
bool stop{true};

//ToDo: interface library
std::string make_string(std::vector<std::string>& vs, int pos);
void clean_buffer();
std::vector<std::string> prompt();
bool are_you_sure();
std::vector<std::string> get_names();
std::vector<std::string> split(const std::string &s, char delim);
void select_list();
void delete_list(std::string n);
bool check_list(std::string n);
void remove_list(std::string n);
void edit_list();
bool set_name(std::string n);
bool set_file(std::string n);
void print_lists();
void print_help();
void print_error();
bool save_list();

/* ---------- MAIN ------------ */

int main() {

  while (!quit) {
    hl.clean();
    select_list();
    /*std::vector<std::string> vs;
    vs = prompt();
    for (std::string s : vs) {
      std::cout << s << std::endl;
    }*/
  }

  std::cout << "Good bye!" << std::endl;

  return 0;

}

/* -----------------------------*/

std::vector<std::string> prompt() {
  std::cout << ">>> ";
  std::string istr;
  //Something wrong with this.
  getline(std::cin, istr);
  std::stringstream ss(istr);
  std::vector<std::string> words;
  for(std::string s; ss >> s;) { words.push_back(s); }
  return words;
}

void select_list() {

  std::cout << std::endl;
  std::cout << "Select list, please." << std::endl << std::endl;

  input.clear();
  input = prompt();

  std::string cmd;
  cmd = input[0];  
 
  std::cout << std::endl;

  /* NEW */
  if      (cmd == "new") {
    if (input.size() > 1) {
      std::string n{make_string(input, 1)};
      if (set_name(n)) { edit_list(); }
    }    
    return;
  }

  /* OPEN */
  else if (cmd == "open") {
    if (input.size() > 1) {
      std::string n{make_string(input, 1)};
      if (set_file(n)) { edit_list(); }
    }
    return;
  }

  /* SHOW */
  else if (cmd == "show") {
    if (input.size() > 1) {
      std::string n{make_string(input, 1)};
      if (set_file(n)) { hl.print(); }
    }
    return;
  }

  /* DELETE */
  else if (cmd == "delete") {
    if (input.size() > 1) {
      std::string n{make_string(input, 1)};
      delete_list(n);
    }
    return;
  }

  /* LIST */
  else if(cmd == "list") {
    print_lists();
    return;
  }

  /* HELP */
  else if(cmd == "help") {
    print_help();
    return;
  }

  else if(cmd == "quit") {
    quit = true;
    return;
  }

  print_error();
  return;
}

void edit_list() {

  //Did we stop working with current list?
  stop = false;
  
  while (!stop) {

    //std::cout << std::endl;
    hl.print();
    std::cout << std::endl;

    input.clear();
    input = prompt();

    std::string cmd;
    cmd = input[0]; 

    std::cout << std::endl;
    
    /* STOP */
    if      (cmd == "stop") {
      std::cout << "Do you want to save changes? ";
      if (are_you_sure()) {
        if (save_list()) { return; } 
      }
      else { return; }
    }

    /* SAVE */
    else if (cmd == "save") {
      save_list();
    }

    /* CLEAN */
    else if (cmd == "clean") {
      hl.clean();
    }  

    /* EDIT */
    else if (cmd == "edit") {
      
      int n = -1;
      std::string s;
  
      if (input.size() > 2) {
        try {
          n = std::stoi(input[1]);
        }
        catch (...) {
          std::cout << "Wrong element position" << std::endl;
        }

        s = make_string(input, 2);

        if (n >= 0 && n < hl.size()) { hl.set_content(n, s); }  
        else { std::cout << "Wrong element position" << std::endl; }

      }

      else {
        std::cout << "Not enough arguments" << std::endl;
      }
      //std::cout << "Don't forget remove old list!" << std::endl;
    } 

    /* DOWN */
    else if (cmd == "down") {
      int n = -1;
      if (input.size() > 1) {
        try {
          n = std::stoi(input[1]);
          if (n >= 0 && n < hl.size()) {
            hl.down_rate(n);
          }
          else {
            std::cout << "Wrong element position" << std::endl;
          }
        }
        catch (...) {
          std::cout << "Wrong argument" << std::endl;
        }
      }
      else {
        std::cout << "Usage: down [index <int>]" << std::endl;
      }
    } 

    /* UP */
    else if (cmd == "up") {
      int n = -1;
      if (input.size() > 1) {
        try {
          n = std::stoi(input[1]);
          if (n >= 0 && n < hl.size()) {
            hl.up_rate(n);
          }
          else {
            std::cout << "Wrong element position" << std::endl;
          }
        }
        catch (...) {
          std::cout << "Wrong argument" << std::endl;
        }
      }
      else {
        std::cout << "Usage: up [index <int>]" << std::endl;
      }
    } 

    /* SET */
    else if (cmd == "set") {

      int n = -1;
      int r = -1;

      if (input.size() > 2) {
        try {
          n = std::stoi(input[1]);
        }
        catch (...) {
          std::cout << "Wrong index" << std::endl;
        }

        try {
          r = std::stoi(input[2]);
        }
        catch (...) {
          std::cout << "Wrong rate" << std::endl;
        }

        if (n >= 0 && n < hl.size() && r >= 0) {
          hl.set_rate(n, r);
        }   
        else {
          std::cout << "Wrong arguments. Usage: set [index <int>] [rate <int>]" << std::endl;
        }
      }
      else {
        std::cout << "Not enough arguments" << std::endl;
      }  
    } 

    /* ADD */
    else if (cmd == "add") {
      int r = -1;
      std::string s;
  
      if (input.size() > 2) {
        try {
          r = std::stoi(input[1]);
        }
        catch (...) {
          std::cout << "Wrong rate" << std::endl;
        }

        s = make_string(input, 2);

        if (r >= 0) { hl.add_element(r, s); }  
        else { std::cout << "Wrong rate" << std::endl; }

      }

      else {
        std::cout << "Not enough arguments" << std::endl;
      }
      
    }

    /* REMOVE */
    else if (cmd == "remove") {

      int n = -1;
      if (input.size() > 1) {
        try {
          n = std::stoi(input[1]);
          if (n >= 0 && n < hl.size()) {
            hl.remove(n);
          }
          else {
            std::cout << "Wrong element position" << std::endl;
          }
        }
        catch (...) {
          std::cout << "Wrong argument" << std::endl;
        }
      }
      else {
        std::cout << "Usage: remove [index <int>]" << std::endl;
      }
      
    }

    /* RENAME */
    else if (cmd == "rename") {

      std::string s;
      if (input.size() > 1) {
        s = make_string(input, 1);
        if (!set_name(s)) { 
          std::cout << "Wrong name" << std::endl; 
        }
      }
      else {
        std::cout << "Not enough arguments" << std::endl;
      }
      
    }
 
    /* HELP */
    else if (cmd == "help") {
      print_help();
    }

    else { 
      print_error();
      std::cout << std::endl;
    }
  }

}

bool set_name(std::string n) {

  if (check_list(n)) {
    std::cout << "ERROR: List with same name already exist. Try other name." << std::endl;
    return false;
  }
  hl.set_name(n);

  return true;

}

//Should I clean list before read? Yes, but where? In this function?
bool set_file(std::string n) {

  if (check_list(n)) {
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

void delete_list(std::string n) {

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
      std::cout<<"List succesfully deleted.";
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

            << "\t\t- " << std::left << std::setw(c) << "show"
                        << std::left << std::setw(p) << "<name>" 
                        << std::left << std::setw(p) << "" 
                        << "show list;" << std::endl

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

            << "\t\t- " << std::left << std::setw(c) << "edit"
                        << std::left << std::setw(p) << "<index>"
                        << std::left << std::setw(p) << "<content>"
                        << "edit content of element;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "swap"
                        << std::left << std::setw(p) << "<index>"
                        << std::left << std::setw(p) << "<index>"
                        << "swap rate of elements;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "remove"
                        << std::left << std::setw(p) << "<index>"
                        << std::left << std::setw(p) << ""
                        << "remove element;" << std::endl

            << "\t\t- " << std::left << std::setw(c) << "rename"
                        << std::left << std::setw(p) << "<new_name>"
                        << std::left << std::setw(p) << ""
                        << "set new name to list;" << std::endl

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
                        << "remove all elements from list." << std::endl;



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

std::string make_string(std::vector<std::string>& vs, int pos) {
  if (pos < vs.size()) {
    std::stringstream ostr;
    ostr << vs[pos];
    for(int i = pos + 1; i < vs.size(); ++i) {
      ostr << " " << vs[i];
    }
  return ostr.str();
  }
  return {};
}

/* bool get_int(std::string s, int& n) {
  try {
    n = std::stoi(s);
  }
  catch (...) {
    return false;
  }
  return true;
}
*/
