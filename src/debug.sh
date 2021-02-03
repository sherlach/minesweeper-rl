#!/bin/bash

# deps: tmux, gdb, gdbserver

tmux splitw -h -p 50 "gdbserver :12345 ./msweaper"
tmux selectp -t 0
gdb -x debug.gdb
