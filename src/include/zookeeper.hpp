#pragma once

#include <semaphore.h>
#include <string>
#include <zookeeper/zookeeper.h>

class ZooKeeper {
public:
  ZooKeeper();
  ~ZooKeeper();
  void Start();
  void Create(const char *path, const char *data, int datalen, int state = 0);
  std::string GetData(const char *path);

private:
  zhandle_t *_zkhandle;
};