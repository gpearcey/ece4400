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

template<typename Iter, typename Comparator>
void bubbleSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
}

template<typename Iter>
void insertionSort(const Iter& begin, const Iter& end)
{   
    int extraction;
    for(Iter i = (begin + 1); i != end; ++i){
        int extraction = *i;
        Iter n = i;
        while(n != begin && extraction < *(n - 1)){
            *n = *(n-1);
            --n;
        }
        *n = extraction;
    }
}