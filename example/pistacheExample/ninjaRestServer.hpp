/*
 * The MIT License
 *
 * Copyright 2019 weber Calixto.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * File:   ninjaRestServer.hpp
 * Author: weber Calixto
 *
 * Created on September 8, 2019, 10:17 AM
 */

#ifndef NINJARESTSERVER_HPP
#define NINJARESTSERVER_HPP
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
class ninjaRestServer
{
    private:
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router                    router;
    void helloHandler(const Pistache::Rest::Request &req, Pistache::Http::ResponseWriter writer);
    void setRoute();

    public:
    ninjaRestServer(Pistache::Address addr);
    void init(size_t _numRestServerProcesses, int _maxRestRequestSize);
    void start();
};

#endif /* NINJARESTSERVER_HPP */
