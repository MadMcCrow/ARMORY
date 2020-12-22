#!/usr/bin/env python
#
# functions.py : 
#             useful functions for the python modules in this folder
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#

#
#   getGodotVersion()
#   get version as tuple int,int : major, minor
#
def getGodotVersion() -> tuple :
    try:
        from version  import major
        from version  import minor
        return major, minor
    except:
        return tuple([4,0])
        pass


#
#   getPlatform() :
#   get platform  as tuple(int,str,str)
#   first is 32 or 64 bits, second is operating system, 3rd is CPU architecture (x86, arm, risc-v, ...)
#   everything is in a Godot fashion to avoid future problems
#
def getPlatform() -> tuple :
    from sys      import maxsize
    from platform import system
    from os       import uname
    bits = 64 if maxsize > 2**32 else 32
    arch  = uname()[4][:3] 
    major, minor = getGodotVersion()
    if "arm" in arch :
        arch = "arm" + str(bits)
    elif "x86" in arch : 
        arch = "x" + str(bits)
    platform =  system()
    if platform.lower() in ["linux", "freebsd7", "freebsd8", "freebsdN", "openbsd6"] : 
        return bits, ("linuxbsd" if major == 4 else "x11"), arch
    elif platform.lower() in ["win32", "cygwin", "msys"] : 
        return bits, "windows", arch
    elif platform.lower() in ["darwin", "os2", "os2emx"] : 
        return bits, "osx", arch
    else: #riscos or atheos
        return bits, platform, arch

#
#   isWindows :
#   Check platform against windows  
#
def isWindows() -> bool:
    _bits, os, _arch = getPlatform()
    return "windows" in os

#
#   isMacOs :
#   Check platform against osx  
#
def isMacOs() -> bool:
    _bits, os, _arch = getPlatform()
    return "osx" in os

#
#   isLinux :
#   Check platform against linuxbsd or x11  
#
def isLinux() -> bool:
    _bits, os, _arch = getPlatform()
    return  ("linuxbsd" in os  or "x11" in os)

#
#   isLinux :
#   Check platform against linuxbsd or x11  
#
def  isArm(arch : str) -> bool:
    return "arm" in arch

# Find a folder based on its name
def findFolder(path : str, foldername : str)  -> str:
    from os import walk
    from os.path import relpath
    for cur, dirs, _files in walk(path):
        if foldername in dirs :
            return relpath( str('/'.join([cur,foldername])) )

#get git Rep out of a path
def getGitRepo(path : str):
    import os.path
    path = os.path.realpath(path)
    repo = None
    try:
        from git import Repo
        try :
            repo = Repo(path)
        except:
            parent_path = None
            is_git = False
            while not is_git : 
                parent_path = os.path.abspath(os.path.join(path, os.pardir))
                is_git = ".git" in getFolders(parent_path)
            if not is_git : 
                raise Exception
            repo = Repo(parent_path)
    except:
        return None
    finally:
        return repo


# look for path in tree
def _gitRecursiveLookForPath(path, trees, found = None) :
    if  not isinstance(found, list) :
        found = []
    import os.path
    try:
        for tree in trees :
            try :
                if str(os.path.basename(path)) in str(os.path.basename(tree.path))  :
                    found = [str(p.path) for p in tree.trees]
                else:
                    _gitRecursiveLookForPath(path, tree.trees, found)
            except:
                continue
    except:
        pass
    return found
    


# get names of git tracked folders in path
def getGitFolders(path : str) -> list :
    dirs = []
    try:
        import os.path 
        repo = getGitRepo(path)
        dirs = _gitRecursiveLookForPath(path, repo.tree())
    except:
        raise
    finally:
        return dirs

# get names of subfolders in folder
def getFolders(path : str)  -> list:
    from os import walk
    return next(walk(path))[1]

# Find files based on substring
def findFiles(path : str, sub :str)  -> list:
    glob = []
    from os import walk
    for cur, _dirs, files in walk(path):
        glob = glob + ['/'.join([cur,itr]) for itr in files if sub in str(itr)]
    return glob


# Find files based on list of substring
def findFilesList(path : str, sub_list :list)  -> list:
    glob = []
    for sub in sub_list :
        glob = glob + findFiles(path, sub)
    # get only duplicates (observes all rules)
    dup = set(glob)
    glob = list(set([x for x in glob if x not in dup or dup.discard(x)]))
    print(glob)
    return glob

