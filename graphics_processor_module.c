#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include "./address_map_arm.h"

// https://www.youtube.com/watch?v=oX9ZwMQL2f4&ab_channel=FastbitEmbeddedBrainAcademy

// tamanho maximo do dado que vai ser enviado pra ca (64bit??)
#define MAX_SIZE 64
// nao sei oq é
#define BASE_MINOR 0
// qtd de devices, deve ser 1
#define DEVICE_COUNT 1
// nome graphic processor
#define DEVICE_NAME "GP"


void * LW_virtual; // Lightweight bridge base address
volatile int* data_a_ptr;
volatile int* data_b_ptr;
volatile int* start_ptr;

static char msg[MAX_SIZE]; // array pra guardar a msg que vai chegar
// variaveis necessarias pro modulo
static dev_t device_number = 0;
static struct cdev cdev;
static struct class *class = NULL;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .read = device_read,
    .write = device_write,
    .release = device_release,
};

static void __init iniciar (void) {
    
    //implementar tratamento de erro dps
    // add um valor dinamico pro device_number
    alloc_chrdev_region(&device_number, BASE_MINOR, DEVICE_COUNT, DEVICE_NAME);
    cdev_init(&cdev, &fops);
    cdev.owner = THIS_MODULE;
    
    cdev_add(&cdev, &device_number, BASE_MINOR);
    class = class_create (THIS_MODULE, DEVICE_NAME);
	device_create (class, NULL, device_number, NULL, DEVICE_NAME);
    
    // generate a virtual address for the FPGA lightweight bridge
    LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);

    data_a_ptr = (int *) (LW_virtual + DATA_A_BASE);
    data_b_ptr = (int *) (LW_virtual + DATA_B_BASE);
    start_ptr = (int *) (LW_virtual + START_BASE);

    printk(KERN_INFO "Módulo carregado no sistema\n");

}

static void __exit parar(void) {
    iounmap (LW_virtual);
}

// funçoes pro driver de dispositivo de caracteres
// chamada qdo algum processo abre o arquivo
static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Arquivo aberto no espaço do usuário\n");
    return SUCCESS;
}
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Arquivo fechado\n");
    return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset) {
}

static int set_background_color(int R, int G, int B) {
    *data_a_ptr = (0x0000 | 0x00000); //opcode para WBR e endereço do registrador
    *data_b_ptr = (R << 2) | (G << 4) | B; // cor rosa
    return 1;
}



// Module metadata
MODULE_AUTHOR("TEC499-TP02-G02");
MODULE_DESCRIPTION("Módulo pro processador gráfico");
MODULE_LICENSE("GPL");



module_init(iniciar);
module_exit(sair);
