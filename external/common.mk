sub_dirs = $(wildcard external/*)

# include options from all sub directories
-include $(addsuffix /options.mk,$(sub_dirs))

lib_list = $(foreach lib_dir,$(EXT_LIBS), $(wildcard $(lib_dir)/lib*))	# list of all libs available in external directory
lib_name = $(foreach lib,$(lib_list),$(call filename,$(lib)))			# list of libnames
lib_link = $(addprefix $(LIB_DIR)/,$(lib_name))							# path of linked lib

all: $(lib_link)	# include lib to be processed with default target

$(lib_link):
	ln -r -s $(filter %$(strip $(call filename,$@)),$(lib_list)) $(LIB_DIR)
