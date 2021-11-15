#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
class Class;
using namespace std;
enum Degree {
    undergraduate,
    graduate
};
class Student {
    // TODO: implement class Student.
private:
    const std::string year;
    const std::string name;
    Degree degree;
protected:
    vector<Class*> classes;
public:
    Student(std::string &i,std::string &y,std::string &n)
        :id(i),year(y),name(n){};
    ~Student();
    const std::string id;
    std::string toString() const;
    void addClass(Class *c){
       classes.push_back(c);
    }
    virtual double getGrade() = 0;
};

// TODO: implement class Graduate.
class Undergraduate:public Student{
public:
    Undergraduate(std::string &i,std::string &y,std::string &n):Student(i,y,n){}
    double getGrade();
};
// TODO: implement class Undergraduate.
class Graduate:public Student{
public:
    Graduate(std::string &i,std::string &y,std::string &n):Student(i,y,n){}
    double getGrade();
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error
    
    StudentWrapper(const std::string &id, const Student &student):id(id),student(student) {
    }
    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Wrong score!";
        this->score = score;
    }

    double getScore() const
    {        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};
#endif // STUDENT_H_
