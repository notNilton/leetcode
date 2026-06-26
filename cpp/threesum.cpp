// --- Headers ---
// <iostream> gives us std::cout for printing.
// <vector>    gives us std::vector, a dynamic array.
// <algorithm> gives us std::sort, which we need to sort the array in-place.
#include <iostream>
#include <vector>
#include <algorithm>

// --- Class ---
// Groups the solution method. 'public:' makes it callable from main().
class solution {
    public:
        // --- Function signature ---
        // Returns a vector of vectors: each inner vector is one valid triplet.
        // 'nums' is passed by reference (&) — std::sort will modify it in-place,
        // and we avoid an unnecessary copy of potentially large input.
        std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
            std::vector<std::vector<int>> result;
            int n = nums.size();

            // --- Why sort first? ---
            // Sorting enables the two-pointer technique: once the array is ordered,
            // moving 'left' right increases the sum, moving 'right' left decreases it.
            // Without sorting we'd need O(n³) brute force; sorting gives us O(n²).
            // std::sort uses introsort (quicksort + heapsort hybrid) — O(n log n).
            // .begin() and .end() are iterators: pointers to the first and one-past-last elements.
            std::sort(nums.begin(), nums.end());

            // --- Outer loop: fix the first element of the triplet ---
            // We iterate 'i' up to n-2 because we need at least two more elements
            // (left and right) to form a triplet.
            for (int i = 0; i < n - 2; i++) {

                // --- Early exit: all remaining sums are positive ---
                // Array is sorted, so if nums[i] > 0, then nums[left] and nums[right]
                // are also > 0. Their sum can never be 0 — no point continuing.
                if (nums[i] > 0) break;

                // --- Skip duplicate values of 'i' ---
                // If nums[i] == nums[i-1], we already found all triplets starting
                // with this value on the previous iteration. Skipping avoids duplicates
                // in the result without needing a hash set.
                // The guard 'i > 0' prevents reading nums[-1] on the first iteration.
                if (i > 0 && nums[i] == nums[i - 1]) continue;

                // --- Two-pointer setup ---
                // 'left' starts just after 'i'; 'right' starts at the far end.
                // Together with nums[i] they form a candidate triplet.
                int left = i + 1;
                int right = n - 1;

                // The two pointers converge toward each other.
                // Once they meet, all pairs for this 'i' have been checked.
                while (left < right) {
                    int sum = nums[i] + nums[left] + nums[right];

                    if (sum == 0) {
                        // --- Valid triplet found ---
                        // .push_back() appends to the result vector.
                        // The brace initializer {a, b, c} constructs a temporary vector.
                        result.push_back({nums[i], nums[left], nums[right]});

                        // --- Skip duplicates for left pointer ---
                        // Advance 'left' past any repeated values so we don't emit
                        // the same triplet again. The bound check 'left < right'
                        // prevents left from overshooting right.
                        while (left < right && nums[left] == nums[left + 1]) left++;

                        // --- Skip duplicates for right pointer ---
                        // Same idea: move 'right' past repeated values on the right side.
                        while (left < right && nums[right] == nums[right - 1]) right--;

                        // Move both pointers inward to search for the next unique triplet.
                        left++;
                        right--;

                    } else if (sum < 0) {
                        // Sum is too small — we need a larger value.
                        // Moving 'left' right picks a bigger number (array is sorted).
                        left++;
                    } else {
                        // Sum is too large — we need a smaller value.
                        // Moving 'right' left picks a smaller number.
                        right--;
                    }
                }
            }

            return result;
        }
};

// --- main ---
// Program entry point. Returns 0 to signal success to the OS.
int main() {
    solution s;

    // Brace-initializer creates and fills the vector in one line.
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};

    // 'auto' lets the compiler deduce the type (std::vector<std::vector<int>>)
    // so we don't have to write it out explicitly.
    auto result = s.threeSum(nums);

    // Range-based for loop: 'triplet' takes each inner vector in turn.
    // 'auto&' is a const reference — no copy, read-only access.
    for (auto& triplet : result)
        std::cout << "[" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << "]\n";

    return 0;
}
