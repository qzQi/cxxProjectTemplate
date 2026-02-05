#include <iostream>
#include "./proto/test.pb.h"

using namespace std;
using namespace tutorial;

int main()
{
    tutorial::TestMessage message;
    message.set_text("this is a test text");
    message.set_number(1);

    // 序列化
    std::string data;
    message.SerializeToString(&data);
    std::cout<<"serialized size ="<< data.size() <<" bytes;\n";
    std::cout<<"serialized content ="<< data <<"\n";

    // 反序列化
    tutorial::TestMessage message2;
    message2.ParseFromString(data);
    std::cout<<"text "<<message2.text()<<endl;
    std::cout<<"num "<<message2.number()<<endl;

    // rpc method
}