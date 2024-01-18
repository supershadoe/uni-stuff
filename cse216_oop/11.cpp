#include <iostream>
#include <fstream>

class Student
{
private:
    int reg_no;
    std::string stu_name;
    char section;
    std::string dept;
    static int line_count;

public:
    Student(int r, std::string n, char s, std::string d) : reg_no(r), stu_name(n), section(s), dept(d) {}

    void getDetails()
    {
        std::cout << "Name: " << stu_name << '\n'
                  << "Register no: " << reg_no << '\n'
                  << "Section: " << section << '\n'
                  << "Department: " << dept << std::endl;
    }

    static Student fromFile(const std::string &fname)
    {
        std::ifstream f(fname);
        int r;
        char s;
        std::string d, n;

        for (int i = 0; i < line_count; i++)
            std::getline(f, n); // skip to n-th line
        f >> r >> s >> d;
        std::getline(f, n);
        Student stu = Student(r, n, s, d);
        line_count++;
        f.close();
        return stu;
    }

    void toFile(const std::string &fname)
    {
        std::ofstream f(fname, std::ios::app);
        f << reg_no << ' ' << section << ' ' << dept << ' ' << stu_name << std::endl;
    }
};

int Student::line_count = 0;

int main()
{
    Student s = Student::fromFile("stu_details.txt");
    Student s2 = Student::fromFile("stu_details.txt");
    s.getDetails();
    s2.getDetails();
    Student(11, "sdgsgsdgs", 'A', "CSE").toFile("stu_details.txt");
    return 0;
}
