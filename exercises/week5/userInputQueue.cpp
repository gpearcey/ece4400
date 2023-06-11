#include "queue.h"
#include <string>
#include <iostream>
#include <vector>

/**Queue Class
 * Still in Progress
*/
using namespace std;

void ParseInput(std::string input, Queue<int>& q){
    std::vector<std::string> words;
    std::string word;
    for (auto c : input){
        if (c == ' '){
            words.push_back(word);
            word = "";
        }
        else {
            word = word + c;
        }
    }

    if (words[0] == "enqueue"){
        int n = std::stoi(words[1]);
        q.enqueue(n);
    }
    else if (words[0] == "dequeue"){
        if (!q.empty()){
            int n = q.dequeue();
            cout << "Removed " << n << " from array" << endl;
        }
        else {
            cout << "queue is empty cannot remove anything" << endl;
        }
    }
    else {
        cout << "invalid format" << endl;
    }
}

int main(){

    Queue<int> q;

    while (true){
        std::string user_input;
        std::vector<std::string> words;
        
        cout << "Tell me what integer you want to enqueue or dequeue. For example: 'enqueue 4' ";
        cin >> user_input;
        cout << endl;
        ParseInput(user_input, q);

    }
};