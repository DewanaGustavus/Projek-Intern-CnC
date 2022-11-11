#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    int N,M;
    const int NMAX = 1e5;
    vector<string> friendsA;
    vector<string> friendsB;

    long long ans;
    void InputFormat() {
        LINE(N, M);
        LINES(friendsA, friendsB);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 < N && N <= NMAX);
        CONS(0 < M && M <= NMAX);
        CONS(FriendCons(friendsA, friendsB));
    }
private:
    bool FriendCons(vector<string> friendsA, vector<string> friendsB){
        set<string> names;
        bool inbound = true;
        
        for(string name:friendsA){
            names.insert(name);
            if(name.size() > 10 || name.size() == 0)inbound = false;
            for(char ch:name){
                if(ch-'a'<0 || ch-'a'>25){
                    inbound = false;
                }
            }
        }

        for(string name:friendsB){
            names.insert(name);
            if(name.size() > 10 || name.size() == 0)inbound = false;
            for(char ch:name){
                if(ch-'a'<0 || ch-'a'>25){
                    inbound = false;
                }
            }
        }

        if(names.size() > N || friendsA.size() != M || friendsA.size() != friendsB.size()){
            inbound = false;
        }
        return inbound;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5 3",
            "gura ame",
            "calli gura",
            "ina kiara"
        });
        Output({
            "6"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "4 1",
            "botan lamy"
        });
        Output({
            "5"
        });
    }

    void BeforeTestCase() {
        friendsA.clear();
        friendsB.clear();
    }

    void TestCases(){
        for(int i=0;i<5;i++)CASE(N=10, M=10, random_friend(N,M,friendsA,friendsB));
        for(int i=0;i<5;i++)CASE(N=100, M=300, random_friend(N,M,friendsA,friendsB));
        for(int i=0;i<5;i++)CASE(N=1000, M=10000, random_friend(N,M,friendsA,friendsB));
        for(int i=0;i<5;i++)CASE(N=1000, M=NMAX, random_friend(N,M,friendsA,friendsB));
        for(int i=0;i<5;i++)CASE(N=NMAX, M=1000, random_friend(N,M,friendsA,friendsB));
        for(int i=0;i<5;i++)CASE(N=NMAX, M=NMAX, random_friend(N,M,friendsA,friendsB));
        for(int i=0;i<5;i++)CASE(N=rnd.nextInt(2,NMAX), M=rnd.nextInt(1,min(NMAX, (N*(N-1))/2)), random_friend(N,M,friendsA,friendsB));
    }

private:
    void random_friend(int N, int M, vector<string>& friendsA, vector<string>& friendsB){
        set<string> namelist;
        map<int, string> nameidx;

        int curridx = 0;
        while(curridx != N){
            string newname = generatename();
            if(namelist.count(newname) == 0){
                namelist.insert(newname);
                nameidx[curridx] = newname;
                curridx++;
            }
        }
        
        set<pair<int,int>> appear;
        for(int i=0;i<M;i++){
            int a,b;
            do{
                a = rnd.nextInt(0, N-1);
                b = rnd.nextInt(0, N-1);
            }while(appear.count({a,b}) || a==b);
            appear.insert({a,b});
            friendsA.push_back(nameidx[a]);
            friendsB.push_back(nameidx[b]);
        }
    }

    string generatename(){
        int length = rnd.nextInt(1,10);
        string name(length, '.');
        for(int i=0;i<length;i++){
            int tmp = rnd.nextInt(0,25);
            char alphabet = tmp + 'a';
            name[i] = alphabet;
        }
        return name;
    }
};