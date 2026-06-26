// --- Headers ---
// <iostream> gives us std::cout for printing to the terminal.
// <vector> gives us std::vector, a dynamic array that grows at runtime.
#include <iostream>
#include <vector>

// --- Class ---
// In C++, a class groups data and functions together.
// Here we use it only to hold the method, which is the LeetCode convention.
// 'public:' means the method is accessible from outside the class (e.g. from main()).
class solution {
    public:
        // --- Function signature ---
        // Returns an int (the count).
        // Takes 'nums' by reference (std::vector<int>&) — the '&' avoids copying
        // the whole vector into the function; we read it in-place.
        // 'target' is passed by value (a plain copy) since it's just one int.
        int countMajoritySubarrays(std::vector<int>& nums, int target) {

            // .size() returns a 'size_t' (unsigned), but we store it in an int
            // so we can safely use it in arithmetic with signed values below.
            int n = nums.size();
            int totalSubarrays = 0;

            // --- Outer loop: fix the left boundary of the subarray ---
            // We try every possible starting index 'i'.
            // This is the brute-force O(n²) approach: enumerate all O(n²) subarrays.
            for (int i = 0; i < n; ++i) {

                // --- Balance variable (the key insight) ---
                // Instead of counting target vs non-target separately, we encode:
                //   target element     → +1
                //   non-target element → -1
                // A running total (balance) > 0 means target has appeared
                // strictly more than half the time in nums[i..j].
                // This works because: count(target) > count(other)
                //   ⟺ count(target) - count(other) > 0
                //   ⟺ sum of (+1 / -1) encoding > 0
                // Reset to 0 each time 'i' advances — each starting point is independent.
                int balance = 0;

                // --- Inner loop: expand the right boundary ---
                // 'j' starts at 'i' so the shortest subarray we consider is length 1.
                for (int j = i; j < n; ++j) {

                    // --- Ternary operator ---
                    // (condition) ? value_if_true : value_if_false
                    // Equivalent to: if (nums[j] == target) balance += 1; else balance -= 1;
                    // '+=' accumulates: balance = balance + (result of ternary).
                    balance += (nums[j] == target) ? 1 : -1;

                    // Every time balance > 0, the subarray nums[i..j] has target
                    // as its strict majority element, so we count it.
                    if (balance > 0) totalSubarrays++;
                }
            }

            return totalSubarrays;
        }
    };

// --- main ---
// Entry point of the program. Execution starts here.
// 'int main()' must return an int; returning 0 signals success to the OS.
int main() {
    // Instantiate our solution class — 's' is an object of type 'solution'.
    solution s;

    // Brace-initializer list: creates and fills the vector in one line.
    std::vector<int> nums = {1, 2, 3, 1, 1};
    int target = 1;

    // Call the method on object 's' using the dot operator.
    // std::cout streams the result to stdout; "\n" ends the line.
    std::cout << s.countMajoritySubarrays(nums, target) << "\n";
    return 0;
}
