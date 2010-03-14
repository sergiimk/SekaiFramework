#======================================================
# stage.py
# author: Sergey Mikhtonyuk
# date: 14 March 2010
# description: Stages the built project for deployment
#======================================================

import os
import sys
import shutil
import optparse

options = None
configurations = [ "release", "debug" ]
bin_extensions = [ ".exe", "", None, ".lib", ".a", ".dll", ".so" ]
header_extensions = [ ".h", ".inc" ]


def stage_project():
    if not os.path.exists(options.proj_dir):
        raise Exception("Project directory doesn't exist")
    
    bin_dir = find_binaries()

    src_dir = os.path.join(options.proj_dir, "src")
    if not os.path.exists(src_dir):
        raise Exception("Source files directory not found")

    if not os.path.exists(options.out_dir):
        os.makedirs(options.out_dir)

    stage_binaries(bin_dir)
    stage_headers(src_dir)


def find_binaries():
    bins = os.path.join(options.proj_dir, "bin")
    if not os.path.exists(bins):
        raise Exception("Binaries not found, have you built the project?")

    dirs = os.listdir(bins);
    for d in dirs:
        if d.lower().find(options.config.lower()) != -1:
            return os.path.join(bins, d)

    raise Exception("Binaries not found, have you built the project?")



def stage_binaries(bin_dir):
    bin_out = os.path.join(options.out_dir, "bin")

    if not os.path.exists(bin_out):
        os.makedirs(bin_out)

    for f in os.listdir(bin_dir):
        fl = os.path.join(bin_dir, f)
        _, ext = os.path.splitext(f)
        if os.path.isfile(fl) and ext in bin_extensions:
            shutil.copy(fl, bin_out)



def stage_headers(src_dir):
    src_out = os.path.join(options.out_dir, "sf")

    stage_headers_rec(src_dir, src_out)


def stage_headers_rec(src, dest):
    for d in os.listdir(src):
        dfull = os.path.join(src, d)
        ndest = os.path.join(dest, d)
        
        if os.path.isdir(dfull) and d != "implementation":
            copy_headers(dfull, ndest)
            stage_headers_rec(dfull, ndest)


def copy_headers(src, dest):
    if not os.path.exists(dest):
        os.makedirs(dest)

    for f in os.listdir(src):
        fl = os.path.join(src, f)
        _, ext = os.path.splitext(f)

        if os.path.isfile(fl) and ext in header_extensions:
            shutil.copy(fl, dest)


if __name__ == "__main__":
    parser = optparse.OptionParser()
    parser.add_option("-c", "--configuration", dest="config", help="release/debug", metavar="CFG")
    parser.add_option("-p", "--project-dir", dest="proj_dir", help="project root directory", metavar="PDIR")
    parser.add_option("-o", "--output-dir", dest="out_dir", help="output directory", metavar="ODIR")
    
    (options, _) = parser.parse_args()

    if options.config == None or options.config.lower() not in configurations:
        parser.error("Invalid project configuration")

    if options.proj_dir == None:
        parser.error("Project directory not specified")

    if options.out_dir == None:
        parser.error("Output directory not specified")

    try:
        stage_project()
    except Exception as ex:
        print "Staging failed: ", ex
    
