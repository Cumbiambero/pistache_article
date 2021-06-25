#include "Server.hpp"

#include <chrono>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <signal.h>

using namespace Pistache;
using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
  auto start = high_resolution_clock::now();
  Port port(8084);

  int threads = argc == 2 ? std::min(255,::stoi(argv[1])): hardware_concurrency();
  Address addr(Ipv4::any(), port);
  cout << "Using " << threads << " threads" << endl;
  Server server(addr, start);
  server.init(threads);  
  server.start();
}
