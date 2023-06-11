#include <iostream>
using namespace std;

int main()
{
    double Numbers[] = {5, 2.2, 4, 9, 6};
    double temp;
    double C;
    int sizing = sizeof(Numbers);

for(int i = 0; i <  sizing; i++){
	for(int j = 0; j < sizing-i; j++){
    	if (Numbers[i] > Numbers[j])
            temp = Numbers[i];
            Numbers[i] = Numbers[j];
            Numbers[j] = temp;
        C++;
        }
        }
 cout << Numbers << endl;        
return 0;

}
