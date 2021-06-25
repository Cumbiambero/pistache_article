#include "SieveOfAtkin.hpp"

#include <easylogging++.h>
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
  Server(Address addr) : httpEndpoint(addr), description("Demo API", "0.1") {}

  void init(uint threads) {
    auto opts = Http::Endpoint::options()
                    .threads(static_cast<int>(threads))
                    .threadsName("server");
    httpEndpoint.init(opts);
    createDescription();
  }

  void shutdown(int signal) {
    LOG(INFO) << "Shutting down with signal " << signal;
    httpEndpoint.shutdown();
  }

  void start() {
    router.initFromDescription(description);
    httpEndpoint.setHandler(router.handler());
    httpEndpoint.serveThreaded();
  }

private:
  Http::Endpoint httpEndpoint;
  Rest::Description description;
  Rest::Router router;

  void createDescription() {
    description.route(description.get("/"))
        .bind(&Server::hello)
        .produces(MIME(Text, Plain))
        .response(Http::Code::Ok, "HelloWorld!");

    description.route(description.get("/primes"), "Calculate primes")
        .bind(&Server::primes)
        .produces(MIME(Application, Json))
        .parameter<Rest::Type::Integer>("limit", "Limit of the calculation")
        .response(Http::Code::Ok, "Total and list of primes");
  }

  static void hello([[maybe_unused]] const Rest::Request &request,
                    Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "Hello from Pistache");
    LOG(INFO) << "Processed / request";
  }

  static void primes(const Rest::Request &request,
                     Http::ResponseWriter response) {
    u_int32_t limit = strtol(
        request.query().get("limit").value_or("100").c_str(), nullptr, 10);
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
    LOG(INFO) << "Processed /primes request";
  }
};