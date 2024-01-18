#include <iostream>

class ObjectCounter {
    static int count;
    int id;
    
    public:
        ObjectCounter() {
            count++;
            id = count;
            std::cout << "Object " << count << " created." << std::endl;
        }
        ~ObjectCounter() {
            std::cout << "Object " << id << " destroyed." << std::endl;
            count--;
        }
        static int getCount() {
            return count;
        }
};

int ObjectCounter::count = 0;

int main() {
    using namespace std;
    ObjectCounter o1;
    {
        ObjectCounter o2, o3;
    }
    {
        cout << "Objects after leaving block 1: " << ObjectCounter::getCount() << endl;
        ObjectCounter o4;
    }
    cout << "Total remaining objects: " << ObjectCounter::getCount() << endl;
    return 0;
}
