/**
 * @file promise.cpp
 * @author Ben Berg (bsb20)
 * @brief Tutorial code for C++ STL promise and future.
 */

// This program shows a small example of the usage of std::promise. The
// std::promise class provides a way for a thread to store a value (or an
// exception) that another thread can retrieve later, without any manual
// locking or condition variables. It is a one-shot communication channel:
// one thread produces a value, and one thread consumes it.

// Each std::promise object is paired with a std::future object. The producer
// thread holds the promise and calls set_value to store a result. The consumer
// thread holds the future and calls get to retrieve that result. If the result
// is not ready yet, the get call blocks until the producer sets the value.

// To make the blocking behavior obvious, the producer thread in this example
// does not compute something instantly. Instead it waits for an external file
// to appear on disk, then reports how many bytes that file contains. This lets
// you control when the producer finishes from outside the program: while the
// program is running, create the file in another terminal, e.g.
//   echo "hello promise" > /tmp/promise_signal.txt
// Until you do, the main thread stays blocked inside future::get().

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the future library header, which contains both std::promise and
// std::future.
#include <future>
// Includes std::this_thread::sleep_for, used to poll without busy-spinning.
#include <thread>
// Includes std::chrono literals for the polling interval.
#include <chrono>
// Includes the filesystem library, used to check for and measure the file.
#include <filesystem>

// The path the producer thread waits for. Create this file externally to
// unblock the program.
const std::filesystem::path kSignalFile = "/tmp/promise_signal.txt";

// This function is run by the producer thread. It takes a std::promise object
// by value (the promise is moved into this function, since a promise is
// moveable but not copyable). It then does some blocking work: it polls the
// filesystem once per second until kSignalFile exists. Once the file appears,
// it stores the file's size in the promise, making that value available to
// whoever holds the paired future.
void wait_for_file(std::promise<uintmax_t> result_promise) {
  std::cout << "Producer: waiting for " << kSignalFile << " to appear..."
            << std::endl;

  // Poll the filesystem until the file exists. Sleeping between checks avoids
  // burning CPU in a tight busy-loop.
  while (!std::filesystem::exists(kSignalFile)) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // The file now exists, so we can measure it and hand the result back.
  uintmax_t size = std::filesystem::file_size(kSignalFile);

  // set_value stores the result. The main thread, blocked in get(), will now
  // wake up and receive this value.
  result_promise.set_value(size);
}

// The main method creates a promise, extracts its paired future, and then
// launches a producer thread that fills in the promise once the signal file
// appears. The main thread then calls get on the future, which blocks until
// the producer thread has called set_value. Once the value is ready, get
// returns it and we print it.
int main() {
  // Construct a promise that will eventually hold the file's size.
  std::promise<uintmax_t> result_promise;

  // Retrieve the future associated with this promise. get_future may only be
  // called once per promise. This future is how the main thread will read the
  // value the producer thread produces.
  std::future<uintmax_t> result_future = result_promise.get_future();

  // Launch the producer thread. We use std::move to transfer ownership of the
  // promise into the thread, since a promise cannot be copied.
  std::thread producer(wait_for_file, std::move(result_promise));

  while(result_future.wait_for(std::chrono::milliseconds(500)) != std::future_status::ready){
    std::cout << "Main: blocked in get() until the producer sets a value..."
            << std::endl;
  }

  // get() blocks until the producer thread calls set_value on the promise.
  // Since the producer waits for an external file, this call will not return
  // until you create that file. Note that get() may only be called once per
  // future.
  uintmax_t result = result_future.get();

  std::cout << "Main: file is " << result << " bytes." << std::endl;

  // Join the producer thread before exiting.
  producer.join();
  return 0;
}
