#include "interrupts.h"

void printf(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];


void InterruptManager::SetInterruptDescriptorTableEntry(
    uint8_t intteruptNumber,
    uint16_t gdt_codeSegmentSelectorOffset,
    void (*handler)(),
    uint8_t DescriptorPrivilegeLevel,
    uint8_t DescriptorType)
{
    const uint8_t IDT_DESC_PRESENT = 0x80;

    interrtuptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler & 0xFFFF
    interrtuptDescriptorTable[interruptNumber].handlerAddressHighBits = (((uint32_t)handler) >> 16) & 0xFFFF
    interrtuptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    interrtuptDescriptorTable[interruptNumber].reserved = 0;
    interrtuptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel & 3) << 5)

}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
{
    uint16_t CodeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for(uint16_t i = 0; i < 256; i++)
        SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);


    SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

    InterruptDescriptorTable idt;
    idt.size = 256 * sizeof(GateDescriptorTable) - 1;
    idt.base - (uint32_t)interruptDescriptorTable;
    asm volatile("ldt %0" : : "m" (idt));
}

InterruptManager::~InterruptManger()
{
}

void InterruptManager::Activate()
{
    asm("sti");
}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp)
{
    printf(" INTERRUPT");
    return esp;
}
