#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct subArray
{
    int low;
    int high;
    float sum;
};

subArray MaxCrossingSum(float arr[], int low, int mid, int high);
std::vector<subArray> MaxSubArraySum(float arr[], int low, int high);
using namespace std;

int main()
{
    string line;
    ifstream myFile;
    myFile.open("data.txt");
    int count = 0;

    while (getline(myFile, line))
    {
        count++;
    }

    float *data = new float[count];

    fstream input("data.txt", ios_base::in);
    float temp;
    for (int i = 0; i < 2 * (count); i++)
    {
        input >> temp;
        if (i % 2 == 0)
            continue;
        data[i / 2] = temp;
    }

    // Close file
    myFile.close();

    // for (int i = 1; i < count + 1; i++) {
    // cout << data[i] << endl;
    // }

    vector<subArray> results = MaxSubArraySum(data, 0, count - 1);

    // find the minimum length of all sub-arrays
    int minLength = INT_MAX;
    for (subArray result : results)
    {
        int length = result.high - result.low + 1;
        if (length < minLength)
        {
            minLength = length;
        }
    }

    // create a new vector to store only the sub-arrays with the minimum length
    vector<subArray> minSubArrays;
    for (subArray result : results)
    {
        int length = result.high - result.low + 1;
        if (length == minLength)
        {
            minSubArrays.push_back(result);
        }
    }

    // print the sub-arrays with the minimum length
    cout << "The minimum length sub-arrays are:" << endl;
    for (subArray result : minSubArrays)
    {
        cout << "[" << result.low + 1 << ", " << result.high + 1 << "] with sum = " << result.sum << endl;
    }
}

subArray MaxCrossingSum(float arr[], int low, int mid, int high)
{
    subArray result;
    result.sum = 0;

    // Include elements having index value less than or equal to the mid.
    float sum = 0;
    int leftpartsum = INT_MIN;
    int leftIndex = mid;
    for (int i = mid; i >= low; i--)
    {
        sum = sum + arr[i];
        if (sum > leftpartsum)
        {
            leftpartsum = sum;
            leftIndex = i;
        }
    }

    // Include elements having index value greater mid.
    sum = 0;
    int rightpartsum = INT_MIN;
    int rightIndex = mid + 1;
    for (int i = mid + 1; i <= high; i++)
    {

        sum = sum + arr[i];
        if (sum > rightpartsum)
        {
            rightpartsum = sum;
            rightIndex = i;
        }
    }

    result.sum = leftpartsum + rightpartsum;
    result.low = leftIndex;
    result.high = rightIndex;

    // Return sum of elements on left and right of mid.
    return result;
}

vector<subArray> MaxSubArraySum(float arr[], int low, int high)
{
    vector<subArray> results;

    // If low index is equal to the high index h then the subarray contains only one element.
    if (low == high)
    {
        subArray result;
        result.low = low;
        result.high = high;
        result.sum = arr[low];
        results.push_back(result);
        return results;
    }

    // Otherwise find the mid index and proceed.
    int mid = (low + high) / 2;

    // Maximum sum sub-array can be either in the left part, right part or covering elements from both parts.
    vector<subArray> leftResults = MaxSubArraySum(arr, low, mid);
    vector<subArray> rightResults = MaxSubArraySum(arr, mid + 1, high);
    subArray crossResult = MaxCrossingSum(arr, low, mid, high);

    // Find the maximum sum among the left, right and cross results
    float maxSum = max(max(leftResults[0].sum, rightResults[0].sum), crossResult.sum);

    // Add all subarrays from left and right results with maximum sum
    for (subArray result : leftResults)
    {
        if (result.sum == maxSum)
        {
            results.push_back(result);
        }
    }
    for (subArray result : rightResults)
    {
        if (result.sum == maxSum)
        {
            results.push_back(result);
        }
    }

    // If the maximum sum subarray crosses the mid point, add it to the results
    if (crossResult.sum == maxSum)
    {
        results.push_back(crossResult);
    }

    return results;
}