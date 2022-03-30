#include "interface99/interface99.h"
#include "metalang99/include/metalang99.h"
#include <stdio.h>

enum {
  SSH_AUTH_PASSWORD = 0,
  SSH_AUTH_PRIVATE_KEY,
}    SSH_AUTH_TYPE_IDS;

char *SSH_AUTH_TYPES[] = {
  "password",
  "private_key",
  NULL,
};
#define SSH_AUTH_TYPE_ID_TO_NAME(SSH_AUTH_TYPE_ID) \
  SSH_AUTH_TYPES[SSH_AUTH_TYPE_ID]                 \

typedef struct {
  int          id;
  char         *Type;
  char         *host;
  unsigned int port;
  char         *username;
  int          timeout_ms;
} SshAuth;

typedef struct {
  char    *privatekey;
  SshAuth *auth;
} SshAuthPrivateKey;

typedef struct {
  char    *password;
  SshAuth *auth;
} SshAuthPassword;

#define SSH_IFACE                                                                           \
  vfunc(int, connect, VSelf, char *host, unsigned int port, char *username, int timeout_ms) \
  vfunc(int, ping, SSH ssh)                                                                 \

interface(SSH);


void SSH_ping(SshAuth *auth) {
  printf("Pinging host type %s\n", auth->Type);
}


int SshAuthPassword_ping(SSH ssh){
  printf("Password ping host........\n");
}


int SshAuthPrivateKey_ping(SSH ssh){
  printf("Privatekey ping host........\n");
}


void SSH_print_auth(SshAuth *auth){
  char msg[1024];

  sprintf(&msg, "host: %s|id:%d|Type:%s|", auth->host, auth->id, auth->Type);
  log_debug(msg);
}


SshAuth *SSH_get_auth(int id, char *host, unsigned int port, char *username, int timeout_ms){
  SshAuth *auth = malloc(sizeof(SshAuth));

  auth->host       = strdup(host);
  auth->port       = port;
  auth->id         = id;
  auth->Type       = strdup(SSH_AUTH_TYPE_ID_TO_NAME(auth->id));
  auth->timeout_ms = timeout_ms;
  SSH_print_auth(auth);
  SSH_ping(auth);
  return(auth);
}


int SshAuthPrivateKey_connect(VSelf, char *host, unsigned int port, char *username, int timeout_ms){
  VSELF(SshAuthPrivateKey);
  printf("connect private key\n");
  self->auth = SSH_get_auth(SSH_AUTH_PRIVATE_KEY, host, port, username, timeout_ms);
  return(2);
}


int SshAuthPassword_connect(VSelf, char *host, unsigned int port, char *username, int timeout_ms){
  VSELF(SshAuthPassword);
  printf("connect pass\n");
  self->auth = SSH_get_auth(SSH_AUTH_PASSWORD, host, port, username, timeout_ms);
  return(3);
}

impl(SSH, SshAuthPassword);
impl(SSH, SshAuthPrivateKey);

