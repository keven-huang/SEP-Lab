#include"lexicon.h"
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;
class boggle{
    public:
    Lexicon Lists;
    vector<string> BoardList;
    vector<string> UsrList;
    int Score;
    int Computer_Score;
    int N;
    char** Map;
    int ** visited;
    enum Direction{WEST,NORTH_WEST,NORTH,NORTH_EAST,EAST,SOUTH_EAST,SOUTH,SOUTH_WEST};
    boggle(){
    }
    ~boggle(){
        delete Map;
    }
    void boggle_set(){
        int M;
        cin>>M;
        N = M;
        Map = new char* [N];
        for(int i = 0;i < N;i++)
            Map[i] = new char [N];
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++){
                cin>>Map[i][j];
                if(Map[i][j]>='a'&&Map[i][j]<='z')
                    Map[i][j]+='A'-'a';
            }
        }
        visited  = new int* [N];
        for(int i = 0;i < N;i++){
            visited[i] = new int [N];
        }
        Lists.addWordsFromFile("://EnglishWords.txt");
        Score = 0;
        Computer_Score = 0;
    }
    void clear_visited(){
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++)
                visited[i][j] = 0;
        }
    }
    void print_board(){
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++){
                cout<<Map[i][j];
            }
            cout<<"\n";
        }
        cout<<"Your Score: "<<Score<<"\n";
        cout<<"Your Words: ";
        for(int i = 0;i < int(UsrList.size());i++)
            cout<<UsrList[i]<<" ";
        cout<<"\n";
    }
    void Computer_search_print(){
        cout<<"Computer Score: "<<Computer_Score<<endl;
        cout<<"Computer Words: ";
        for(int i = 0; i < int(BoardList.size());i++){
            cout<<BoardList[i]<<" ";
        }
    }
    char translate(char &x){
        if(x >= 'a'&&x <= 'z'){
            return x - 'a' + 'A';
        }
        else
            return x;
    }
    void translate(string &s){
        for(int i = 0;i<int(s.length());i++){
            s[i] = (s[i]>='a'&&s[i]<='z') ? s[i] : s[i] - 'A' + 'a';
        }
        return;
    }
    void Move(int &PosX,int &PosY,Direction dir){
        if(dir == WEST){
            PosY = PosY - 1;
        }
        else if(dir == NORTH_WEST){
            PosX = PosX - 1;
            PosY = PosY - 1;
        }
        else if(dir == NORTH){
            PosX = PosX - 1;
        }
        else if(dir == NORTH_EAST){
            PosX = PosX - 1;
            PosY = PosY + 1;
        }
        else if(dir == EAST){
            PosY = PosY + 1;
        }
        else if(dir == SOUTH_EAST){
            PosX = PosX + 1;
            PosY = PosY + 1;
        }
        else if(dir == SOUTH){
            PosX = PosX + 1;
        }
        else if(dir == SOUTH_WEST){
            PosX = PosX + 1;
            PosY = PosY - 1;
        }
    }
    bool isBounder(int PosX,int PosY,Direction dir){
        Move(PosX,PosY,dir);
        if(PosX>=0&&PosX<N&&PosY>=0&&PosY<=N)
            return false;
        return true;
    }
    bool inUsrList(string &word){
        for(int i = 0;i < int(UsrList.size());i++){
            if(UsrList[i] == word)
                return true;
        }
        return false;
    }
    void Search(int PosX,int PosY,string word){
        if(visited[PosX][PosY])
            return;
        if(!Lists.containsPrefix(word))
            return;
        if(word.length()>=4&&!inUsrList(word)&&Lists.contains(word)){
            Computer_Score += int(word.length()) -3;
            BoardList.push_back(word);
        }
        visited[PosX][PosY] = 1;
        for(int dir = WEST;dir<=SOUTH_WEST;dir++){
            int X = PosX;
            int Y = PosY;
            if(!isBounder(X,Y,Direction(dir))){
                Move(X,Y,Direction(dir));
                word += Map[X][Y];
                Search(X,Y,word);
            }
        }
        visited[PosX][PosY] = 0;
        return;
    }
    bool CanbeSearched(string &word){
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++){
                if(Map[i][j] == translate(word[0])){
                    clear_visited();
                    cout<<i<<j<<endl;
                    if(CanbeSearched(i,j,word,0))
                        return true;
                }
            }
        }
        return false;
    }
    bool CanbeSearched(int posx,int posy,string &word,int i){
        if(i == int(word.length()) - 1)
            return true;
        if(i >= int(word.length())){
            return false;
        }
        if(visited[posx][posy]){
            return false;
        }
        visited[posx][posy] = 1;
        for(int dir = WEST;dir<=SOUTH_WEST;dir++){
            cout<<dir<<endl;
            int X = posx;
            int Y = posy;
            if(!isBounder(X,Y,Direction(dir))){
                Move(X,Y,Direction(dir));
                if(Map[X][Y] == translate(word[i+1])){
                    if(CanbeSearched(X,Y,word,i+1))
                        return true;
                }
                else
                    continue;
            }
        }
        visited[posx][posy] = 0;
        return false;
    }
    void computer_search(){
        for(int i = 0;i<N;i++){
            for(int j = 0;j < N;j++){
                clear_visited();
                string s ="";
                s += Map[i][j];
                cout<<s<<endl;
                Search(i,j,s);
            }
        }
    }
    void user_search(string word){
        if(word.length()<4){
            cout<<word<<" is too short"<<endl;
            print_board();
            return;
        }
        translate(word);
        if(inUsrList(word)){
            cout<<word<<" is already found"<<endl;
            print_board();
            return;
        }
        if(!Lists.contains(word)){
            cout<<word<<" is not a word"<<endl;
            print_board();
            return;
        }
        else{
            if(CanbeSearched(word)){
                Score += word.length() - 3;
                UsrList.push_back(word);
                print_board();
            }
            else{
                cout<<word<<" is not on board"<<endl;
                print_board();
            }
            return;
        }
    }

    void User_op(){
        string op;
        while(true){
            getline(cin,op);
            if(op == "???"){
                computer_search();
                Computer_search_print();
                break;
            }
            else
                user_search(op);
        }
    }

};
int main(){
    boggle Game;
    Game.boggle_set();
    Game.User_op();
    return 0;
}
