#include "zookeeper.hpp"
#include "log.hpp"
#include "mprpcapplication.hpp"
#include <cstdlib>
#include <semaphore.h>
#include <zookeeper/proto.h>
#include <zookeeper/zookeeper.h>

void watcher(zhandle_t *zh, int type, int state, const char *path,
             void *watcherCtx) {
  // Do nothing
  if (type == ZOO_SESSION_EVENT) {
    if (state == ZOO_CONNECTED_STATE) {
      sem_t *sem = (sem_t *)zoo_get_context(zh);
      sem_post(sem);
    }
  }
}

ZooKeeper::ZooKeeper() : _zkhandle(nullptr) {}

ZooKeeper::~ZooKeeper() {
  if (_zkhandle != nullptr)
    zookeeper_close(_zkhandle);
}

void ZooKeeper::Start() {
  std::string ip = MprpcApplication::getInstance().GetConfig().zookeeperIP;
  int port = MprpcApplication::getInstance().GetConfig().zookeeperPort;
  std::string connstr = ip + ":" + std::to_string(port);

  _zkhandle =
      zookeeper_init(connstr.c_str(), watcher, 30000, nullptr, nullptr, 0);

  if (_zkhandle == nullptr) {
    LOG_ERROR("zookeeper_init error");
    exit(EXIT_FAILURE);
  }

  sem_t sem;
  sem_init(&sem, 0, 0);
  zoo_set_context(_zkhandle, &sem);
  // later, we can access it by using zoo_get_context(zh)
  sem_wait(&sem);
  LOG_INFO("zookeeper_init success");
}

void ZooKeeper::Create(const char *path, const char *data, int datalen,
                       int mode) {
  char path_buffer[128];
  int bufferlen = sizeof(path_buffer);
  int flag;

  /* check if a node already exists
     @param zh(the context of connection);
     @path the name of the node;
     @watcher whether register a watcher;
     @completiion, the callback function;
     @data, the data to be passed to the callback function;
  */
  flag = zoo_exists(_zkhandle, path, 0, nullptr);
  if (ZNONODE == flag) {
    // if the node doesn't exist
    flag = zoo_create(_zkhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE,
                      mode, path_buffer, bufferlen);
    if (flag == ZOK) {
      LOG_INFO("ZNODE CREATE SUCCESS...path: {}", path_buffer);
    } else {
      LOG_ERROR("FLAG: {}", flag);
      LOG_ERROR("ZNODE CREATE ERROR...path: {}", path_buffer);
      exit(EXIT_FAILURE);
    }
  } else {
    LOG_ERROR("...ZNODE EXISTS...path: {}", path_buffer);
  }
}

std::string ZooKeeper::GetData(const char *path) {
  char data[64];
  int datalen = sizeof(data);
  int flag = zoo_get(_zkhandle, path, 0, data, &datalen, nullptr);

  if (ZOK != flag) {
    LOG_ERROR("GET ZNODE ERROR...PATH:{}", path);
    return nullptr;
  }
  LOG_INFO("GET ZNODE SUCCESS...PATH:{}, DATA:{}", path, data);
  return std::string(data);
}