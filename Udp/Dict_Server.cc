#include "Udp_Server.hpp"
#include<unordered_map>
#include<iostream>
#include<stdlib.h>


unordered_map<string,string> Dict;

void Translate(const string& req,string* res)
{
  auto it = Dict.find(req);
  if(it == Dict.end())
  {
    *res = "未查到";
    return ;
  }
  *res = it->second;
}


int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    printf("Usage./Dict_Server[ip] [port]\n");
    return 1;
  }

  //数据初始化
  Dict.insert(make_pair("hehe","呵呵"));
  Dict.insert(make_pair("cardiac","心脏"));

  //启动服务器
  UdpServer server;
  string ip(argv[1]);
  server.Start(ip,atoi(argv[2]),Translate);
  return 0;
}
