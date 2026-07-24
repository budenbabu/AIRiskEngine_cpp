#include "SessionFactory.h"

SessionFactory::SessionFactory(IRequestHandler &router):m_requesthandler(router)
{
}

std::shared_ptr<Session> SessionFactory::Create(tcp::socket&& socket)
{
    return std::make_shared<Session>(std::move(socket),m_requesthandler);
}
