#include "stdint.h"
#include <algorithm>
#include <mutex>
#include <vector>

using namespace std;

class SieveOfAtkin {
public:
  static vector<uint32_t> calculate(uint32_t limit) {
    bool *sieve = createSieve(limit);
    std::vector<uint32_t> result = extractNumbers(limit, sieve);
    delete[] sieve;
    return result;
  }

private:
  static bool *createSieve(uint32_t limit) {
    bool *sieve = new bool[max(uint32_t(4), limit + 1)];
    for (uint32_t i = 0; i < limit; i++) {
      sieve[i] = false;
    }
    sieve[2] = true;
    sieve[3] = true;

    for (uint32_t x = 1, xSquare; xSquare = x * x, xSquare < limit; ++x) {
      for (uint32_t y = 1, ySquare; ySquare = y * y, ySquare < limit; ++y) {
        uint32_t n = (xSquare << 2) + ySquare;
        if (n <= limit && (n % 12 == 1 || n % 12 == 5)) {
          sieve[n] ^= true;
        }

        n = 3 * xSquare + ySquare;
        if (n <= limit && n % 12 == 7) {
          sieve[n] ^= true;
        }

        n = 3 * xSquare - ySquare;
        if (x > y && n <= limit && n % 12 == 11) {
          sieve[n] ^= true;
        }
      }
    }

    for (uint32_t r = 5, rSquare; rSquare = r * r, rSquare < limit; ++r) {
      if (sieve[r]) {
        for (uint32_t i = rSquare; i < limit; i += rSquare) {
          sieve[i] = false;
        }
      }
    }
    return sieve;
  }

  static vector<uint32_t> extractNumbers(uint32_t limit, bool *sieve) {
    vector<uint32_t> result;
    for (uint32_t a = 2; a < limit; a++) {
      if (sieve[a]) {
        result.push_back(a);
      }
    }
    return result;
  }
};