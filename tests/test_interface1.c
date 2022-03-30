#include <stdio.h>
#include <stdlib.h>
/*********************************/
#include "metalang99/include/metalang99.h"
/*********************************/
#include "interface99/interface99.h"
/*********************************/
#include "log/log.c"
/*********************************/
#include "include/rrd.h"
/*********************************/


void test_ssh(SSH ssh, char *secret, char *cmd){
  printf("ssh connect start\n");
  int res  = VCALL(ssh, config, "127.0.0.1", 22, "tu", secret);
  int ping = VCALL(ssh, ping);

  printf("ping result = %d\n", ping);
  int connect = VCALL(ssh, connect);
  int e       = VCALL(ssh, exec, cmd);
  int i       = VCALL(ssh, sshinit);
}


void main_ssh(){
  SSH  ssh_password   = DYN_LIT(SshAuthPassword, SSH, { });
  SSH  ssh_privatekey = DYN_LIT(SshAuthPrivateKey, SSH, {});
  char *cmd           = "hostname";

  test_ssh(ssh_password, "xxxxxxxxxx", cmd);
  test_ssh(ssh_privatekey, "yyyyyyyyyyyyyy", cmd);
}


int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
  main_ssh();
  log_info("TEST2 OK");
}

