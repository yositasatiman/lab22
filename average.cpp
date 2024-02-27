#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc, char *argv[]){
    int sum = 0;

    if(argc < 2){
        cout << "Please input numbers to find average." << endl;
    }else{
        for(int i = 0; i < argc; i++){
            sum = sum + atoi(argv[i]);
        }
        cout << "---------------------------------\n";
        cout << "Average of " << argc - 1 << " numbers = " << sum/(argc - 1) << endl;
        cout << "---------------------------------";
    }
    
    return 0;
}
