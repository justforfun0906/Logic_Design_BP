#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <utility>
#include <string>
#include <string.h>
#include <math.h>

using namespace std;


class QM{
private:
    int var_num;
    int term_num;

    vector<string> minterm;     // store minterm
    vector<string> prime;       // prime after QM 
    vector<string> out_prime;   // final output prime 


public:

    bool hit(string &a, string &b, string &out){
        // check whether a and b can be merged 
        // if can merge, return true and store the merged term in out
        int flag = 0, index = -1;
        for(int i = 0; i < a.length();i++){
            if(a[i]!=b[i]){
                if(flag==0){
                    flag = 1;
                    index = i;
                }
                else{
                    return false;
                }
            }
        }
        out = a;
        out[index] = '-';
        return true;
    }
    
    void init(ifstream &in){
        // read input from file
        in>>var_num;
        in>>term_num;
        string temp;
        for(int i = 0; i < term_num; i++){
            in>>temp;
            minterm.push_back(temp);
        }
    }
    
    void merge_implicants(){
        // Merges groups of minterms with one difference into a single term with a dash ("-").

    }
    

    void find_prime_implicants(){
        int time = 0;
        while(time <= var_num){
            merge_implicants();
            time++;
        }
    }

    

    void find_essential_prime_implicants(){
        // Finds essential prime implicants from the prime implicants.

    }


    void find_min_cover(){
        // Finds the minimum cover of the left minterms 
        // after finding the essential prime implicants.

        
    }

    bool check_equal(){
        // check whether the out prime implicants are equal to the minterms
        // if equal, return true
        // Please remain vector minterm unchanged and store the result in vector out_prime before call this function

        queue<string> q;
        unordered_set<string> temp;
        unordered_map<string, bool> mp, mp2;
        for(string &a : minterm){
            mp[a] = true;
        }
        for(string &a : out_prime){  
            if(!mp2[a]){
                q.push(a);
                mp2[a] = true;
            }
        }
        while(!q.empty()){
            string a = q.front();
            q.pop();
            
            int i = 0;
            for(i = 0; i < a.length(); i++){
                if(a[i]=='-'){
                    string b = a;
                    b[i] = '0';
                    q.push(b);
                    b[i] = '1';
                    q.push(b);
                    break;
                }
            }
            if(i == a.length()){
                if(mp[a]){
                    temp.insert(a);
                }
                else{
                    cout<<"output prim cover more than minterm"<<endl;
                    cout<<"output prime implicants are not equal to the minterms\n"<<endl;
                    return false;
                }
            }
        }
        if(temp.size() == minterm.size()){
            cout<<"output prime implicants are equal to the minterms\n"<<endl;
            return true;
        }
        else{
            // cout<<"minterm size : "<<minterm.size()<<endl;
            // cout<<"Output prime expand minterm size : "<<temp.size()<<endl;
            cout<<"output prime implicants are not equal to the minterms\n"<<endl;
            
            return false;
        }
        
    }
    
    void output_prime(ofstream & out){
        int litteral_count = 0;
        for(string &a : out_prime){
            litteral_count+= var_num - count(a.begin(), a.end(), '-');
        }
        out<<litteral_count<<endl<<out_prime.size()<<endl;
        for(string &a : out_prime){
            out<<a<<endl;
        }
    }


};

int main(int argc, char* argv[]){
    QM qm;
    
    // command example: ./main ../testcase/case00.in ../output/case00.out

    
    
    ifstream in(argv[1]);
    ofstream out(argv[2]);

    // read input from file
    qm.init(in);

    // Finds the prime implicants from the minterms.
    qm.find_prime_implicants();

    // Finds essential prime implicants from the prime implicants.
    qm.find_essential_prime_implicants();

    // Finds the minimum cover of the left minterms 
    // after finding the essential prime implicants.
    qm.find_min_cover();

    // check whether the out prime implicants are equal to the minterms
    // Please remain vector minterm unchanged and store the result in vector out_prime before call this function
    qm.check_equal();

    qm.output_prime(out);
    
    return 0;
}