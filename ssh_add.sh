#!/bin/sh
eval "$(ssh-agent -s)"
ssh-add -K optoc
