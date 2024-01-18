#include <iostream>
#include <vector>

using namespace std;

class LivingBeings {
    private:
        int type_id;
    protected:
        enum avail_types { plants = 1, animals };
    public:
        LivingBeings(int _type): type_id(_type) {}
        void whoAmI();
};

class Plants: private LivingBeings {
    private:
        string name, flower_color;
        bool edible_or_not;
        static vector<Plants> plants_list;
    public:
        Plants():
            LivingBeings(plants),
            name("Missing"),
            flower_color("Black"),
            edible_or_not(false)
        {
            plants_list.push_back(*this);
        }

        Plants(const string& pname, const string& fcolor, bool is_edible)
            : LivingBeings(plants),
              name(pname),
              flower_color(fcolor),
              edible_or_not(is_edible)
        {
            plants_list.push_back(*this);
        }

        void whoAmI() {
            cout << "Type: Plant\n" << "Name: "<< name << "\n"
                << "Flower color: " << flower_color << "\n"
                << (edible_or_not ? "Edible" : "Inedible") << " plant\n"
                << endl;
        }

        static void my_color(const string& color) {
            bool no_plant = true;
            for( Plants p: plants_list ) {
                if (p.flower_color == color) {
                    if (no_plant) {
                        cout << "These are the plants with the flower color "
                            << color << endl;
                        no_plant = false;
                    }
                    p.whoAmI();
                }
            }
            if (no_plant)
                cout << "There are no plants of this color." << endl;
        }
};

class Animals: private LivingBeings {
    private:
        string name;
    public:
        Animals(const string& aname, int atype = animals):
            LivingBeings(atype), name(aname) {}

        int length() {
            return name.length();
        }
        
        void whoAmI() {
            cout << "Type: Animal\n" << "Name: " << name << "\n" << endl;
        }

        string operator >(const Animals& other) {
            return name.length() > other.name.length() ? name : other.name;
        }
};

vector<Plants> Plants::plants_list;

int main() {
    Plants p1, p2("Hibiscus", "Pink", true), p3("Rose", "Pink", true);
    Animals a1("Lion"), a2("Tiger");
    
    p1.whoAmI();
    a2.whoAmI();
    cout << "Lion vs tiger winner: " << (a1 > a2) << endl;
    cout << "Length of a1 name: " << a1.length() << endl;

    string c;
    cout << "\nEnter a color: ";
    cin >> c;

    Plants::my_color(c);
    return 0;
}
