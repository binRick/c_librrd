#include "interface99/interface99.h"
#include "metalang99/include/metalang99.h"
#include <stdio.h>


int SshAuthPassword_sshinit(VSelf){
  VSELF(SshAuthPassword);
  return(SSH_sshinit(self->auth));
}


int SshAuthPrivateKey_sshinit(VSelf){
  VSELF(SshAuthPrivateKey);
  return(SSH_sshinit(self->auth));
}


int SshAuthPassword_exec(VSelf, char *cmd){
  VSELF(SshAuthPassword);
  return(SSH_exec(self->auth, cmd));
}


int SshAuthPrivateKey_exec(VSelf, char *cmd){
  VSELF(SshAuthPrivateKey);
  return(SSH_exec(self->auth, cmd));
}


int SshAuthPassword_connect(VSelf){
  VSELF(SshAuthPassword);
  return(SSH_sshconnect(self->auth));
}


int SshAuthPrivateKey_connect(VSelf){
  VSELF(SshAuthPrivateKey);
  return(SSH_sshconnect(self->auth));
}


int SshAuthPassword_ping(VSelf){
  VSELF(SshAuthPassword);
  return(SSH_ping(self->auth));
}


int SshAuthPrivateKey_ping(VSelf){
  VSELF(SshAuthPrivateKey);
  return(SSH_ping(self->auth));
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
