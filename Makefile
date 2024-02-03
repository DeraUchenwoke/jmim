#!/bin/bash
CLI_NAME=jmim
GO_CMD=go
EXEC_PATH=${HOME}/sdk/bin

clean:
	# Redirect stdout '1' and stderr '2' to null device file '/dev/null'.
	if find -f EXEC_PATH/${CLI_NAME} > /dev/null 2>&1; then rm EXEC_PATH/${CLI_NAME}; fi;

build:
	# Build executable if 'go' command exists.
	if ! command -v "${GO_CMD}" > /dev/null 2>&1; \
	then echo "The '${GO_CMD}' command does not exist." && exit 1; \
	else cd ${CLI_NAME} && echo "Adding ${CLI_NAME} to GOPATH..." && ${GO_CMD} install; \
	fi;

test:
	echo "Executing ${CLI_NAME}..."
	${HOME}/sdk/bin/${CLI_NAME}
