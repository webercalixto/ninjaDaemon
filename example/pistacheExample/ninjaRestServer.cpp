#include "global.hpp"
#include "ninjaRestServer.hpp"
#include <sstream>
#include <string>
#include <fstream>

/*#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>*/

using namespace std;
using namespace Pistache;

ninjaRestServer::ninjaRestServer(Address addr)
    : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
{
}

void ninjaRestServer::init(size_t _numRestServerProcesses, int _maxRestRequestSize)
{
    auto opts = Http::Endpoint::options()
                    .threads(_numRestServerProcesses)
                    .maxRequestSize(_maxRestRequestSize)
                    .flags(Pistache::Tcp::Options::ReuseAddr | Pistache::Tcp::Options::FastOpen);
    httpEndpoint->init(opts);
    this->setRoute();
}

void ninjaRestServer::start()
{
    this->httpEndpoint->setHandler(router.handler());
    this->httpEndpoint->serve();
}

void ninjaRestServer::setRoute()
{
    using namespace Rest;
    Routes::Get(router, "/hello/:argument", Routes::bind(&ninjaRestServer::helloHandler, this));
}

void ninjaRestServer::helloHandler(const Rest::Request &req, Http::ResponseWriter writer)
{
    auto        argument = req.param(":argument").as<std::string>();
    std::string response = " HI! You have sent |" + argument + "| as argument";
    /*writer.headers().add<Pistache::Header::Server>("pistache/0.1").add<Pistache::Header::ContentType>(MIME(Text,
    Plain)); writer.cookies().add(Pistache::Http::Cookie("lang", "en-US"));*/
    writer.send(Http::Code::Ok, response);
}
