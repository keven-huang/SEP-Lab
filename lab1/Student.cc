#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

Student::~Student(){}

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
}

// TODO: implement functions which are declared in Student.h.
double Undergraduate::getGrade(){
       double TotalPoint = 0.0,TotalScore=0.0;
       for(vector<Class *>::iterator it = classes.begin()
              ;it!=classes.end();it++){
       double score = ((*it)->getStudentWrapper(id)).getScore()/20.0;
       TotalScore+=((*it)->point)*score;
       TotalPoint+=(*it)->point;
       }
       if(TotalPoint!=0) return TotalScore/TotalPoint;
       else return 0.0;
}

double Graduate::getGrade(){
    double TotalPoint = 0.0,TotalScore =0.0;
    for(vector<Class*>::iterator it = classes.begin()
        ;it!=classes.end();it++){
        double score = ((*it)->getStudentWrapper(id)).getScore();
        switch (int(score/10)) {
        case 10:
        case 9:score = 4.0;break;
        case 8:score = 3.5;break;
        case 7:score = 3.0;break;
        case 6:score = 2.5;break;
        default: score = 2.0;
        }
        TotalScore += score*((*it)->point);
        TotalPoint +=(*it)->point;
    }
    if(TotalPoint!=0) return TotalScore/TotalPoint;
    else return 0.0;
}
