################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AOAFrame.cpp \
../src/AOAPlus.cpp \
../src/AOAReciver.cpp \
../src/LocationFrame.cpp \
../src/datamaker.cpp \
../src/serial.cpp 

OBJS += \
./src/AOAFrame.o \
./src/AOAPlus.o \
./src/AOAReciver.o \
./src/LocationFrame.o \
./src/datamaker.o \
./src/serial.o 

CPP_DEPS += \
./src/AOAFrame.d \
./src/AOAPlus.d \
./src/AOAReciver.d \
./src/LocationFrame.d \
./src/datamaker.d \
./src/serial.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


