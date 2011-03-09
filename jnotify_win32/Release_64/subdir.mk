################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Lock.cpp \
../Logger.cpp \
../WatchData.cpp \
../Win32FSHook.cpp \
../net_contentobjects_jnotify_win32_JNotify_win32.cpp 

OBJS += \
./Lock.o \
./Logger.o \
./WatchData.o \
./Win32FSHook.o \
./net_contentobjects_jnotify_win32_JNotify_win32.o 

CPP_DEPS += \
./Lock.d \
./Logger.d \
./WatchData.d \
./Win32FSHook.d \
./net_contentobjects_jnotify_win32_JNotify_win32.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	x86_64-w64-mingw32-g++ -I"c:\Program Files (x86)\Java\jdk1.6.0_18\include\win32" -I"c:\Program Files (x86)\Java\jdk1.6.0_18\include" -O0 -Os -Wall -c -fmessage-length=0 -static-libgcc -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


