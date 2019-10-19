import os 
import io
# dir_path: c:\Users\35974\source\repos\Noder\Noder\tools
dir_path = os.path.dirname(os.path.realpath(__file__))  # tools
noder_path = os.path.join(dir_path, '../')  # Noder
def preappend_pragma_once(hpp_filename):
    content = ""
    with io.open(hpp_filename, "r", encoding="utf-8") as hpp_file:
        content = hpp_file.read()
    if not content.startswith('#pragma once'):
        content = '#pragma once\n' + content
        with io.open(hpp_filename, "w+", encoding="utf-8") as hpp_file:
            print('preappend #pragma once to {}'.format(hpp_filename))
            hpp_file.write(content) 
    
def add_pragma_once(folder):
    files = os.listdir(folder)
    for filename in files:
        full_filename = os.path.join(folder, filename)
        if os.path.isfile(full_filename):
            if(full_filename.endswith('.hpp')):
                preappend_pragma_once(full_filename)
        else:
            add_pragma_once(full_filename)
    
add_pragma_once(noder_path)