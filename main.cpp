#define BOOST_DI_CFG_DIAGNOSTICS_LEVEL 10
#define BOOST_DI_CFG_CTOR_LIMIT_SIZE 20
#pragma comment(lib, "pqxx.lib")

#include <boost/core/ignore_unused.hpp>
#include <boost/di.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <stdexcept>

#include "Modules/HttpModule.h"

// namespace di = boost::di;
// namespace net = boost::asio;


int main(int argc, char const* argv[]) {
    boost::ignore_unused(argc);
    boost::ignore_unused(argv);

    try {
        std::cout << "[INIT] Starting system initialization...\n";

        net::io_context ioc;
        auto injector = di::make_injector(
            di::bind<net::io_context>().to(ioc),          
            di::bind<unsigned short>().named<ServerPort>().to(static_cast<unsigned short>(5600)),  
            di::bind<unsigned short>().named<WSPort>().to(static_cast<unsigned short>(5601)),
            di::bind<unsigned short>().named<port>().to(static_cast<unsigned short>(5432)),
            di::bind<std::size_t>().named<POOLSIZE>().to(static_cast<std::size_t>(8)),
            di::bind<std::string>().named<host>().to("localhost"),
            di::bind<std::string>().named<database>().to("riskdb"),
            di::bind<std::string>().named<user>().to("postgres"),
            di::bind<std::string>().named<password>().to("1Qazwsxedc@"),
            HttpModule(),
            CommonModdule(),
            MarketModule(),
            WebsocketModule(),
            DbModule(),
            TradeModule(),
            ValidatorModdule(),
            AppModule()
        );
        //auto&  app= injector.create<IApplicationStartup&>();
        //app.Run();
        //std::cin.get();
        //app.stop();

        
        auto& app = injector.create<Application&>();
        std::cout << "[INIT] System initialized successfully\n";
         net::signal_set signals(ioc, SIGINT, SIGTERM);
         signals.async_wait([&app](const boost::system::error_code& ec, int signal_number) {
             if (!ec) {
                 std::cout << "[SIGNAL] Received signal (" << signal_number << "). Shutting down...\n";
                 app.stop();
             } else if (ec != net::error::operation_aborted) {
                 std::cerr << "[ERROR] Signal handling error: " << ec.message() << "\n";
             }
         });
         app.Run();

        std::cout << "[SHUTDOWN] Shutdown complete.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[FATAL] " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "[FATAL] Unknown error occurred\n";
        return 1;
    }
}
