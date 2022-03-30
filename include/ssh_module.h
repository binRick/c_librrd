#include "interface99/interface99.h"
#include "metalang99/include/metalang99.h"
#include <stdio.h>

#define SSH_IFACE_PING    \
  vfunc(int, ping, VSelf) \

#define SSH_IFACE_CONFIG                                                                 \
  vfunc(int, config, VSelf, char *host, unsigned int port, char *username, char *secret) \

#define SSHCOMMON_IFACE \
  SSH_IFACE_PING        \
    SSH_IFACE_CONFIG    \

#define SSH_IFACE \
  SSHCOMMON_IFACE \

interface(SSH);


int SSH_ping(SshAuth *auth) {
  printf("Pinging host type %s|host:%s:%d\n", auth->type, auth->host, auth->port);
  return(0);
}


int SshAuthPassword_ping(VSelf, SSH ssh){
  VSELF(SshAuthPassword);
  return(SSH_ping(self->auth));
}


int SshAuthPrivateKey_ping(VSelf, SSH ssh){
  VSELF(SshAuthPrivateKey);
  return(SSH_ping(self->auth));
}


void SSH_print_auth(SshAuth *auth){
  char msg[1024];

  log_debug("name:%s", auth->creds->name);
  sprintf(&msg,
          AC_RESETALL AC_YELLOW AC_REVERSED "host: %s|id:%d|type:%s|secret:%s|" AC_RESETALL,
          auth->host,
          auth->id,
          auth->type,
          auth->secret
          );
  log_debug(msg);
}


SshAuth *SSH_get_auth(int id, char *host, unsigned int port, char *username, char *secret){
  SshAuth *auth = malloc(sizeof(SshAuth));

  auth->creds       = malloc(sizeof(SshCredentials));
  auth->creds->name = "xxxxxxxxxxx";
  auth->host        = strdup(host);
  auth->secret      = strdup(secret);
  auth->port        = port;
  auth->id          = id;
  auth->type        = strdup(SSH_AUTH_TYPE_ID_TO_NAME(auth->id));
  switch (auth->id) {
  case SSH_AUTH_PASSWORD:
    auth->creds->name = "password";
    auth->creds->data = "zxzzzzzzzzzzzzzzz";
    break;
  case SSH_AUTH_PRIVATE_KEY:
    auth->creds->name = "private_key";
    auth->creds->data = "yyyyyyyyyyyy";
    break;
  }
  SSH_print_auth(auth);
  return(auth);
}


int SshAuthPrivateKey_config(VSelf, char *host, unsigned int port, char *username, char *secret){
  VSELF(SshAuthPrivateKey);
  printf("config private key\n");
  self->auth = SSH_get_auth(SSH_AUTH_PRIVATE_KEY, host, port, username, secret);
  return(2);
}


int SshAuthPassword_config(VSelf, char *host, unsigned int port, char *username, char *secret){
  VSELF(SshAuthPrivateKey);
  printf("config pass\n");
  self->auth = SSH_get_auth(SSH_AUTH_PASSWORD, host, port, username, secret);
  return(2);
}

impl(SSH, SshAuthPassword);
impl(SSH, SshAuthPrivateKey);

