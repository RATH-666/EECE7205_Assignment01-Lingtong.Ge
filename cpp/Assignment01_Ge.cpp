#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <numeric>
#include <climits>

using namespace std;

// ==================== Problem 1 ===================
vector<vector<int>> mergeIntervals(vector<vector<int>> intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
             return a[0] < b[0];});

    vector<vector<int>> merged;
    for (const auto& interval : intervals) {
        if (merged.empty() || interval[0] > merged.back()[1]) {
            merged.push_back(interval);
        } else {
            merged.back()[1] = max(merged.back()[1], interval[1]);
        }
    }
    return merged;
}


// ==================== Problem 2 ====================
void sortColorsCounting(vector<int>& nums) {
    int count0 = 0, count1 = 0, count2 = 0;
    for (int x : nums) {
        if (x == 0) count0++;
        else if (x == 1) count1++;
        else count2++;
    }
    int idx = 0;
    while (count0--) nums[idx++] = 0;
    while (count1--) nums[idx++] = 1;
    while (count2--) nums[idx++] = 2;
}

void sortColorsDutch(vector<int>& nums) {
    int low = 0, mid = 0, high = (int)nums.size() - 1;
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

// ==================== Problem 3 ====================
string largestNumber(vector<int> nums) {
    if (nums.empty()) return "0";

    vector<string> strs;
    for (int x : nums) strs.push_back(to_string(x));

    sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
        return a + b > b + a;
    });

    if (strs[0] == "0") return "0";

    string result;
    for (const string& s : strs) result += s;
    return result;
}

// ==================== Problem 4 ====================
vector<vector<string>> groupAnagrams(vector<string> strs) {
    unordered_map<string, vector<string>> map;
    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        map[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& pair : map) {
        result.push_back(pair.second);
    }
    return result;
}

// ======== Problem 5 =========
bool canAttendAll(vector<vector<int>> intervals) {
    if (intervals.size() <= 1) return true;

    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[0] < b[0];
         });

    for (size_t i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] < intervals[i - 1][1]) {
            return false;
        }
    }
    return true;
}

// ==================== Problem 6 ====================
vector<vector<int>> kClosestSort(vector<vector<int>> points, int k) {
    sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
        int da = a[0] * a[0] + a[1] * a[1];
        int db = b[0] * b[0] + b[1] * b[1];
        return da < db;
    });
    if (k > (int)points.size()) k = (int)points.size();
    return vector<vector<int>>(points.begin(), points.begin() + k);
}

vector<vector<int>> kClosestHeap(vector<vector<int>> points, int k) {
    if (k <= 0) return {};
    auto cmp = [](const vector<int>& a, const vector<int>& b) {
        int da = a[0] * a[0] + a[1] * a[1];
        int db = b[0] * b[0] + b[1] * b[1];
        return da < db; // max heap
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> maxHeap(cmp);

    for (const auto& p : points) {
        maxHeap.push(p);
        if ((int)maxHeap.size() > k) {
            maxHeap.pop();
        }
    }

    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return result;
}

// ==================== Problem 7 ====================
vector<int> topKFrequent(vector<int> nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    vector<pair<int, int>> items;
    for (auto& p : freq) {
        items.push_back({p.first, p.second});
    }

    sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    vector<int> result;
    for (int i = 0; i < k && i < (int)items.size(); i++) {
        result.push_back(items[i].first);
    }
    return result;
}

// ========= Problem 8 ============
vector<int> mergeKSorted(vector<vector<int>> arrays) {
    struct Node {
        int value;
        int arrayIndex;
        int elementIndex;
        bool operator>(const Node& other) const {
            return value > other.value;
        }
    };

    priority_queue<Node, vector<Node>, greater<Node>> minHeap;
    for (int i = 0; i < (int)arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }

    vector<int> result;
    while (!minHeap.empty()) {
        Node node = minHeap.top();
        minHeap.pop();
        result.push_back(node.value);

        int nextIndex = node.elementIndex + 1;
        if (nextIndex < (int)arrays[node.arrayIndex].size()) {
            minHeap.push({arrays[node.arrayIndex][nextIndex], node.arrayIndex, nextIndex});
        }
    }
    return result;
}

// ==================== Problem 9 ====================
int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (nums[j] <= pivot) {
            swap(nums[i], nums[j]);
            i++;
        }
    }
    swap(nums[i], nums[right]);
    return i;
}

