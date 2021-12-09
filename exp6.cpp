#include<iostream>
#include<fstream>
#include<cstring>
#include<omp.h>

using namespace std;

string filename[4] = {"p.txt","p.txt","p.txt","p.txt"};
string word[4] = {"aaa", "p", "q", "aa"};
int main(){
double st=omp_get_wtime();
    for(int i=0;i<4;i++){
        for(int j=1;j<=8;j*=2){
            #pragma omp parallel for num_threads(j) 
            for(int k=0;k<4;k++){
                int count = 0;
                fstream file;
                string word1;
                file.open(filename[i].c_str());
                while (file >> word1)
                {
                    if(strcmpi(word[k].c_str(),word1.c_str())==0)
                        count++;
                }
                cout<<count<<" "<<word[k]<<endl;
                cout<<"Time "<<omp_get_wtime()-st<<endl;
            }
        }
    }
