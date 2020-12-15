#include <iostream>
#include <fstream>
#include "Element.h"
#include "HierarchicalList.h"

int main() {
   
    /* Test creating HierarchicalList, add_elements to list and printing to cmd */

    std::cout << "Test creating HierarchicalList, "
              << "add_elements to list "
              << "and printing to cmd:" << std::endl;

    HierarchicalList hl1{"Животные"};

    Element e11{};
    Element e12{"Слон"};
    Element e13{"Дельфин", 4};
    Element e14{3};
    Element e15{"Жираф", 1};
    Element e16{"Утка", 3};
    Element e17{"Мышь", 2};

    hl1.add_element(e11);
    hl1.add_element(e12);
    hl1.add_element(e13);
    hl1.add_element(e14);
    hl1.add_element(e15);
    hl1.add_element(e16);
    hl1.add_element(e17);
    
    HierarchicalList hl2{"Вещи"};
    HierarchicalList hl3{"Принципы"};

    hl1.print();
    hl2.print();
    hl3.print();

    /* Test get/set name */

    std::cout << std::endl << "Test get/set name: " << std::endl;

    std::cout << hl2.get_name() << " -> ";
    hl2.set_name("Предметы быта");
    std::cout << hl2.get_name() << std::endl;

    /* Test up/down rate of element by position */

    std::cout << std::endl; 
    std::cout << "Test up/down rate of element by position:" << std::endl;

    hl1.up_rate(3);
    hl1.print();
    hl1.write();

    hl1.down_rate(1);
    hl1.print();
    hl1.down_rate(1);
    hl1.print();
    hl1.down_rate(1);
    hl1.print();
    hl1.down_rate(1);
    hl1.print();
    hl1.down_rate(1);
    hl1.print();
    hl1.down_rate(1);
    hl1.print();

    /* Test get position of rate */

    std::cout << std::endl << "Test get position of rate:" << std::endl;

    for (int i = 0; i < 6; ++i) {
        std::cout << "Position [" << i << "]: " 
                  << "(" << hl1.get_position_rate_first(i) 
                  << "," << hl1.get_position_rate_last(i)
                  << ")" << std::endl;
    }
    
    /* Test index */
    
    std::cout << std::endl << "Test index operator []:" << std::endl;
    std::vector<Element> v;
    v = hl1[3];
    for(Element& e : v) std::cout << e << std::endl;

    /* Test writing to file */
    
    std::cout << std::endl << "Test writing to file:" << std::endl;
    hl1.write();

    /* Test reading from file */

    HierarchicalList hl;
    std::string file{"lists/Животные.lst"};

    std::cout << std::endl;
    std::cout << "Test read from file '" << file << "':" << std::endl;

    hl.read(file);
    hl.print();

    std::cout << std::endl;

    /* Test construct from file */

    std::cout << "Test HierarchicalList constructor from file:" << std::endl;

    HierarchicalList hl54("Люди");
    hl54.add_element(1, "Хороший");
    hl54.add_element(3, "Плохой");
    hl54.add_element(2, "Злой");
    hl54.write();
    HierarchicalList hl45("lists", "Люди.lst");
    hl45.print();
    std::cout << std::endl;

    /* Test operator '<<' and '>>' */
    std::cout << "Test operators '<<' and '>>':" << std::endl;
    HierarchicalList hl12;
    std::string file12{"lists/Животные.lst"};
    std::ifstream ifs{file12};
    if (!ifs) {
        std::cout << "Reading from " << file << " failed." << std::endl;
    }
    ifs >> hl12;
    std::cout << hl12 << std::endl;
    
    return 0;
}
