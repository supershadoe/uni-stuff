#include <iostream>
#include <fstream>
#include <exception>

class FileNotFoundException : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "File was not found.";
    }
};

int main()
{
    std::ifstream f;
    std::string fname, temp;
    std::cout << "Enter file name: ";
    std::cin >> fname;
    try
    {
        f.open(fname);
        if (f)
        {
            std::getline(f, temp);
            std::cout << "First line of the file: " << temp << std::endl;
        }
        else
        {
            throw FileNotFoundException();
        }
        throw "something";
    }
    catch (FileNotFoundException &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "Randomly thrown error." << std::endl;
        return 1;
    }
    return 0;
}