int findKthLargest(vector<int> nums, int k) {
    int target = (int)nums.size() - k;
    int left = 0, right = (int)nums.size() - 1;

    while (true) {
        int pivotIndex = partition(nums, left, right);
        if (pivotIndex == target) {
            return nums[pivotIndex];
        } else if (pivotIndex < target) {
            left = pivotIndex + 1;
        } else {
            right = pivotIndex - 1;
        }
    }
}

// ==================== Problem 10 ====================
long long mergeAndCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            count += (mid - i + 1);
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
    return count;
}

long long mergeSortCount(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    long long count = 0;
    count += mergeSortCount(arr, temp, left, mid);
    count += mergeSortCount(arr, temp, mid + 1, right);
    count += mergeAndCount(arr, temp, left, mid, right);
    return count;
}

long long countInversions(vector<int> values) {
    if (values.size() <= 1) return 0;
    vector<int> temp(values.size());
    return mergeSortCount(values, temp, 0, (int)values.size() - 1);
}

// ==================== Utility Functions ====================
template <typename T>
void printVector(const vector<T>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

void printIntervals(const vector<vector<int>>& intervals) {
    cout << "[";
    for (size_t i = 0; i < intervals.size(); i++) {
        if (i > 0) cout << ", ";
        cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]";
    }
    cout << "]";
}

void printStringGroups(const vector<vector<string>>& groups) {
    cout << "[";
    for (size_t i = 0; i < groups.size(); i++) {
        if (i > 0) cout << ", ";
        printVector(groups[i]);
    }
    cout << "]";
}

void printPoints(const vector<vector<int>>& points) {
    cout << "[";
    for (size_t i = 0; i < points.size(); i++) {
        if (i > 0) cout << ", ";
        cout << "[" << points[i][0] << "," << points[i][1] << "]";
    }
    cout << "]";
}

