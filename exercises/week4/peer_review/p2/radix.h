#pragma once

#include <vector>
#include <algorithm>
#include <string>

template <typename T>
void radixSort(std::vector<T>& arr)
{
    if (arr.empty())
        return;

    size_t maxLen = 0;
    for (const auto& str : arr)
    {
        if (str.length() > maxLen)
            maxLen = str.length();
    }

    for (int pos = maxLen - 1; pos >= 0; --pos)
    {
        std::vector<T> output(arr.size());
        std::vector<int> count(256, 0);

        for (const auto& str : arr)
        {
            if (str.length() > pos)
                count[static_cast<unsigned char>(str[pos])]++;
        }

        for (size_t i = 1; i < count.size(); i++)
            count[i] += count[i - 1];

        for (int i = arr.size() - 1; i >= 0; i--)
        {
            if (arr[i].length() > pos)
            {
                output[count[static_cast<unsigned char>(arr[i][pos])] - 1] = arr[i];
                count[static_cast<unsigned char>(arr[i][pos])]--;
            }
            else
            {
                output[count[0] - 1] = arr[i];
                count[0]--;
            }
        }

        for (size_t i = 0; i < arr.size(); i++)
            arr[i] = output[i];
    }
}