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
/*********************************/
/*********************************/


void test_ssh(SSH ssh){
    int res = VCALL(ssh, connect, "127.0.0.1", 22, "testuser", 1000);
    printf("ssh connect result = %d\n", res);
}

void main_ssh(){
  SSH ssh_password = DYN_LIT(SshAuthPassword, SSH, {});
  SSH ssh_privatekey = DYN_LIT(SshAuthPrivateKey, SSH, {});
  test_ssh(ssh_password);
  test_ssh(ssh_privatekey);
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
  main_ssh();
  log_info("TEST2 OK");
}

