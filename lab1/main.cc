#include <vector>
#include <iostream>
#include <fstream>
#include<cstdlib>
#include<cstring>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);

        studentVec.push_back(st);
    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?
    bufv.clear();
    int cl_flag = 0;
    Class *cl = nullptr;
    ifstream clfile("./Classes.txt");
    while(getline(clfile,line)){
        if(line[0]=='#') continue;
        if(line.empty()){
            cl_flag = 0;
            bufv.clear();
            cl=nullptr;
            continue;
        }
        if(line[0]=='C'&&line[1]=='l') {
            pos2 = line.find(':');
            bufv.push_back(line.substr(pos2+1));
            cl_flag = 1;
            continue;
        }
        if(line[0]=='P'&&line[1]=='o'){
                pos2 = line.find(':');
                bufv.push_back(line.substr(pos2+1));
                cl = new Class(bufv[0],atoi(bufv[1].c_str()));
                classVec.push_back(cl);
                continue;
        }
        st = nullptr;
        if(cl_flag&&cl!=nullptr){
            for(vector<Student*>::iterator it = studentVec.begin()
                ;it!=studentVec.end();it++){
                if((*it)->id==line){st = *it;(*it)->addClass(cl);break;}
            }
            if(st==nullptr)
                cout<<"No match student!\n";
            else classVec.back()->addStudent(*st);
            }

    }
}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printAvgScore().
    string sbuf;
    Class *cl;
    while(true){
    cout << "Please input the class name (or input q to quit): ";
    cin >> sbuf;
    if (sbuf == "q")
        break;
    cl =nullptr;
    for(vector<Class *>::iterator it = classVec.begin();it != classVec.end();
        it++){
        if((*it)->name == sbuf){
            cl = *it;
            break;
        }
    }
    if(cl == nullptr){ cout<<"No match class!\n";
        continue;
    }

    while(true){
        try {
        cout << "Please input the student id (or input q to quit): ";
        string stid;
        cin >> stid;
        if(stid=="q") break;
        StudentWrapper &st = cl->getStudentWrapper(stid);
        cout<<st.toString();
        while(true){
        cout << "Please input the student score (or input q to quit): ";
        string stsc;
        cin>>stsc;
        if(stsc=="q") break;
        double sc = atof(stsc.c_str());
        st.setScore(sc);
        break;
        }
         }  catch (char const* s) {
            if(strcmp(s,"Wrong score!")==0) cout<<"Wrong score!\n";
            else if(strcmp(s,"No match student!")==0) cout<<"No match student!\n";
        }
     }       
      }
    }

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        printf("The average score is: %.2f\n",avg);
    }
}

void AppX::printGpa()
{
    // TODO: implement printGpa.
    // Hint: Take a look at printAvgScore().

    while(true){
        cout << "Please input the student id (or input q to quit): ";
        string stid;
        Student *st = nullptr;
        cin >> stid;
        if(stid=="q") break;
        for(vector<Student *>::iterator it = studentVec.begin()
            ;it!=studentVec.end();it++){
            if((*it)->id==stid) {st = *it;break;}
        }
        if(st == nullptr){ cout<<"No match student!\n"; continue;}
        cout<<st->toString();
        double gpa = st->getGrade();
        printf( "GPA = %.2f\n",gpa);
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
             << "\ti: Input score\n"
             << "\ta: Compute average score of a class\n"
             << "\tg: Compute grade of a student\n"
             << "\tq: Quit\n"
             << "Please input the command: ";
         cin >> cmd;
         if (cmd == 'i') {
             inputScore();
         } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
