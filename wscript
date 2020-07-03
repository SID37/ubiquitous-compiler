top = '.'
out = 'build'

def options(opt):
        opt.load('compiler_cxx')

def configure(conf):
        conf.load('compiler_cxx')

def build(bld):
        bld.program(
                source=bld.path.ant_glob('src/**/*.cpp'),
                target='test',
                includes='headers')
