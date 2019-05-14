# options.mk: provide options for this lib

export INCLUDE_DIR += -I $(EXT_LIB_PATH)/curl-7.64.1/include
export EXT_LIBS    += $(EXT_LIB_PATH)/curl-7.64.1/lib
