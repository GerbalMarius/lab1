//
// Created by Marius Ambrazevičius on 27/09/2024.
//
// Created by marius on 2024-09-11.
//

#ifndef CAT_H
#define CAT_H
#include <string>
#include <algorithm>


class Cat {

public:
    Cat();
    Cat(int age, std::string name, double weight);
    ~Cat() = default;
    static const Cat EMPTY;

    [[nodiscard]]
    int getAge() const;

    [[nodiscard]]
    std::string getName() const;

    [[nodiscard]]
    double getWeight()const;

    [[nodiscard]]
    std::string getHash() const;

    void setAge(int age);
    void setName(const std::string& name);
    void setWeight(double weight);
    void setHash(std::string hash);


    friend std::ostream& operator <<(std::ostream& os, const Cat& cat);
    friend bool operator ==(const Cat& cat1, const Cat& cat2);
    friend bool operator !=(const Cat& cat1, const Cat& cat2);
    friend bool operator >(const Cat& cat1, const Cat& cat2);

    [[nodiscard]] std::string serialize() const;


private:
    int age_{};
    std::string name_;
    double weight_{};
    std::string hash_;
};



#endif //CAT_H
