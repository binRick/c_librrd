#include "interface99/interface99.h"
#include "metalang99/include/metalang99.h"
#include <stdio.h>

#define SSH_IFACE_EXEC \
  vfunc(int, exec, const VSelf, char *cmd)

#define SSH_IFACE_CONNECT \
  vfunc(int, connect, VSelf)

#define SSH_IFACE_PING    \
  vfunc(int, ping, VSelf) \

#define SSH_IFACE_SSHINIT \
  vfunc(int, sshinit, VSelf)

#define SSH_IFACE_CONFIG                                                                 \
  vfunc(int, config, VSelf, char *host, unsigned int port, char *username, char *secret) \

#define SSHCOMMON_IFACE \
  SSH_IFACE_CONFIG      \
  SSH_IFACE_PING        \
  SSH_IFACE_CONNECT     \
  SSH_IFACE_EXEC        \
    SSH_IFACE_SSHINIT   \

#define SSH_IFACE \
  SSHCOMMON_IFACE \

interface(SSH);
