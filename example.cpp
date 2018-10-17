#include "tpool/tpool.hpp"

#include <iostream>

auto main() -> int {
  // construct a default thread pool object
  tpool::thread_pool_safe pool{};
  // or you can go with the faster tpool::thread_pool_std, depending on the case of your program, 
  // whether it needs to use a thread-safe queue implementation or is fine with a std::queue

  // variables to be used in the functions passed to the pool
  constexpr auto num1 = 12.25f;
  constexpr auto num2 = 17.75f;
  
  // enqueue lambdas to the pool which will give them a thread if there's any unused threads left
  // there sure are enough, unless you're running on a single-core CPU, where 
  // a default pool construction might create a pool of only 1 thread
  auto func1 = pool.enqueue([num1] { return num1; });
  auto func2 = pool.enqueue([num2] { return num2; });
  
  // the return values from the enqueued lambdas are futures, thus use std::future::get() to retrieve them
  std::cout << "Result: " << func1.get() + func2.get() << std::endl;

  return 0;
}