// ==================== Menu ====================
int main() {
    int choice;
    do {
        cout << "\n===== Assignment 01 Menu =====\n";
        cout << "1. Merge Intervals\n";
        cout << "2. Sort Colors (0,1,2)\n";
        cout << "3. Largest Number\n";
        cout << "4. Group Anagrams\n";
        cout << "5. Can Attend All Meetings\n";
        cout << "6. K Closest Points\n";
        cout << "7. Top K Frequent Elements\n";
        cout << "8. Merge K Sorted Arrays\n";
        cout << "9. Kth Largest Element\n";
        cout << "10. Count Inversions\n";
        cout << "0. Exit\n";
        cout << "Choose a problem: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- Problem 1: Merge Intervals ---\n";

            vector<vector<int>> t1 = {{1,3},{2,6},{8,10},{15,18}};
            cout << "Example input:    "; printIntervals(t1); cout << "\n";
            cout << "Example output:   "; printIntervals(mergeIntervals(t1)); cout << "\n\n";

            vector<vector<int>> t2 = {{1,4},{4,5}};
            cout << "Additional 1 in:  "; printIntervals(t2); cout << "\n";
            cout << "Additional 1 out: "; printIntervals(mergeIntervals(t2)); cout << "\n\n";

            vector<vector<int>> t3 = {};
            cout << "Edge input:       "; printIntervals(t3); cout << "\n";
            cout << "Edge output:      "; printIntervals(mergeIntervals(t3)); cout << "\n";
        }
        else if (choice == 2) {
            cout << "\n--- Problem 2: Sort Colors ---\n";

            vector<int> t1 = {2,0,2,1,1,0};
            cout << "Example input:    "; printVector(t1); cout << "\n";
            auto a1 = t1; sortColorsCounting(a1);
            cout << "  Counting out:   "; printVector(a1); cout << "\n";
            auto b1 = t1; sortColorsDutch(b1);
            cout << "  Dutch out:      "; printVector(b1); cout << "\n\n";

            vector<int> t2 = {2,2,2};
            cout << "Additional 1 in:  "; printVector(t2); cout << "\n";
            auto a2 = t2; sortColorsCounting(a2);
            cout << "  Counting out:   "; printVector(a2); cout << "\n";
            auto b2 = t2; sortColorsDutch(b2);
            cout << "  Dutch out:      "; printVector(b2); cout << "\n\n";

            vector<int> t3 = {};
            cout << "Edge input:       "; printVector(t3); cout << "\n";
            auto a3 = t3; sortColorsCounting(a3);
            cout << "  Counting out:   "; printVector(a3); cout << "\n";
            auto b3 = t3; sortColorsDutch(b3);
            cout << "  Dutch out:      "; printVector(b3); cout << "\n";
        }
        else if (choice == 3) {
            cout << "\n--- Problem 3: Largest Number ---\n";

            vector<int> t1 = {10,2};
            cout << "Example input:    "; printVector(t1); cout << "\n";
            cout << "Example output:   " << largestNumber(t1) << "\n\n";

            vector<int> t2 = {3,30,34,5,9};
            cout << "Additional 1 in:  "; printVector(t2); cout << "\n";
            cout << "Additional 1 out: " << largestNumber(t2) << "\n\n";

            vector<int> t3 = {0,0};
            cout << "Edge input:       "; printVector(t3); cout << "\n";
            cout << "Edge output:      " << largestNumber(t3) << "\n";
        }
        else if (choice == 4) {
            cout << "\n--- Problem 4: Group Anagrams ---\n";

            vector<string> t1 = {"eat","tea","tan","ate","nat","bat"};
            cout << "Example input:    "; printVector(t1); cout << "\n";
            cout << "Example output:   "; printStringGroups(groupAnagrams(t1)); cout << "\n\n";

            vector<string> t2 = {""};
            cout << "Additional 1 in:  "; printVector(t2); cout << "\n";
            cout << "Additional 1 out: "; printStringGroups(groupAnagrams(t2)); cout << "\n\n";

            vector<string> t3 = {};
            cout << "Edge input:       "; printVector(t3); cout << "\n";
            cout << "Edge output:      "; printStringGroups(groupAnagrams(t3)); cout << "\n";
        }
        else if (choice == 5) {
            cout << "\n--- Problem 5: Can Attend All Meetings ---\n";

            vector<vector<int>> t1 = {{0,30},{5,10},{15,20}};
            cout << "Example input:    "; printIntervals(t1); cout << "\n";
            cout << "Example output:   " << (canAttendAll(t1) ? "true" : "false") << "\n\n";

            vector<vector<int>> t2 = {{7,10},{2,4}};
            cout << "Additional 1 in:  "; printIntervals(t2); cout << "\n";
            cout << "Additional 1 out: " << (canAttendAll(t2) ? "true" : "false") << "\n\n";

            vector<vector<int>> t3 = {};
            cout << "Edge input:       "; printIntervals(t3); cout << "\n";
            cout << "Edge output:      " << (canAttendAll(t3) ? "true" : "false") << "\n";
        }
        else if (choice == 6) {
            cout << "\n--- Problem 6: K Closest Points ---\n";

            vector<vector<int>> t1 = {{1,3},{-2,2}};
            int k1 = 1;
            cout << "Example input:    "; printPoints(t1); cout << ", k = " << k1 << "\n";
            cout << "  Sort out:       "; printPoints(kClosestSort(t1, k1)); cout << "\n";
            cout << "  Heap out:       "; printPoints(kClosestHeap(t1, k1)); cout << "\n\n";

            vector<vector<int>> t2 = {{3,3},{5,-1},{-2,4}};
            int k2 = 2;
            cout << "Additional 1 in:  "; printPoints(t2); cout << ", k = " << k2 << "\n";
            cout << "  Sort out:       "; printPoints(kClosestSort(t2, k2)); cout << "\n";
            cout << "  Heap out:       "; printPoints(kClosestHeap(t2, k2)); cout << "\n\n";

            vector<vector<int>> t3 = {};
            int k3 = 0;
            cout << "Edge input:       "; printPoints(t3); cout << ", k = " << k3 << "\n";
            cout << "  Sort out:       "; printPoints(kClosestSort(t3, k3)); cout << "\n";
            cout << "  Heap out:       "; printPoints(kClosestHeap(t3, k3)); cout << "\n";
        }
        else if (choice == 7) {
            cout << "\n--- Problem 7: Top K Frequent Elements ---\n";

            vector<int> t1 = {1,1,1,2,2,3};
            int k1 = 2;
            cout << "Example input:    "; printVector(t1); cout << ", k = " << k1 << "\n";
            cout << "Example output:   "; printVector(topKFrequent(t1, k1)); cout << "\n\n";

            vector<int> t2 = {1};
            int k2 = 1;
            cout << "Additional 1 in:  "; printVector(t2); cout << ", k = " << k2 << "\n";
            cout << "Additional 1 out: "; printVector(topKFrequent(t2, k2)); cout << "\n\n";

            vector<int> t3 = {4,4,4,4};
            int k3 = 1;
            cout << "Edge input:       "; printVector(t3); cout << ", k = " << k3 << "\n";
            cout << "Edge output:      "; printVector(topKFrequent(t3, k3)); cout << "\n";
        }
        else if (choice == 8) {
            cout << "\n--- Problem 8: Merge K Sorted Arrays ---\n";

            vector<vector<int>> t1 = {{1,4,5},{1,3,4},{2,6}};
            cout << "Example input:    ";
            for (auto& a : t1) { printVector(a); cout << " "; }
            cout << "\n";
            cout << "Example output:   "; printVector(mergeKSorted(t1)); cout << "\n\n";

            vector<vector<int>> t2 = {{1,2,3},{4,5,6}};
            cout << "Additional 1 in:  ";
            for (auto& a : t2) { printVector(a); cout << " "; }
            cout << "\n";
            cout << "Additional 1 out: "; printVector(mergeKSorted(t2)); cout << "\n\n";

            vector<vector<int>> t3 = {};
            cout << "Edge input:       []\n";
            cout << "Edge output:      "; printVector(mergeKSorted(t3)); cout << "\n";
        }
        else if (choice == 9) {
            cout << "\n--- Problem 9: Kth Largest Element ---\n";

            vector<int> t1 = {3,2,1,5,6,4};
            int k1 = 2;
            cout << "Example input:    "; printVector(t1); cout << ", k = " << k1 << "\n";
            cout << "Example output:   " << findKthLargest(t1, k1) << "\n\n";

            vector<int> t2 = {3,2,3,1,2,4,5,5,6};
            int k2 = 4;
            cout << "Additional 1 in:  "; printVector(t2); cout << ", k = " << k2 << "\n";
            cout << "Additional 1 out: " << findKthLargest(t2, k2) << "\n\n";

            vector<int> t3 = {1};
            int k3 = 1;
            cout << "Edge input:       "; printVector(t3); cout << ", k = " << k3 << "\n";
            cout << "Edge output:      " << findKthLargest(t3, k3) << "\n";
        }
        else if (choice == 10) {
            cout << "\n--- Problem 10: Count Inversions ---\n";

            vector<int> t1 = {2,4,1,3,5};
            cout << "Example input:    "; printVector(t1); cout << "\n";
            cout << "Example output:   " << countInversions(t1) << "\n\n";

            vector<int> t2 = {5,4,3,2,1};
            cout << "Additional 1 in:  "; printVector(t2); cout << "\n";
            cout << "Additional 1 out: " << countInversions(t2) << "\n\n";

            vector<int> t3 = {};
            cout << "Edge input:       "; printVector(t3); cout << "\n";
            cout << "Edge output:      " << countInversions(t3) << "\n";
        }
        else if (choice == 0) {
            cout << "Exiting.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

        cout << "\n";
    } while (choice != 0);

    return 0;
}