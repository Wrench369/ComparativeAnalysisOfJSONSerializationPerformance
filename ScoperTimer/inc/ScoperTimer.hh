#include <chrono>
#include <iostream>

class Timer {
 public:
  Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

  void Reset() { start_time_ = std::chrono::high_resolution_clock::now(); }

  double Elapsed() const {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        end_time - start_time_);
    return duration.count() / 1000000.0;  // 返回秒数
  }

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
};