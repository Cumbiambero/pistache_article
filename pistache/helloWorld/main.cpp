#include <pistache/endpoint.h>
using namespace Pistache;

class HelloHandler : public Http::Handler {
public:
  HTTP_PROTOTYPE(HelloHandler)
  void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
    response.send(Http::Code::Ok, "Hello from Pistache");
  }
};
int main() {
  Http::listenAndServe<HelloHandler>(Address (Ipv4::any(), Port(8084)), Http::Endpoint::options());
}