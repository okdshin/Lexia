# A very simple setup script to create a single executable
#
# hello.py is a very simple "Hello, world" type script which also displays the
# environment in which the script runs
#
# Run the build process by running the command 'python setup.py build'
#
# If everything works well you should find a subdirectory in the build
# subdirectory that contains the files needed to run the script without Python

from cx_Freeze import setup, Executable

setup(
        name = "lexia",
        version = "1.0",
        description = "lexia is simple lexical analyzer generator",
        executables = [Executable("lexia.py")],
        options = {
            'build_exe': {
                'include_files':['resource/LexicalAnalyzer.h', 'resource/TokenType.h']
            }    
        })

