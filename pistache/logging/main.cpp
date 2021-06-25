#include "Server.hpp"

#include <chrono>
#include <easylogging++.h>
#include <pistache/http.h>

int waitForTermination(Server &server);

using namespace Pistache;
using namespace std;
using namespace std::chrono;

INITIALIZE_EASYLOGGINGPP

void initLogging() {
  el::Helpers::setThreadName("main");
  el::Configurations config;
  config.setGlobally(el::ConfigurationType::Format,
                     "ts=%datetime{%Y-%M-%dT%H:%m:%s.%g} lvl=%level "
                     "thr=%thread src=%fbase msg=%msg");
  el::Loggers::reconfigureLogger("default", config);
}

int main(int argc, char *argv[]) {
  auto start = high_resolution_clock::now();
  initLogging();

  Port port(8084);
  uint threads =
      argc == 2 ? std::min(255, ::stoi(argv[1])) : hardware_concurrency();
  Address addr(Ipv4::any(), port);
  Server server(addr);
  server.init(threads);
  server.start();
  LOG(INFO) << "Started service in "
            << duration_cast<microseconds>(high_resolution_clock::now() - start)
                   .count()
            << "µs";
  LOG(INFO) << "Started using " << threads << " threads";
  return waitForTermination(server);
}

int waitForTermination(Server &server) {
  sigset_t signals;
  sigaddset(&signals, SIGTERM);
  sigaddset(&signals, SIGINT);
  sigaddset(&signals, SIGHUP);
  pthread_sigmask(SIG_BLOCK, &signals, nullptr);
  int signal = 0;
  int status = sigwait(&signals, &signal);
  server.shutdown(signal);
  return status;
}
