# returns the filename in the path given
# returns with leading spaces
define filename
	$(lastword $(subst /, ,$1))
endef
