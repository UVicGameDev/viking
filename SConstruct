# This is an scons script to build the library
# Projects in different IDEs should make an scons call to this file

import sys
from os import path

# directory info
viking_dirs = { 
'target': 'viking',
'src': 'source/src', # root of source files
'include': 'source/include', # root of include directory
'build': 'build', # name of the build folder created in the root of the repository
'obj': 'obj', # name of the build subdirectory where object files are built
'bin': 'bin',
'release': 'Release',
'debug': 'Debug',
'demos': 'demos',
'test': 'Test'
}

# compiler flags
viking_flags = {
'common': [ '-std=c++11', '-Wall' ],
'debug': [ '-g', '-D_DEBUG' ],
'release': [ '-O2', '-DNDEBUG' ],
}

# libraries to link
viking_libs = {
'common': [ 'Irrlicht', 'GL' ],
'linux': [ 'Xxf86vm' ]
}

# will be either viking_dirs['debug'] or viking_dirs['release'] depending on script arguments
build_configuration = ''

# pick up "debug" argument from command line input. Defaults to 0 (false).
if ARGUMENTS.get('debug', '0') != '0':
	build_configuration = viking_dirs['debug']
else:
	build_configuration = viking_dirs['release']

# create environment
env = Environment()

# add common compiler flags
env.Append(CXXFLAGS = viking_flags['common'])

# link common libraries
env.Append(LIBS = viking_libs['common'])

# link platform dependent libraries
if sys.platform.startswith('linux'):
	env.Append(LIBS = viking_libs['linux'])

# add include directories: include folder AND src folder
env.Append(CPPPATH = [ path.abspath(viking_dirs['include']), path.abspath(viking_dirs['src']) ] )

configuration_path = ''

# conditionally add compiler flags
if build_configuration == viking_dirs['debug']:
	env.Append(CXXFLAGS = viking_flags['debug'])
	configuration_path = viking_dirs['debug']
else:
	env.Append(CXXFLAGS = viking_flags['release'])
	configuration_path = viking_dirs['release']

# compose path to build of Viking
viking_dirs['build_obj'] = path.abspath(path.join(viking_dirs['build'], configuration_path, viking_dirs['obj']))
viking_dirs['build_bin'] = path.abspath(path.join(viking_dirs['build'], configuration_path, viking_dirs['bin']))

# export variables so other scripts can Import them
Export('env viking_dirs build_configuration viking_libs')

# subdirectories with SConscripts in them
script_subdirs = []

if ARGUMENTS.get('viking','1') != '0':
	script_subdirs += ['source']

if ARGUMENTS.get('test','0') != '0':
	script_subdirs += ['tests']

# Run scripts to selectively build viking sub-projects
SConscript(dirs=script_subdirs, name='SConscript')
