#! /usr/bin/env python
# encoding: utf-8
# Federico Allocati - 2016

"""
Quick n dirty libdynamixel detection
"""

import os
from waflib.Configure import conf


def options(opt):
    opt.add_option('--libdynamixel', type='string', help='path to libdynamixel', dest='libdynamixel')


@conf
def check_libdynamixel(conf, **kw):
    required = 'required' in kw and kw.get('required', False)
    includes_check = ['/usr/include', '/usr/local/include']
    resibots_dir = conf.options.resibots if hasattr(conf.options, 'resibots') and conf.options.resibots else None

    if resibots_dir:
        includes_check = [resibots_dir + '/include'] + includes_check

    if conf.options.libdynamixel:
        includes_check = [conf.options.libdynamixel + '/include'] + includes_check

    conf.start_msg('Checking for libdynamixel includes')
    try:
        res = conf.find_file('dynamixel/dynamixel.hpp', includes_check)
    except:
        res = False

    if res:
        conf.env.INCLUDES_LIBDYNAMIXEL = [os.path.expanduser(include) for include in includes_check]
        conf.env.DEFINES_LIBDYNAMIXEL = ['USE_LIBDYNAMIXEL']
        conf.end_msg('ok')
    else:
        if conf.options.libdynamixel and resibots_dir:
            msg = 'not found in %s nor in %s' % (conf.options.libdynamixel, resibots_dir)
        elif conf.options.libdynamixel or resibots_dir:
            msg = 'not found in %s' % (conf.options.libdynamixel if conf.options.libdynamixel else resibots_dir)
        else:
            msg = 'not found, use --libdynamixel=/path/to/libdynamixel or --resibots=/path/to/resibots'

        if required:
            conf.fatal(msg)
        else:
            conf.end_msg(msg, 'YELLOW')
