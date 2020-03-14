@echo off
cl -c myLink.c 
cl -c SIMS.c
cl -c userType.c
cl -c message.c

cl StudentAchievementManagementSystem.c myLink.obj SIMS.obj userType.obj message.obj