project('libgoodix-tls', 'c',
  version : '0.1',
  default_options : ['warning_level=3']
)

libusb = dependency('libusb-1.0')

inc = include_directories('include', 'src')

libgoodix = library(
  'goodix-tls',
  sources : [
    'src/goodix.c',
    'src/goodix_usb.c',
  ],
  include_directories : inc,
  dependencies : libusb,
  install : true
)

executable(
  'goodix-usb-test',
  'tools/goodix-capture.c',
  include_directories : inc,
  link_with : libgoodix
)
