#ifndef __INTERRUPTS.H 
#define __INTERRUPTS.H 

#include "types.h"
#include "port.h"
#include "gdt.h"

	class InterruptManager
	{
    protected:
        struct GatedDescriptor
        {
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSeclector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBits;

        }__attribute__((packed))

        static GateDescriptor interruptDescriptorTable[256];
        
        struct InterruptDescriptorTablePointer
        {
            uint16_t size;
            uint32_t base;
        }__attribute__((packed))

        static void SetInterruptDescriptorTableEntry(
                uint8_t intteruptNumber,
                uint16_t gdt_codeSegmentSelectorOffset,
                void (*handler)(),
                uint8_t DescriptorPrivilegeLevel,
                uint8_t DescriptorType
                );

	public:
        InterruptManager(GlobalDescriptorTable* gdt);
        ~InterruptManger();
        void Activate();
            
		static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);
        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x01();
        static void HandleInterruptRequest0x00();
	};


#endif
