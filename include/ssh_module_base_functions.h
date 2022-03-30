#define _POSIX_C_SOURCE    200809L
#include <pthread.h>
#define PATH_MAX           1024 * 1024
#include <arpa/inet.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <features.h>
#include <libssh2.h>
#include <linux/memfd.h>
#include <math.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>
/***************/
#include "interface99/interface99.h"
#include "metalang99/include/metalang99.h"


/*******************************/


//       EXEC                  //


/*******************************/


int SSH_exec(SshAuth *auth, char *cmd) {
  printf("Exec host type %s|host:%s:%d|cmd:%s\n", auth->type, auth->host, auth->port, cmd);
  return(0);
}


/*******************************/


//       CONNECT                  //


/*******************************/
int SSH_sshinit(SshAuth *auth){
    int rc = libssh2_init(0);
  if (rc != 0) {
    log_error("libssh2 initialization failed (%d)", rc);
    return(1);
  log_debug("SSH Initialization OK");
  }
  return 0;
}
int SSH_sshconnect(SshAuth *auth) {
  printf("SSH Connecting host type %s|host:%s:%d\n", auth->type, auth->host, auth->port);
    struct StringBuffer            *sout    = stringbuffer_new_with_options(1024, true);
  LIBSSH2_SESSION                *session = NULL;
  LIBSSH2_CHANNEL                *channel;
  LIBSSH2_AGENT                  *agent = NULL;
  struct libssh2_agent_publickey *identity, *prev_identity = NULL;
       int                            sock;
  struct sockaddr_in             sin;
  const char                     *fingerprint;

  sin.sin_family = AF_INET;
  if (INADDR_NONE == (sin.sin_addr.s_addr = inet_addr(auth->host))) {
    log_error("Invalid remote IP address");
    return(-1);
  }
  sin.sin_port = htons(auth->port);
  /*
  if (connect(sock, (struct sockaddr *)(&sin),
              sizeof(struct sockaddr_in)) != 0) {
    fprintf(stderr, "Failed to connect!\n");
    return(-1);
  }

  sprintf(m, "Connect %s:%d OK", auth->host, auth->port);
  debug(m);
  info("SSH Session Initializing");
  session = libssh2_session_init();
  if (!session) {
    fprintf(stderr, "Could not initialize the SSH session!\n");
    return(-1);
  }
  info("SSH Session OK");

  if (libssh2_session_handshake(session, sock)) {
    fprintf(stderr, "Failure establishing SSH session\n");
    return(1);
  }
  info("SSH Handshake OK");

  fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);
  info("Fingerprint OK");


  userauthlist = libssh2_userauth_list(session, auth->username, strlen(auth->username));
  char sstr[1024 * 1024];

  sprintf(sstr, "%s", userauthlist);
  char **ual  = strsplit(sstr, ",");
  char **ualq = strsplit_count(userauthlist, ",", &userauthlist_qty);

  sprintf(m, "%d Authentication methods: %s", userauthlist_qty, userauthlist);
  debug(m);
  if (strstr(userauthlist, "publickey") == NULL) {
    log_error("\"publickey\" authentication is not supported\n");
    goto shutdown;
  }
  sprintf(m, "SSH Public Key Auth Method for %s OK", auth->username);
  debug(m);
  */
  return(0);
}
int SSH_connect(SshAuth *auth) {
  printf("Connecting host type %s|host:%s:%d\n", auth->type, auth->host, auth->port);
  return(0);
}


/*******************************/


//       PING                  //


/*******************************/
int SSH_ping(SshAuth *auth) {
  printf("Pinging host type %s|host:%s:%d\n", auth->type, auth->host, auth->port);
  return(0);
}


/*******************************/


//       PRINT                  //


/*******************************/
void SSH_print_auth(SshAuth *auth){
  char msg[1024];

  log_debug("name:%s", auth->creds->name);
  sprintf(&msg,
          AC_RESETALL AC_YELLOW AC_REVERSED "host: %s|id:%d|type:%s|secret:%s|ok:%s|" AC_RESETALL,
          auth->host,
          auth->id,
          auth->type,
          auth->secret
          , (auth->ok) ? "Yes" : "No"
          );
  log_debug(msg);
}


/*******************************/


//       GET AUTH CONFIG       //


/*******************************/
SshAuth *SSH_get_auth(int id, char *host, unsigned int port, char *username, char *secret){
  SshAuth *auth = malloc(sizeof(SshAuth));

  auth->ok = false;
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
  auth->ok = (strlen(auth->host)>0 ) ? true : false;
  SSH_print_auth(auth);
  return(auth);
}

