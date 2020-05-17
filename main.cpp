/*1. Продемонстрировать различные уровни инкапсуляции данных (указать комментарием):
a. Отсутствие инкапсуляции (public свойства)
b. Инкапсуляция с помощью set/get
c. Инкапсуляция с помощью специализированных протоколов/методов
d. Инкапсуляция за счёт абстракций

p.s. использовать механизмы исключений, если нарушается инвариант или не соблюдаются пост/пред-условия

2. Продемонстрировать различные варианты инкапсуляции поведения
a. За счёт позднего связывания
b. Замена поведения (тут тоже используется позднее связывание)
c. Расширения поведения (тут тоже используется позднее связывание)
 */
#include <iostream>
using namespace std;

class DanceStudio {
protected:
  unsigned int quantity_student;
  unsigned int price;

public:
  string name_DanceStudio; //Отсутствие инкапсуляции (public свойства)

  DanceStudio(unsigned int quatity_student, unsigned int price,
              string name_DanceStudio) {
    this->quantity_student = quantity_student;
    this->price = price;
    this->name_DanceStudio = name_DanceStudio;
  }

  unsigned int getQuantityStudent() const { //Инкапсуляция с помощью set/get
    return quantity_student;
  }
  void setQuantityStudent(unsigned int quantityStudent) {
    quantity_student = quantityStudent;
  }

  unsigned int getPrice() const { return price; }
  void setPrice(unsigned int price) { DanceStudio::price = price; }

  virtual void say_price() const{ //Расширения поведения
    cout << "Цена занятий в нашей студии равна " << getPrice() << endl;
  };
};

class ChildGroup : public DanceStudio {
protected:
  unsigned int quantity_class;

public:
  ChildGroup(unsigned int quatityStudent, unsigned int price,
             const string &nameDanceStudio, unsigned int quantity_class)
      : DanceStudio(quatityStudent, price, nameDanceStudio) {}

  virtual unsigned int getQuantityClass() const { //За счёт позднего связывания
    return quantity_class;
  }
  void setQuantityClass(unsigned int quantityClass) {
    quantity_class = quantityClass;
  }

  virtual void add_students(unsigned int quantity_student) {
    quantity_student++;
  }

  void say_price() const {
    cout << "Цена занятий в детской группе равна " << getPrice()/2 << endl;
  };
};

class TeacherCG : public ChildGroup {
protected:
  unsigned int salary;

public:
  TeacherCG(unsigned int quatityStudent, unsigned int price,
            const string &nameDanceStudio, unsigned int quantityClass,
            unsigned int salary)
      : ChildGroup(quatityStudent, price, nameDanceStudio, quantityClass) {
    this->quantity_student = quantity_student;
    this->price = price;
    this->name_DanceStudio = name_DanceStudio;
    this->quantity_class = quantityClass;
    this->salary = salary;
  }

  unsigned int getSalary() const { //Замена поведения
    return 30000;
  }
  void setSalary(unsigned int salary) { TeacherCG::salary = salary; }

  void say_price() const {
    cout << "Цена занятий в моей группе равна " << getPrice()/2 << endl;
  };
};


void say(DanceStudio *d){//Инкапсуляция за счёт абстракций
  d->say_price();
}

int main() {
  TeacherCG teacher(5, 300, "DanceStudio", 3, 30);
  cout << teacher.getSalary() << endl;
  DanceStudio studio(15, 300, "DanceStudio");
  studio.say_price();

  say(&teacher);
  say(&studio);

  std::cout << "Hello, World!" << std::endl;
  return 0;
}