#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include "./address_map_arm.h"

// Module metadata
MODULE_AUTHOR("TEC499-TP02-G02");
MODULE_DESCRIPTION("Módulo pro processador gráfico");
MODULE_LICENSE("GPL");

void * LW_virtual; // Lightweight bridge base address
volatile int* data_a_ptr;
volatile int* data_b_ptr;
volatile int* start_ptr;

static void __init iniciar (void) {
    // generate a virtual address for the FPGA lightweight bridge
    LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);

    data_a_ptr = (int *) (LW_virtual + DATA_A_BASE);
    data_b_ptr = (int *) (LW_virtual + DATA_B_BASE);
    start_ptr = (int *) (LW_virtual + START_BASE);

}

static void __exit parar(void) {
    iounmap (LW_virtual);
}

static int set_background_color(int R, int G, int B) {
    *data_a_ptr = (0x0000 | 0x00000); //opcode para WBR e endereço do registrador
    *data_b_ptr = (R << 2) | (G << 4) | B; // cor rosa
    return 1;
}



module_init(iniciar);
module_exit(sair);
