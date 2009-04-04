#!/usr/bin/env python
import os.path
from glob import glob

prog_target = 'tx'
sources = glob('*.cpp')

env = Environment()
win32 = ARGUMENTS.get('win32', 0)
debug_flag = ARGUMENTS.get('debug', 0)

env.AppendUnique(LIBS=['m', 'IL', 'mxml', 'rcbc', 'luabind'])

if int(win32):
	env.Tool('crossmingw', toolpath = ['scons-tools'])
	env['MINGWROOT'] = '/usr/$MINGWPREFIX'
	env['MINGWLIBS'] = '$MINGWROOT/lib/'
	
	env.AppendUnique(LIBS=['opengl32', 'glu32'])
	env.ParseConfig('/usr/$MINGWPREFIX/bin/sdl-config --cflags --libs')
	env.AppendUnique(LIBS=['lua'])
	env.AppendUnique(LIBS=['bulletdynamics', 'bulletcollision', 'bulletmath'])
	env.MergeFlags('-I/usr/$MINGWPREFIX/include/bullet/')
	env.MergeFlags(env.subst( "$MINGWLIBS/libopengl32.a" ))
	env.MergeFlags(env.subst( "$MINGWLIBS/libmxml.a" ))
	env.MergeFlags(env.subst( "$MINGWLIBS/DevIL.lib" ))
else:
	env.AppendUnique(LIBS=['GL', 'GLU'])
	env.ParseConfig('sdl-config --cflags --libs')
	env.ParseConfig('pkg-config --cflags --libs lua5.1')
	env.ParseConfig('pkg-config --cflags --libs bullet')
	

if int(debug_flag):
	env.Append(CCFLAGS = ['-g'])
	
env.Append(CCFLAGS = ['-Wall'])

objects = env.Object(sources)
target = env.Program(target = prog_target, source=objects)

Default(target)
