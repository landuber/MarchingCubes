# vim: filetype=python

from SCons.Script import *
from os           import getenv
from os.path      import join


AddOption('--prefix'
        , dest    = 'prefix'
        , nargs   = 1
        , type    = 'string'
        , action  = 'store'
        , default = getenv('PREFIX', '/usr')
        , help    = '''
A prefix with which to look for and install libraries / applications.
        ''')

AddOption('--coverage'
        , dest    = 'coverage'
        , default = False
        , action  = 'store_true'
        , help    = '''
GCC Code Coverage should be enabled see: http://www.llvm.org/docs/CoverageMappingFormat.html
        ''')

AddOption('--include-path'
        , dest    = 'include_path'
        , default = []
        , action  = 'append'
        , help    = '''
Add another include path.  Note that for cases where multiple subdirectories
are already added to the include paths, these will be appended here as well.

Eg:
    --include-path=/usr/tmp

This argument should be repeated for every additional include path.
        ''')

AddOption('--lib-path'
        , dest    = 'lib_path'
        , default = []
        , action  = 'append'
        , help    = '''
Add another lib path.  Note that for cases where multiple subdirectories
are already added to the include paths, these will be appended here as well.
        ''')

AddOption('--dbg'
        , dest    = 'debug'
        , default = False
        , action  = 'store_true'
        , help    = '''
Disable optimizations and include debug symbols
        ''')

AddOption('--production'
        , dest    = 'production'
        , default = False
        , action  = 'store_true'
        , help    = '''
Use production quality build options
        ''')

AddOption('--verbose', action='store_true', help='use verbose output')

# --------------------------------------------------------------------------- #
Env = Environment(ENV={'PATH': getenv('PATH')})
COLORS = {
    'cyan'  : '\033[96m',
    'purple': '\033[95m',
    'blue'  : '\033[94m',
    'green' : '\033[92m',
    'yellow': '\033[93m',
    'red'   : '\033[91m',
    'end'   : '\033[0m'
}

compile_str = \
        '{0}Compile:{1} $SOURCE'.format(COLORS['green'], COLORS['end'])
linking_str = \
        '{0}Linking:{1} $SOURCE'.format(COLORS['yellow'], COLORS['end'])

if not GetOption('verbose'):
    Env.Append(
        CXXCOMSTR=compile_str,
        CCCOMSTR=compile_str,
        SHCXXCOMSTR=compile_str,
        SHCCCOMSTR=compile_str,
        ARCOMSTR=linking_str,
        SHLINKCOMSTR=linking_str,
        LINKCOMSTR=linking_str
        )

# -- virtualenv paths
venv_root = getenv('VIRTUAL_ENV', '/usr')

lib_paths = [
    '/usr/local/lib',
    '/usr/local/lib64',
    '/usr/lib64',
    '/usr/lib'
    ] + [join(venv_root, 'lib')] \
      + GetOption('lib_path')
libraries = [
    'opencv_core',
    'opencv_highgui',
    'opencv_imgproc',
    'opencv_photo',
    'glog',
    'pcl_common',
    'pcl_io',
    'pcl_sample_consensus',
    'boost_system',
    'boost_filesystem',
    'protobuf',
    'boost_program_options',
    'protobuf',
     ]
Env.Append(LIBPATH=lib_paths)
Env.Append(RPATH=lib_paths)
Env.Append(LIBS=libraries)

base_include_paths = [
    '/usr/local/include',
    '/usr/include'
    ] + GetOption('include_path') \
      + [join(venv_root, 'include')]
for path in base_include_paths:
    Env.Append(CPPPATH=[
                Dir('#src').abspath,
                path,
                join(path, 'pcl-1.7'),
                join(path, 'pcl-1.8'),
                join(path, 'eigen3')])

Env.Append(CXXFLAGS=['-std=c++11'
                   , '-Wall'
                   , '-Werror'
                   #, '-ffast-math'
                   #, '-funsafe-math-optimizations'
                   #, '-fno-signed-zeros'
                   #, '-ffinite-math-only'
                   , '-pipe'])

if getenv('CXX', None):
    Env.Replace(CXX=getenv('CXX'))

Env.Append(CXXFLAGS=[
    '-rdynamic',
    '-msse',
    '-msse2',
    '-msse3',
    '-msse4',
    '-msse4.2'
    ])

if   GetOption('debug'):
    Env.Append(CXXFLAGS=[
        '-rdynamic',
        '-O0',
        '-g'])
elif GetOption('production'):
    Env.Append(CXXFLAGS=[
        '-mavx',
        '-O3',
        '-DNDEBUG',
        ])
else:
    Env.Append(CXXFLAGS=[
        '-O2'
        ])

if GetOption('coverage'):
    Env.Append(LIBS=['gcov'])
    Env.Append(CXXFLAGS=['--coverage'])
    #Env.Append(LIBS=['profiler_rt'])
    #Env.Append(CXXFLAGS=[
    #    '-fprofile-instr-generate',
    #    ])

# --------------------------------------------------------------------------- #
libMarchingCubes = \
    SConscript('src/SConscript',
               exports={'Env':Env},
               variant_dir='build')

applications = \
    SConscript('app/SConscript',
               exports={'Env':Env, 'libMarchingCubes': libMarchingCubes})
