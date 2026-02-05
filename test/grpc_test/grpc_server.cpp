#include <grpcpp/grpcpp.h>
#include "echo.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using demo::EchoService;
using demo::EchoRequest;
using demo::EchoReply;

class EchoServiceImpl final : public EchoService::Service {
    Status Echo(ServerContext* context, const EchoRequest* request,
                EchoReply* reply) override {
        reply->set_message("Server received: " + request->message());
        return Status::OK;
    }
};

int main() {
    std::string server_address("0.0.0.0:50051");
    EchoServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}
