#include <iostream>
#include "Element.h"

int main() {

    Element e1{};
    Element e2{3};
    Element e3{"Hello"};
    Element e4{"World",2};

    /*Test elements, get_rate and get_content*/
    std::cout << "Element 1: "
              << "[" << e1.get_rate() << "] " 
              << e1.get_content() << std::endl;

    std::cout << "Element 2: "
              << "[" << e2.get_rate() << "] " 
              << e2.get_content() << std::endl;

    std::cout << "Element 3: "
              << "[" << e3.get_rate() << "] " 
              << e3.get_content() << std::endl;

    std::cout << "Element 4: "
              << "[" << e4.get_rate() << "] " 
              << e4.get_content() << std::endl;
    std::cout << std::endl;

    /*Test cout*/
    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;
    std::cout << e3 << std::endl;
    std::cout << e4 << std::endl;
    std::cout << std::endl;

    /*Test set_rate and set_content*/
    Element e5{"Ho-ho!", 7};
    std::cout << "Element 5: " << e5 << std::endl;
    e5.set_rate(5);
    e5.set_content("Hello");
    std::cout << "Element 5: " << e5 << std::endl;
    std::cout << std::endl;

    /*Test up_rate and down_rate*/
    e5.up_rate();
    std::cout << "Element 5: " << e5 << std::endl;
    e5.up_rate();
    std::cout << "Element 5: " << e5 << std::endl;
    std::cout << "Element 3: " << e3 << std::endl;
    if(e3.down_rate()) {
        std::cout << "Element 3: " << e3 << std::endl;
    }
    else {
        std::cout << "Can't down_rate Element 3." << std::endl;
    }
    e3.set_rate(1);   
    if(e3.down_rate()) {
        std::cout << "Element 3: " << e3 << std::endl;
    }
    else {
        std::cout << "Can't down_rate Element 3." << std::endl;
    }
    if(e3.down_rate()) {
        std::cout << "Element 3: " << e3 << std::endl;
    }
    else {
        std::cout << "Can't down_rate Element 3." << std::endl;
    }
    std::cout << "Element 3: " << e3 << std::endl;
    std::cout << std::endl;

    /*Test == and !=*/
    std::cout << "e1==e2: "<< (e1==e2) << std::endl;
    std::cout << "e1==e3: "<< (e1==e3) << std::endl;
    std::cout << "e1==e2: "<< (e1==e4) << std::endl;
    std::cout << "e1!=e2: "<< (e1!=e2) << std::endl;
    std::cout << "e1==e5: "<< (e1==e5) << std::endl;
    std::cout << "e1!=e5: "<< (e1!=e5) << std::endl;
    std::cout << "e3==e5: "<< (e3==e5) << std::endl;
    std::cout << "e3!=e5: "<< (e3!=e5) << std::endl;
    std::cout << std::endl;
    
    Element e6{3};
    std::cout << "Element 6: " << e6 << std::endl;
    std::cout << "Element 2: " << e2 << std::endl;
    std::cout << "e2==e6: "<< (e2==e6) << std::endl;

    Element e_test;
    std::cout << "Enter element in format <[int] std::string>: ";
    std::cin >> e_test;
    std::cout << "Read element: " << e_test << std::endl;    
    
}
