project('todoprogram', 'cpp')

if meson.get_compiler('cpp').get_id() == 'msvc'
  extra_args = ['/std:c++latest','/Zc:preprocessor']
elif meson.get_compiler('cpp').get_id() == 'clang'
  extra_args = ['-std=c++20']
else
  extra_args = ['-std=c++20']
endif

notifydeps = [dependency('libnotifymm-1.0'), dependency('glibmm-2.4')]
sources = files(
  'src/main.cpp',
  'src/fileUtils.cpp',
  'src/printUtils.cpp'
)
executable('todoprogram', sources, dependencies: notifydeps, cpp_args: extra_args)
