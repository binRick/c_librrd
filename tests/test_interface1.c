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


void test_ssh(SSH ssh, char *secret){
  printf("ssh connect start\n");
  int res  = VCALL(ssh, config, "127.0.0.1", 22, "tu", secret);
  int ping = VCALL(ssh, ping);

  printf("ping result = %d\n", ping);
}


void main_ssh(){
  SSH ssh_password   = DYN_LIT(SshAuthPassword, SSH, { });
  SSH ssh_privatekey = DYN_LIT(SshAuthPrivateKey, SSH, {});

  test_ssh(ssh_password, "xxxxxxxxxx");
  test_ssh(ssh_privatekey, "yyyyyyyyyyyyyy");
}


int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
  main_ssh();
  log_info("TEST2 OK");
}

