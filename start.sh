#!/bin/bash
pwd
make all
konsole --noclose -e "./pc3.run" & konsole --noclose -e "./pc2.run" & konsole --noclose -e "./pc1.run"