#include "SieveOfAtkin.hpp"

#include <iostream>
#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <pistache/thirdparty/serializer/rapidjson.h>

using namespace std;
using namespace Pistache;
using namespace std::chrono;
using namespace rapidjson;

class Server {
public:
  Server(Address addr, time_point<system_clock> timer)
      : httpEndpoint(addr), description("Demo API", "0.1"), timer(timer) {}

  void init(size_t thr = 2) {
    auto opts = Http::Endpoint::options().threads(static_cast<int>(thr));
    httpEndpoint.init(opts);
    createDescription();
  }

  void start() {
    router.initFromDescription(description);
    httpEndpoint.setHandler(router.handler());
    auto finish = high_resolution_clock::now();
    cout << "Started service in "
         << duration_cast<milliseconds>(finish - timer).count() << "ms" << endl;
    httpEndpoint.serve();
  }

  void shutdown(int signum) { httpEndpoint.shutdown(); }

private:
  Http::Endpoint httpEndpoint;
  Rest::Description description;
  Rest::Router router;
  time_point<system_clock> timer;

  void createDescription() {
    description.route(description.get("/"))
        .bind(&Server::hello, this)
        .produces(MIME(Text, Plain))
        .response(Http::Code::Ok, "HelloWorld!");

    description.route(description.get("/primes"), "Calculate primes")
        .bind(&Server::primes, this)
        .produces(MIME(Application, Json))
        .parameter<Rest::Type::Integer>("limit", "Limit of the calcuation")
        .response(Http::Code::Ok, "Total and list of primes");
  }

  void hello(const Rest::Request &request, Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "Hello from Pistache");
  }

  void primes(const Rest::Request &request, Http::ResponseWriter response) {
    u_int32_t limit =
        atoi(request.query().get("limit").value_or("100").c_str());
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    auto primes = SieveOfAtkin::calculate(limit);
    writer.StartObject();
    writer.Key("count");
    writer.Uint(primes.size());
    writer.Key("primes");
    writer.StartArray();
    for (auto prime : primes) {
      writer.Uint(prime);
    }
    writer.EndArray();
    writer.EndObject();
    writer.IsComplete();
    response.setMime(MIME(Application, Json));
    response.send(Http::Code::Ok, buffer.GetString());
  }
};