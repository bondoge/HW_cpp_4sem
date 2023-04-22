
#include <iostream>
#include <string>
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <cstdlib>
using namespace nlohmann;
using namespace std::filesystem;

class human
{
public:
    human(std::string name, int age): name(name), age(age){};
    human(std::string name): name(name){};
    human(): name(""){};
    ~human(){};  //delete[] &name;

    // конструктор копирования
    human(const human& other){
        name = other.name;
        age = other.age;
    }

    // конструктор перемещения
    human(human&& other) noexcept
    {
        name = other.name;
        age = other.age;
        other.name = nullptr;
    }

    // оператор присваивания копированием
    human& operator=(const human& other)
    {
        if (this == &other) return *this;
        delete[] &name;
        name = other.name;
        age = other.age;
        return *this;
    }
    // оператор присваивания перемещением
    human& operator=(human&& other) noexcept
    {
        if (this == &other) return *this;
        delete [] &name;
        name = other.name;
        other.name = nullptr;
        return *this;
    }

    // внешние методы
    friend std::ostream& operator<<(std::ostream& out, const human& h);
    friend std::istream& operator>>(std::istream& in, human& h);
    friend void to_json(json& j, const human& h);
    friend void from_json(const json& j, human& h);

private:
    std::string name;
    int age;
};

// ввод вывод
std::ostream& operator<<(std::ostream& out, const human& h)
{
    out << "name: " << h.name << ", age: " << h.age << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, human& h)
{
    in >> h.name >> h.age;
    return in;
}

// функции преобразования в JSON объект и обратно
    void to_json(json& j, const human& h) {
        j = json{{"name", h.name}, {"age", h.age}};
    }

    void from_json(const json& j, human& h) {
        h.name = j["name"];
        h.age = j["age"];
    }



int main()
{
    // ввод
    human h1, h2, h3;
    std::cin >> h1; std::cout << h1 << std::endl;
    std::cin >> h2; std::cout << h2 << std::endl;
    std::cin >> h3; std::cout << h3 << std::endl;

    // преобразование созданных экземпляров в набор JSON объектов
    json j1 = h1;
    json j2 = h2;
    json j3 = h3;

    // создадим каталог JSON объектов с помощью filesystem
    create_directory("catalogue");
    auto current_dir = path("catalogue");

    auto file1 = current_dir / "human1.txt";
    std::ofstream fout1(file1);
    fout1 << j1 << std::endl;

    auto file2 = current_dir / "human2.txt";
    std::ofstream fout2(file2);
    fout2 << j2 << std::endl;

    auto file3 = current_dir / "human3.txt";
    std::ofstream fout3(file3);
    fout3 << j3 << std::endl;

    // std::system("dir .");
    // std::system("tree .");
}
