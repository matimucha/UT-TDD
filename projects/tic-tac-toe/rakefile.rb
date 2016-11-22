#!/usr/bin/ruby

unless File.exists?('/tmp/RakeBuilder.rb')
  system('wget https://raw.githubusercontent.com/chaos0x8/rake-builder/master/lib/RakeBuilder.rb -O /tmp/RakeBuilder.rb', err: '/dev/null')
end

require '/tmp/RakeBuilder.rb'

lib = Library.new { |t|
  t.sources = FileList['External/**/*.cpp', 'Source/**/*.cpp'] - ['Source/main.cpp']
  t.name = 'bin/libticTacToe.a'
  t.flags = [ '--std=c++14', '-g' ]
  t.includes = [ 'Source', 'External' ]
}

app = Executable.new { |t|
  t.name = 'bin/ticTacToe'
  t.sources = FileList['Source/main.cpp']
  t.flags = lib.flags
  t.includes = lib.includes
  t.libs = [lib]
}

desc 'Compiles and runs application'
multitask(app: RakeBuilder::Names[app]) {
  sh app.name
}

ut = Executable.new { |t|
  t.name = 'bin/ticTacToe-ut'
  t.sources = FileList['ExternalTestModules/**/*.cpp', 'TestModules/**/*.cpp']
  t.flags = app.flags + [ '-pthread' ]
  t.libs = app.libs + [ '-lgtest', '-lgmock' ]
  t.includes = app.includes + [ 'ExternalTestModules', 'TestModules' ]
}

desc 'Compiles and runs uts'
multitask(ut: RakeBuilder::Names[ut]) {
  sh ut.name
}

multitask(default: :ut)

desc 'Cleans objects, libs and executables'
task(:clean) {
  sh "rm -rf .obj" if File.directory?('.obj')
  sh "rm -rf bin" if File.directory?('bin')
}
