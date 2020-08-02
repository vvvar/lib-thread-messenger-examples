#include <lib-thread-messenger/ThreadMessenger.hpp>

using Messenger = messenger::Messenger;
using MessageData = messenger::MessageData;

class UserData : public MessageData
{
public:
  using UserName = std::string;
  
  UserData(UserName user_name):
    MessageData(),
    _user_name(user_name)
  {}
  
  UserName getUserName()
  {
    return _user_name;
  }
private:
  UserName _user_name;
};

void Worker_1(std::shared_ptr<Messenger> messenger_ptr)
{
  messenger_ptr->registerChannel("worker_1");
  messenger_ptr->waitForMessageInChannel("worker_1");
  auto user_data_ptr = messenger_ptr->receive<UserData>("worker_1");
  std::cout << "Worker 1 got user data: " << user_data_ptr->getUserName() << ".\n";
}

void Worker_2(std::shared_ptr<Messenger> messenger_ptr)
{
  while(true) {
    std::cout << "Enter your name: ";
    std::string input;
    std::getline (std::cin, input);
    std::cin.clear();
    auto user_data_ptr = std::make_shared<UserData>(input);
    messenger_ptr->send<UserData>("worker_1", user_data_ptr);
  }
}

int main()
{
  auto messenger_ptr = libthreadmessenger::MakeMessenger();
  
  std::thread t1(Worker_1, messenger_ptr);
  std::thread t2(Worker_2, messenger_ptr);
  
  t2.detach();
  t1.join();
  
  return 0;
}
