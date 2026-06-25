#include <iostream>
#include <vector>
#include <algorithm>

class solution {
    public:
        std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
            std::vector<std::vector<int>> result;
            int n = nums.size();

            std::sort(nums.begin(), nums.end());

            for (int i = 0; i < n - 2; i++) {
                if (nums[i] > 0) break;
                if (i > 0 && nums[i] == nums[i - 1]) continue;

                int left = i + 1;
                int right = n - 1;

                while (left < right) {
                    int sum = nums[i] + nums[left] + nums[right];

                    if (sum == 0) {
                        result.push_back({nums[i], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    } else if (sum < 0) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }

            return result;
        }
};

int main() {
    solution s;
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto result = s.threeSum(nums);
    for (auto& triplet : result)
        std::cout << "[" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << "]\n";
    return 0;
}
