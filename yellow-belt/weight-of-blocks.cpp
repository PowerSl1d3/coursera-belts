#include <iostream>

int main(void) {

  size_t N;
  unsigned R;
  uint64_t W, H, D, weight_sum = 0;

  std::cin >> N >> R;

  for (size_t i = 0; i < N; i++) {
    std::cin >> W >> H >> D;
    weight_sum += W * H * D * R;
  }

  std::cout << weight_sum << std::endl;

  return 0;
}
