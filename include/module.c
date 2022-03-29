#include "./module.h"

module(internal) {
  define(internal, CLIB_MODULE);
  char *value;
};

exports(internal) {
  defaults(internal, CLIB_MODULE_DEFAULT),
  .value = 0,
};


static inline void *get() {
  return(require(internal)->value);
}


static inline void set(void *val) {
  require(internal)->value = val;
}


static inline void deinit(module(rrd) *exports) {
  printf("deinit module(rrd)\n");
  clib_module_free(require(internal));
  clib_module_deinit(internal);
}


static int init(module(rrd) *exports) {
  clib_module_init(rrd, exports);
  exports->deinit = deinit;
  exports->set    = set;
  exports->get    = get;
  return(0);
}


int rrd(module(rrd) *exports) {
  return(init(exports));
}
