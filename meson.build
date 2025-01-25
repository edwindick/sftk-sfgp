# ./meson.build

project(
    'sfgp', 'c',

    default_options: ['buildtype=release'],
    license: 'MIT',
    version: '0.1',
    meson_version: '>=0.57.0'
)

include_dir = include_directories('./include')

subdir('src/sftk/sfgp')
subdir('bindings')