#include <stdio.h>
#include <stdlib.h>
/*********************************/
#include "log/log.c"
/*********************************/
/*********************************/
/*********************************/


int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
  t1();
  log_debug("argc:%d", argc);
  log_info("TEST2 OK");
}
