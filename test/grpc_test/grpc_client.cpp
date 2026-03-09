#include "grpcpp/grpcpp.h"
#include "echo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using demo::EchoService;
using demo::EchoRequest;
using demo::EchoReply;

int main() {
    std::shared_ptr<Channel> channel =
        grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

    std::unique_ptr<EchoService::Stub> stub = EchoService::NewStub(channel);

    EchoRequest request;
    request.set_message("Hello from client");

    EchoReply reply;
    ClientContext context;
    Status status = stub->Echo(&context, request, &reply);

    if (status.ok()) {
        std::cout << "Reply: " << reply.message() << std::endl;
    } else {
        std::cerr << "RPC failed" << std::endl;
    }
    return 0;
}
