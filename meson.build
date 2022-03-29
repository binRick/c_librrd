project(
    'c_librrd', ['c'],
    version : '0.0.1',
    default_options : ['c_std=gnu99'],
    default_options : [
      'warning_level=2',
    ],
)

pkg = import('pkgconfig')
sh = find_program('sh', required : true)
rrdtool = find_program('rrdtool', required : true)

cc = meson.get_compiler('c')

add_project_arguments(
  cc.get_supported_arguments([
    '-lm',
    '-luv',
    '-lcurl',
    '-lshmc',
    '-lvterm',
  ]),
  language : 'c',
)

add_project_arguments(
  cc.get_supported_arguments([
    '-D_GNU_SOURCE',
    '-fPIC',
  ]),
  language : 'c',
)

incdir = include_directories(
  'include', 
  '../',
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

test_bins = [
  'test1', 
  'test2', 
]

test_env = environment()
test_env.set('__SH', sh.full_path())
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())


    test('help 1', test1, args: ['--help'],
      env : test_env,
    )
    test('test1 help 2', test1, args: ['-h'],
      env : test_env,
    )
    test('test2 help 1', test2, args: ['--help'],
      env : test_env,
    )
#//***********************************************************/


