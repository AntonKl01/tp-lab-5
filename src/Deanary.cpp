//  Copyright 2020 GHA created by Klykov Anton

#include "Deanary.h"
#include <random>

void Deanary::createGroups() {
  CreateGroup_F create_group;
  create_group.readFile();
  size_t size{create_group.getTitle().size()};
  for (size_t i = 0; i < size; ++i) {
    groups.push_back(create_group.parseGroup(i));
  }
}
void Deanary::hireStudent() {
  CreateStudent_F create_student;
  create_student.readFile();
  size_t amountGroups{groups.size()};
  int k{0};
  for (size_t i = 0; i < amountGroups; ++i) {
    for (size_t j = 0; j < 20; ++j, ++k) {
      groups[i]->addStudent(create_student.parseStudent(k));
    }
  }
}
void Deanary::initHeaders() {
  for (size_t i = 0; i < groups.size(); ++i) {
    groups[i]->chooseHeader();
  }
}
void Deanary::fireStudent(int _id) {
  for (size_t i = 0; i < groups.size(); ++i) {
    if (groups[i]->delStudent(groups[i]->getStudent(_id))) {
      return;
    }
  }
}
void Deanary::moveStudent(int _id, int number_group) {
  Student* removingStudent;
  for (size_t i = 0; i < groups.size(); ++i) {
    removingStudent =
        groups[i]->removeStudent(groups[i]->getStudent(_id));
    if (removingStudent) {
      if (removingStudent->group != groups[(number_group)]) {
        groups[(number_group)]->addStudent(removingStudent);
        return;
      } else {
        std::cout << "Student is there already!" << std::endl;
        return;
      }
    }
  }
  std::cout << "He leave the university!" << std::endl;
}
void Deanary::addMarksToAll() {
  static int iteration{0};
  for (size_t i = 0; i < groups.size(); ++i) {
    for (size_t j = 0; j < groups[i]->students.size(); ++j) {
      groups[i]->students[j]->addMark(iteration);
    }
  }
  iteration++;
}
void Deanary::getStatistics() {
  for (size_t i = 0; i < groups.size(); ++i) {
    std::cout << "Groups" << i << ": "
              << groups[i]->getAverageMark() << std::endl;
    for (size_t j = 0; j < groups[i]->students.size(); ++j) {
      std::cout << "  " << groups[i]->students[j]->FinSenThn << ": "
                << groups[i]->students[j]->getAverageMark() << std::endl;
    }
  }
}
void Deanary::fireBadStudents() {
  for (size_t i = 0; i < groups.size(); ++i) {
    for (size_t j = 0; j < groups[i]->students.size(); ++j) {
      if (groups[i]->students[j]->getAverageMark() <= 2) {
        fireStudent(groups[i]->students[j]->id);
      }
    }
  }
}
int Deanary::getAmountGroup() {
  return groups.size();
}
std::string Deanary::getTitleGroup(int _num) {
  return groups[_num]->getTitle();
}
int Deanary::getAmountStudents(int _num) {
  return groups[_num]->students.size();
}
Group* Deanary::getGroup(int _num) {
  return groups[_num];
}
Deanary::~Deanary() {
  for (size_t i = 0; i < groups.size(); ++i) {
    for (size_t j = 0; j < groups[i]->students.size(); ++j) {
      delete groups[i]->students[j];
      groups[i]->students[j] = nullptr;
    }
    delete groups[i];
    groups[i] = nullptr;
  }
}


