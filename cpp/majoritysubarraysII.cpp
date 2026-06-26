// --- Headers ---
// <iostream> gives us std::cout for printing.
// <vector>   gives us std::vector, a resizable array allocated on the heap.
#include <iostream>
#include <vector>

// --- Class ---
// Groups the solution method. 'public:' makes it callable from outside (e.g. main()).
class solution {
public:
    // --- Function signature ---
    // Returns 'long long' instead of 'int' because the answer can be up to O(n²),
    // which overflows a 32-bit int for large inputs (n up to ~10⁵ → up to ~10¹⁰ subarrays).
    // 'nums' is passed by reference (&) to avoid copying the entire vector.
    long long countMajoritySubarrays(std::vector<int>& nums, int target) {
        int n = nums.size();

        // --- Core idea: prefix balance ---
        // Just like in the O(n²) version, we encode each element as +1 (target) or -1 (other).
        // Define prefixBalance[i] = sum of encodings from index 0 to i-1 (empty prefix = 0).
        //
        // A subarray nums[i+1 .. j] has target as strict majority iff:
        //   prefixBalance[j+1] - prefixBalance[i] > 0
        //   ⟺ prefixBalance[j+1] > prefixBalance[i]
        //
        // So for each position j, we want to count how many previous prefix balances
        // are strictly LESS than the current one. That count equals the number of valid
        // subarrays ending at j. This reduces the problem from O(n²) to O(n).

        // --- Balance frequency array ---
        // 'currentBalance' walks from 0 and can range from -n to +n.
        // We can't use negative indices in a vector, so we shift by +n (the offset trick):
        //   real balance b  →  stored at index  b + n
        // The array size is 2*n+1 to cover all values from -n (index 0) to +n (index 2n).
        // The second argument '0' fills every slot with zero — the vector<T>(size, value) constructor.
        std::vector<int> balanceFreq(2 * n + 1, 0);

        // --- Seed the frequency table with the empty prefix ---
        // Before processing any element, the prefix balance is 0 (no elements seen).
        // That "zero balance" state has occurred once, so we record it.
        // Index: 0 + n = n  (applying the offset).
        balanceFreq[0 + n] = 1;

        int currentBalance = 0;

        // 'long long' here because validSubarraysCount accumulates over n steps
        // and can reach O(n²) in the worst case (e.g. all elements == target).
        long long totalSubarrays = 0;
        long long validSubarraysCount = 0;

        // --- Single pass through the array ---
        for (int i = 0; i < n; ++i) {

            if (nums[i] == target) {
                // --- Balance increases by 1 ---
                // We're about to move from 'currentBalance' to 'currentBalance + 1'.
                // Any past prefix balance equal to 'currentBalance' is now strictly less
                // than our new balance, so those positions yield a valid subarray ending here.
                // We add their frequency BEFORE incrementing (old level becomes valid).
                validSubarraysCount += balanceFreq[currentBalance + n];
                currentBalance += 1;
            } else {
                // --- Balance decreases by 1 ---
                // We're about to move from 'currentBalance' to 'currentBalance - 1'.
                // Any past prefix balance equal to 'currentBalance - 1' was previously
                // strictly less than 'currentBalance', but it is NO LONGER less than
                // our new (lower) balance. We subtract their count before decrementing.
                currentBalance -= 1;
                validSubarraysCount -= balanceFreq[currentBalance + n];
            }

            // 'validSubarraysCount' now holds the number of previous prefix positions
            // with a balance strictly less than 'currentBalance' — i.e., the number of
            // valid subarrays that END at index i.
            totalSubarrays += validSubarraysCount;

            // Record that 'currentBalance' has now been seen one more time.
            // Future iterations will use this to know how many subarrays start here.
            balanceFreq[currentBalance + n]++;
        }

        // --- Complexity summary ---
        // Time:  O(n)      — single pass, all operations inside are O(1).
        // Space: O(n)      — the balanceFreq array of size 2n+1.
        // Compare to the O(n²) / O(1) brute-force version in majoritysubarrays.cpp.
        return totalSubarrays;
    }
};

// --- main ---
// Program entry point. Returns 0 to signal success to the OS.
int main() {
    solution s;

    // Brace-initializer: creates and populates the vector in one expression.
    std::vector<int> nums = {1, 2, 3, 1, 1};
    int target = 1;

    // Call the method and print the result.
    // std::cout streams to stdout; "\n" ends the line (faster than std::endl,
    // which also flushes the output buffer unnecessarily here).
    std::cout << s.countMajoritySubarrays(nums, target) << "\n";
    return 0;
}
