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
#include <vector>
#include "templates.h"

using namespace std;

int main()
{

    
    GrowableArray<std::string,8> stringArray;
    
    stringArray << "Hello" << "World";
  
    //returns "World"
    cout << stringArray[1]<< endl;
    
    
    GrowableArray<double,8> Array;
    
    // Add values to the Array
    Array << 10.1 << 20 << 30.1 << 40 << 50;
    
    // Returns 30.04
    cout << Array.average()<< endl;
    

    
    

    
    
}

