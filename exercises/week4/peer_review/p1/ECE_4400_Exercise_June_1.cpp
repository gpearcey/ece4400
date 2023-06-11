#include <iostream>
#include <vector> 
#include <string>
#include <cmath>


using namespace std;

template<typename Iter>
void radixSort(const Iter& begin, const Iter& end){

    //Vectors that will used to help sort. as the program iterates through the numbers, they will be stored and later
    //retrived from these vectors.
    vector<int> Zero_vec;
    vector<int> One_vec;
    vector<int> Two_vec;
    vector<int> Three_vec;
    vector<int> Four_vec;
    vector<int> Five_vec;
    vector<int> Six_vec;
    vector<int> Sev_vec;
    vector<int> Eight_vec;
    vector<int> Nine_vec;

    int largest_int_size = 0;
    int len_of_int;
    int index;

    //*Iter is the method used for getting the value of the integer at a certain index.

    for(Iter i = begin; i != end; ++i){
        int value = *i;
        if (value == 0){
            len_of_int = 1;
        }
        else{
            len_of_int = floor(log10(abs(value))) + 1;
        }

        if (largest_int_size < len_of_int){
            largest_int_size = len_of_int;
        }
    }

    //To index the numbers in the int convert it to a string with "to_string".
    for(int n = 1; n <= largest_int_size; ++n){
        for(Iter i = begin; i != end; ++i){
            int value = *i;
            if (value == 0){
                len_of_int = 1;
            }
            else{
                len_of_int = floor(log10(abs(value))) + 1;
            }   

            if((len_of_int - n) < 0){
                Zero_vec.push_back(value);
            }
            else{
                string integer_as_string = to_string(value);

                switch (stoi(string(1, integer_as_string[len_of_int - n])))
                {
                case 0:
                    Zero_vec.push_back(value);
                    break;
                case 1:
                    One_vec.push_back(value);
                    break;
                case 2:
                    Two_vec.push_back(value);
                    break;
                case 3:
                    Three_vec.push_back(value);
                    break;
                case 4:
                    Four_vec.push_back(value);
                    break;
                case 5:
                    Five_vec.push_back(value);
                    break;
                case 6:
                    Six_vec.push_back(value);
                    break;
                case 7:
                    Sev_vec.push_back(value);
                    break;
                case 8:
                    Eight_vec.push_back(value);
                    break;
                case 9:
                    Nine_vec.push_back(value);
                    break;
                default:
                    break;
                }
            }
        }

        //Adds all of the vectors to the Zero_vec for simple iteration in the next step
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(One_vec.begin()), make_move_iterator(One_vec.end()));
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(Two_vec.begin()), make_move_iterator(Two_vec.end()));
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(Three_vec.begin()), make_move_iterator(Three_vec.end()));
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(Four_vec.begin()), make_move_iterator(Four_vec.end()));
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(Five_vec.begin()), make_move_iterator(Five_vec.end()));
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(Six_vec.begin()), make_move_iterator(Six_vec.end()));
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(Sev_vec.begin()), make_move_iterator(Sev_vec.end()));
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(Eight_vec.begin()), make_move_iterator(Eight_vec.end()));
        Zero_vec.insert(Zero_vec.end(), make_move_iterator(Nine_vec.begin()), make_move_iterator(Nine_vec.end()));

        index = 0;
        for(Iter i = begin; i != end; ++i){
            *i = Zero_vec[index];
            index++;
        }

        //Clears all of the vectors for the next loops
        Zero_vec.clear();
        One_vec.clear();
        Two_vec.clear();
        Three_vec.clear();
        Four_vec.clear();
        Five_vec.clear();
        Six_vec.clear();
        Sev_vec.clear();
        Eight_vec.clear();
        Nine_vec.clear();
    }
}


int main(){
    // Test case
    vector<int> numbers = {170, 0, 75, 90, 802, 24, 2, 66, 543, 2, 1234, 56, 9, 130};
    cout << "Before sorting: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    radixSort(numbers.begin(), numbers.end());

    cout << "After sorting: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;


    return 0;
}