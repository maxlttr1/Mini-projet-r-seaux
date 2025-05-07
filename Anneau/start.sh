#!/bin/bash
pwd
make all
konsole --noclose -e "./pc_test1.run" & konsole --noclose -e "./pc_test2.run"