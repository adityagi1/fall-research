################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BranchBoundNode.cpp \
../IsolationBranchTree.cpp \
../STMinCutSolver.cpp \
../data_structures.cpp \
../main.cpp 

OBJS += \
./BranchBoundNode.o \
./IsolationBranchTree.o \
./STMinCutSolver.o \
./data_structures.o \
./main.o 

CPP_DEPS += \
./BranchBoundNode.d \
./IsolationBranchTree.d \
./STMinCutSolver.d \
./data_structures.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


