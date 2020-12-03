#
#	Default make file for godot projects
#
# config variables, edit to fit your config
BINARY_PATH = bin/godot*tools*
EDITOR_BIN = godot.bin
THREADS = -j$(shell nproc)
GODOT_PATH = ../Godot
CUSTOM_PATH = ../$(notdir $(CURDIR))/custom.py

# create an editor
all : ${EDITOR_BIN} 

${EDITOR_BIN} :
	# build godot
	scons profile=path/to/custom.py
	cd  ${GODOT_PATH}  && scons ${PLATFORM} ${THREADS}  profile=${CUSTOM_PATH}
	# add executable to root folder
	ln -s ${GODOT_PATH}/${BINARY_PATH} ${EDITOR_BIN} 
	

	
clean:
	# remove unnecesary files
	rm  ${EDITOR_BIN} ||\
	rm  ${GODOT_PATH}/bin/*

