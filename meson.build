
project(
    'c_librrd', ['c'],
    version : '0.0.1',
    default_options : [
      'c_std=gnu99',
      'warning_level=2',
    ],
)

host_system = host_machine.system()

cc = meson.get_compiler('c')

pkg = import('pkgconfig')

libssh2 = dependency('libssh2', required : true)
openssl = dependency('openssl', required : true)
threads = dependency('threads', required : true)

sh = find_program('sh', required : true)
rrdtool = find_program('rrdtool', required : true)

add_global_arguments(
  '-lpthread', 
  '-luv', 
  '-lcurl', 
  '-lrvfs', 
  language : 'c',
)

incdir = include_directories(
  'include', 
  '../',
  '../metalang99/include',
  '/usr/lib64',
  '/usr/local/include',
  '/usr/local/lib64',
)

#//***********************************************************/
test1 = executable('test1', 
  [
    'tests/test1.c', 
    'src/rrd.c', 
  ],
  include_directories : [incdir],
  dependencies : [],
)
test2 = executable('test2', 
  [
    'tests/test2.c', 
    'src/rrd.c', 
  ],
  include_directories : [incdir],
  dependencies : [],
)
test_interface1 = executable('test_interface1', 
  [
    'include/rrd.h', 
    'include/ssh.h', 
    'src/rrd.c', 
    'src/ssh.c', 
    'tests/test_interface1.c', 
  ],
  include_directories : [incdir],
  dependencies : [libssh2, openssl],
)


test_bins = [
  'test1', 
  'test2', 
  'test_interface1', 
]

#//***********************************************************/
test_env = environment()
test_env.set('__SH', sh.full_path())
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
test('help 1', test1, args: ['--help'],
  env : test_env,
)
test('test2 help 1', test2, args: ['--help'],
  env : test_env,
)
test('test_interface1', test_interface1, args: ['--help'],
  env : test_env,
)
#//***********************************************************/


