#include <lib-thread-messenger/ThreadMessenger.hpp>

using Messenger = messenger::Messenger;
using MessageData = message::MessageData;

class UserData: public MessageData
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

void Worker_Thread(std::shared_ptr<Messenger> messenger_ptr)
{
  messenger_ptr->waitForMessageInChannel("worker");
  auto user_data_ptr = messenger_ptr->receive<UserData>("worker");
  std::cout << "Worker got user data: " << user_data_ptr->getUserName() << ".\n";
}

void UI_Thread(std::shared_ptr<Messenger> messenger_ptr)
{
  std::cout << "Enter your name: ";
  std::string input;
  std::getline (std::cin, input);
  std::cin.clear();
  auto user_data_ptr = std::make_shared<UserData>(input);
  messenger_ptr->send<UserData>("worker", user_data_ptr);
}

int main()
{
  auto messenger_ptr = libthreadmessenger::MakeMessenger();
  
  messenger_ptr->registerChannel("worker");
  
  std::thread t1(Worker_Thread, messenger_ptr);
  std::thread t2(UI_Thread, messenger_ptr);

  t2.detach();
  t1.join();
  
  return 0;
}
