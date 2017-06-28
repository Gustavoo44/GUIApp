################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/driver/r_riic/r_riic.c 

OBJS += \
./synergy/ssp/src/driver/r_riic/r_riic.o 

C_DEPS += \
./synergy/ssp/src/driver/r_riic/r_riic.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/driver/r_riic/%.o: ../synergy/ssp/src/driver/r_riic/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DSF_MESSAGE_CLASS -I../GUIApp/synergy_cfg/ssp_cfg/bsp/ -I../GUIApp/synergy_cfg/ssp_cfg/driver/ -I../GUIApp/synergy/ssp/inc/ -I../GUIApp/synergy/ssp/inc/bsp/ -I../GUIApp/synergy/ssp/inc/bsp/cmsis/Include/ -I../GUIApp/synergy/ssp/inc/driver/api/ -I../GUIApp/synergy/ssp/inc/driver/instances/ -I../GUIApp/synergy_cfg/ssp_cfg/framework/el/ -I../GUIApp/synergy/ssp/inc/framework/el/ -I../GUIApp/synergy/ssp/src/framework/el/tx/ -I../GUIApp/synergy_cfg/ssp_cfg/framework/ -I../GUIApp/synergy/ssp/inc/framework/api/ -I../GUIApp/synergy/ssp/inc/framework/instances/ -I../GUIApp/synergy_cfg/ssp_cfg/framework/tes/ -I../GUIApp/synergy/ssp/inc/framework/tes/ -I../GUIApp/synergy_cfg/framework/ -I../GUIApp/synergy_cfg/ssp_cfg/framework -I../GUIApp/synergy/ssp/inc/framework/api -I../GUIApp/synergy/ssp/inc/framework/instances -I../GUIApp/synergy_cfg/ssp_cfg/framework/tes -I../GUIApp/synergy/ssp/inc/framework/tes -I../GUIApp/synergy_cfg/ssp_cfg/framework/el -I../GUIApp/synergy/ssp/inc/framework/el -I../GUIApp/synergy/ssp/src/framework/el/tx -I../GUIApp/synergy_cfg/ssp_cfg/bsp -I../GUIApp/synergy_cfg/ssp_cfg/driver -I../GUIApp/synergy/ssp/inc -I../GUIApp/synergy/ssp/inc/bsp -I../GUIApp/synergy/ssp/inc/bsp/cmsis/Include -I../GUIApp/synergy/ssp/inc/driver/api -I../GUIApp/synergy/ssp/inc/driver/instances -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy_cfg\ssp_cfg\framework" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc\framework\api" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc\framework\instances" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc\framework\tes" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc\framework\el" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\src\framework\el\tx" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy_cfg\ssp_cfg\driver" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc\bsp" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc\driver\api" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\synergy\ssp\inc\driver\instances" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\src" -I"C:\Users\Dell\e2_studio\workspace\GUIApp\src\synergy_gen" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '

