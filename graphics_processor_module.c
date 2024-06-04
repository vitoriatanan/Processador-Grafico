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
// https://www.youtube.com/watch?v=DwwZR0EE_1A&list=PLlrqp8hxLfoqSIQFrGbAM5lv5uAnZBB61&index=2&ab_channel=TechoGenius

// tamanho maximo do dado que vai ser enviado pra ca (64bit??)
#define MAX_SIZE 64
// nao sei oq é
#define BASE_MINOR 71
// qtd de devices, deve ser 1
#define DEVICE_COUNT 1
// nome graphic processor
#define DEVICE_NAME "graphicProcessor"


void * LW_virtual; // Lightweight bridge base address
volatile int* data_a_ptr;
volatile int* data_b_ptr;
volatile int* start_ptr;

static char msg[MAX_SIZE]; // array pra guardar a msg que vai chegar
// variaveis necessarias pro modulo
static dev_t device_number = 0;
static struct cdev cdev;
static struct class *class = NULL;
//unint8_t *kernelbuf;


static int __init iniciar (void);
static void __exit parar(void);
static int device_open(struct inode *inode, struct file *filp);
static int device_release(struct inode *inode, struct file *filp);
static ssize_t device_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t device_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .read = device_read,
    .write = device_write,
    .release = device_release,
};


static int __init iniciar (void) {
    int err = 0;
    
    //implementar tratamento de erro dps
    // add um valor dinamico pro device_number
    if ((err =  alloc_chrdev_region(&device_number, BASE_MINOR, DEVICE_COUNT, DEVICE_NAME)) < 0) {
		printk (KERN_ERR "video: alloc_chrdev_region() failed with return value %d\n", err);
		return err;
	}

    cdev_init(&cdev, &fops);
    cdev.owner = THIS_MODULE;

    if ((err = cdev_add(&cdev, device_number, BASE_MINOR)) < 0) {
		printk (KERN_ERR "video: cdev_add() failed with return value %d\n", err);
		return err;
	}

    class = class_create (DEVICE_NAME); // ou class = class_create (THIS_MODULE, DEVICE_NAME);
	device_create (class, NULL, device_number, NULL, DEVICE_NAME);
    
    // generate a virtual address for the FPGA lightweight bridge
    // LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);

    // data_a_ptr = (int *) (LW_virtual + DATA_A_BASE);
    // data_b_ptr = (int *) (LW_virtual + DATA_B_BASE);
    // start_ptr = (int *) (LW_virtual + START_BASE);

    printk(KERN_INFO "Driver carregado no sistema\n");

    return 0;
}

static void __exit parar(void) {
	device_destroy(class, device_number);
	class_destroy(class);
	cdev_del(&cdev);
	unregister_chrdev_region(device_number, DEVICE_COUNT);
    iounmap (LW_virtual);

    printk(KERN_INFO "Driver removido do sistema\n");
	
}

// funçoes pro driver de dispositivo de caracteres
// chamada qdo algum processo abre o arquivo
static int device_open(struct inode *inode, struct file *file) {

    printk(KERN_INFO "Arquivo aberto no espaço do usuário\n");
    return 1;
}
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Arquivo fechado\n");
    return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
	if(copy_to_user(buffer, msg, length) != 0) {
        printk (KERN_ERR "Error: copy_to_user unsuccessful");
    }
    printk(KERN_INFO "Lendo");
    return length;
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset) {

    if (copy_from_user(msg, buffer, length) != 0){
		printk (KERN_ERR "Error: copy_from_user unsuccessful");
    }
    printk(KERN_INFO "mensagem escrita: %s", msg);
    return length;
	//sscanf();
}

static int set_background_color(int R, int G, int B) {
    *data_a_ptr = (0x0000 | 0x00000); //opcode para WBR e endereço do registrador
    *data_b_ptr = (R << 2) | (G << 4) | B; // cor rosa
    return 1;
}



// Module metadata
MODULE_AUTHOR("TEC499-TP02-G02");
MODULE_DESCRIPTION("Driver de caracter pro processador gráfico");
MODULE_LICENSE("GPL");

module_init(iniciar);
module_exit(parar);
