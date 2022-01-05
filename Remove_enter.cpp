#include<iostream>
#include<string>

using namespace std;

int main() {


    while(true) {
        cout << "Enter sentenses (ctrl+z to finish):\n";
        string s, total;
        while(getline(cin, s)){
            total += s;
        }
        cin.clear();
        cout << total << endl;
    }





    return 0;
}