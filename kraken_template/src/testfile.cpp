#include <iostream>
#include <new>
#include <string>
#include <unordered_map>

class node {
    public:
        void (*func)();

        node() {}
        node(void (*func)()) : func(func) {}
};

class SET {
    public:
        std::unordered_map<std::string, node> map;

        void add(std::string name, void (*funcc)()) {
            map[name] = node(funcc);
        }

        void run(std::string name) {
            map[name].func();
        }
};

void fff() {
    std::cout<<"called"<<std::endl;
}

int main() {
    SET set;

    //set.add("n", fff);
    //set.run("n");
    
    return 1;
}