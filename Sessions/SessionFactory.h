#pragma once
#include <boost/di.hpp>
#include "ISessionFactory.h"
#include "Session.h"
#include "../Middleware/IRequestHandler.h"
#include "../RouteRegistrar/Router.h"

struct primary_router_tag {};
struct replica_handler_tag {};

class SessionFactory:public ISessionFactory{
    IRequestHandler& m_requesthandler;
public:
    //BOOST_DI_INJECT(SessionFactory, (named = replica_handler_tag{}) IRequestHandler& router)
    //    :m_requesthandler(router)
    //{}
    explicit SessionFactory(IRequestHandler& router);
    std::shared_ptr<Session> Create(tcp::socket&& socket)override;
};