/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include "templates.h"
using namespace std;


int main()
{
	/**
	 * Testing function and GrowableArray class in templates.h
	*/


	//ints
	cout << "Integers" << "\n";
	int x = 1, y = 1;
	cout << "x + y = " << add(x,y) << "\n";

	std::vector<int> values_int = {1,2,3,4,5};
	cout << "average is " << average(values_int) << "\n";
	cout << "\n";

	//doubles 
	cout << "Doubles" << "\n";
	double z = 1.4, w = 1;
	cout << "x + y = " << add(z,w) << "\n";

	std::vector<double> values_db = {1,2,3,4,5.4,34.2};
	cout << "average is " << average(values_db) << "\n";
	values_db = {};
	cout << "average is " << average(values_db) << "\n";
	cout << "\n";

	//strings
	cout << "Strings" << "\n";
	string a = "1.4", b = "1";
	cout << "x + y = " << add(a,b) << "\n";

	std::vector<string> values_str = {"1","2","3","4","5.4","34.2"};
	cout << "average is " << average(values_str) << "\n";
	cout << "\n";

	//Growable Array

	//String
	GrowableArray<string, 8> gArr_str;
	
	for(int i = 0; i < 8; i++){
		string value = std::to_string(i);
		gArr_str << value;
	}

	cout << "String Array" << "\n";
	for(int i = 0; i < 8; i++){
		cout << gArr_str[i] << "\n";
	}
	cout << "\n";
	cout << "average: " << gArr_str.average() << endl;

	//Double
	GrowableArray<double, 8> gArr_db;
	
	for(int i = 0; i < 20; i++){
		gArr_db << i+0.1;
	}

	cout << "Double Array" << "\n";
	for(int i = 0; i < 20; i++){
		cout << gArr_db[i] << "\n";
	}
	cout << "\n";

	cout << "average: " << gArr_db.average() << endl;

	//Integer
	GrowableArray<int, 8> gArr_int;
	
	for(int i = 4; i < 14; i++){
		gArr_int << i;
	}

	cout << "Integer Array" << "\n";
	for(int i = 0; i < 10; i++){
		cout << gArr_int[i] << "\n";
	}
	cout << "\n";

	cout << "average: " << gArr_int.average() << endl;



	return 0;
}
