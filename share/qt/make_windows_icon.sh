#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/exus.ico

convert ../../src/qt/res/icons/exus-16.png ../../src/qt/res/icons/exus-32.png ../../src/qt/res/icons/exus-48.png ${ICON_DST}
