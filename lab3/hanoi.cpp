#include "termio.h"
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include <sstream>
// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];

class stack{
public:
    int *from,*to;
    int top_f,top_t;
    stack(){
        from = new int [10000];
        to = new int [10000];
        top_f = top_t = -1;

    }
    ~stack(){
        delete [] from;
        delete [] to;
    }
    void pop(int &f,int &t){
        f = from[top_f--];
        t = to[top_t--];
    }
    void top(int &f,int &t){
        f = from[top_f];
        t = to[top_t];
    }
    void push(int f,int t){
        from[++top_f] = f;
        to[++top_t] = t;
    }
    bool isEmpty(){
        return top_f == -1;
    }
};
class list{
private:
    int *disk;
    int top_p;
public:
    list(int n){
        disk = new int[n];
        top_p = -1;
    }
    ~list(){
        delete []disk;
    }
    int pop(){
        return disk[top_p--];
    }
    int top()const{
        if(top_p == -1) return 6;
        return disk[top_p];
    }
    void push(int x){
        disk[++top_p] = x;
    }
    bool isEmpty(){
        return top_p==-1;
    }
    int visit(int i) const{
        return disk[i];
    }
    int size() const{
        return top_p;
    }
};
/*
//write_canvas函数和write_disk函数为了显示当前状态
//使用整合好的Draw函数即可
*/
void write_canvas(){
    for(int i = 0;i<Termio::CANVAS_WIDTH;i++)
        Termio::buffer[Termio::CANVAS_HEIGHT - 1][i] = '-';
    for(int i = 0;i<Termio::CANVAS_HEIGHT;i++){
        Termio::buffer[i][5] = '|';
        Termio::buffer[i][20] = '|';
        Termio::buffer[i][35] = '|';
    }
}
void write_disk(list rod[]){
    for(int i = Termio::CANVAS_HEIGHT -2, p = 0;
       p <= max(max(rod[0].size(),rod[1].size()),rod[2].size());i-=2){
        int a[3] = {5,20,35};
        for(int t = 0;t<=2;t++){
            if(p <= rod[t].size())
                for(int j =a[t] - rod[t].visit(p);j <= a[t] + rod[t].visit(p);j++){
                    Termio::buffer[i][j] = '*';
                }
        }
        p += 1;
    }
}
void Draw(list rod[]){
    Termio::ResetBuffer();
    write_canvas();
    write_disk(rod);
    Termio::Draw();
}
void move(int f,int t,list rod[]){
    if(f<1||f>3||t<1||t>3) {
        Draw(rod);
        throw "num range error";
    }
    if(rod[f-1].isEmpty()||rod[f-1].top()>rod[t-1].top())
    {   Draw(rod);
        throw "input is invalid";
    }
    rod[t-1].push(rod[f-1].pop());
}
void hanoi(int n,int a,int b,int c,list rod[]) {
    if(n==0) return;
    if(n==1){
        move(a,b,rod);
        std::cout << "Auto moving:"<<a<<"->"<<b<< std::endl;
        Draw(rod);
        return;
    }
    hanoi(n-1,a,c,b,rod);
    move(a,b,rod);
    std::cout << "Auto moving:"<<a<<"->"<<b<< std::endl;
    Draw(rod);
    hanoi(n-1,c,b,a,rod);
}
void  autoMode(stack &cmd,list rod[]){
    int p_from,p_to;
    while (!cmd.isEmpty()) {
        cmd.pop(p_from,p_to);
        move(p_to,p_from,rod);
        std::cout << "Auto moving:"<<p_to<<"->"<<p_from<< std::endl;
        Draw(rod);
    }
    int n = rod[0].size()+1;
    hanoi(n,1,2,3,rod);
}
void en_hanoi(int a,int b,int c,int A,int B,int C,list rod[]){
    hanoi(c+b,A,B,C,rod);
    hanoi(c,B,C,A,rod);
}
void En_autoMode(stack &cmd,list rod[],int a,int b,int c){
    int p_from,p_to;
    while (!cmd.isEmpty()) {
        cmd.pop(p_from,p_to);
        move(p_to,p_from,rod);
        std::cout << "Auto moving:"<<p_to<<"->"<<p_from<< std::endl;
        Draw(rod);
    }
    en_hanoi(a,b,c,1,2,3,rod);
}
void play(list rod[]){
    stack cmd;
    string op;
    while(true){
        std::cout << "Move a disk. Format: x y" << std::endl;
        getline(std::cin,op);
        try {
            if(op[0] == '-'){
                int a,b,c;
                a = op[1] - '0';
                b = op[4] - '0';
                c = op[7] - '0';
                if(a+b+c != rod[0].size()+rod[1].size()+rod[2].size()+3)
                    continue;
                En_autoMode(cmd,rod,a,b,c);
                std::cout << "Congratulations! You win!" << std::endl;
                break;
            }
            stringstream ss(op);
            int from,to;
            ss>>from>>to;
            if(from==0&&to==0){
                autoMode(cmd,rod);
                std::cout << "Congratulations! You win!" << std::endl;
                break;
            }
            else{
                move(from,to,rod);
                cmd.push(from,to);
                Draw(rod);
                if(rod[0].isEmpty()&&rod[2].isEmpty()){
                    std::cout << "Congratulations! You win!" << std::endl;
                    break;
                 }
            }
        }  catch (const char*) {
            continue;
        }
    }
}
void run(){
    string num;
    while (true) {
        std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
        getline(std::cin,num);
        if(num == "Q") break;
        int x = atoi(num.c_str());
        if(x<=0||x>5) continue;
        else if(x>=1&&x<=5){
            list f_rod(x),s_rod(x),t_rod(x);
            list rod[]={list(x),list(x),list(x)};
            for(int i = x;i >= 1;i--)
                rod[0].push(i);
            Draw(rod);
            play(rod);
        }
    }
}
int main() {
    run();
    return 0;
}
