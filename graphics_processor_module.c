#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include "./address_map_arm.h"

// https://www.youtube.com/watch?v=oX9ZwMQL2f4&ab_channel=FastbitEmbeddedBrainAcademy
// https://www.youtube.com/watch?v=DwwZR0EE_1A&list=PLlrqp8hxLfoqSIQFrGbAM5lv5uAnZBB61&index=2&ab_channel=TechoGenius
// sudo /home/root/Problemas/2024-1/CoLendaInFPGA.sh botar gpu na placa


// tamanho maximo do dado que vai ser enviado pra ca (64bit??)
#define MAX_SIZE 32
// nao sei oq é
#define BASE_MINOR 71
// qtd de devices, deve ser 1
#define DEVICE_COUNT 1
// nome graphic processor
#define DEVICE_NAME "graphicProcessor"
#define OPCODE_WBR 0b0000
#define OPCODE_WBM 0b0010
#define OPCODE_DP 0b0011
#define OPCODE_WSM 0b0001
#define WBR 1
#define WBM 2
#define DP 3
#define WSM 4
#define CLR 5


void * LW_virtual; // Lightweight bridge base address
volatile int* data_a_ptr;
volatile int* data_b_ptr;
volatile int* wrreg_ptr;

// variaveis necessarias pro modulo
static char msg[MAX_SIZE]; // array pra guardar a msg que vai chegar
static dev_t device_number = 0;
static struct cdev cdev;
static struct class *class = NULL;


static int __init iniciar (void);
static void __exit parar(void);
static int device_open(struct inode *inode, struct file *filp);
static int device_release(struct inode *inode, struct file *filp);
static ssize_t device_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t device_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);
static void escrita_buffer(void);
static int instruction_DP(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco);
static int instruction_WBR (int R, int G, int B, int reg, int x, int y, int offset, int sp);
static int instruction_WBM (int column, int line, int R, int G, int B);
static int instruction_WSM (int R, int G, int B, endereco_memoria);
static void clear_screen (void);

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
		printk (KERN_ERR "alloc_chrdev_region() falhou, erro %d\n", err);
		return err;
	}

    cdev_init(&cdev, &fops);
    cdev.owner = THIS_MODULE;

    if ((err = cdev_add(&cdev, device_number, BASE_MINOR)) < 0) {
		printk (KERN_ERR "cdev_add() falhou, erro: %d\n", err);
		return err;
	}

    class = class_create (THIS_MODULE, DEVICE_NAME); // ou class = class_create (THIS_MODULE, DEVICE_NAME);
	device_create (class, NULL, device_number, NULL, DEVICE_NAME);
    
    // generate a virtual address for the FPGA lightweight bridge
    LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);

    data_a_ptr = (int *) (LW_virtual + DATA_A_BASE);
    data_b_ptr = (int *) (LW_virtual + DATA_B_BASE);
    wrreg_ptr = (int *) (LW_virtual + WRREG_BASE);

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
    return 0;
}
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Arquivo fechado\n");
    return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
	if(copy_to_user(buffer, msg, length) != 0) {
        printk (KERN_ERR "Erro: copy_to_user falhou\n");
    }
    printk(KERN_INFO "Lendo");
    return length;
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset) {
   
    int values[MAX_SIZE];
	int instruction = 0;
    
    if (copy_from_user(msg, buffer, length) != 0){
		printk (KERN_ERR "Erro: copy_from_user falhou\n");
    }

    sscanf(msg, "%d", &values[0]);
    instruction = values[0];

    if (instruction == WBR) {
        sscanf(msg, "%d %d %d %d %d %d %d %d %d", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5], &values[6], &values[7], &values[8]);
        printk(KERN_INFO "entrou em wbr\n");
        instruction_WBR(values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8]);
    } else if (instruction == WBM) {
        sscanf(msg, "%d %d %d %d %d %d", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5]);
        instruction_WBM(values[1], values[2], values[3], values[4], values[5]);
    } else if (instruction == DP) {
        sscanf(msg, "%d %d %d %d %d %d %d %d %d", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5], &values[6], &values[7], values[8]);
       	instruction_DP(values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8]);
    } else if (instruction == WSM) {
	sscanf(msg, "%d %d %d %d %d", &values[0], &values[1], &values[2], &values[3], &values[4]);
        instruction_WSM(values[1], values[2], values[3], values[4]);
    } else if (instruction == CLR) {
	    clear_screen();
    }

    return length;
}

static void escrita_buffer(void) {
    *wrreg_ptr = 1;
    *wrreg_ptr = 0;
}


// background e sprite
static int instruction_WBR (int R, int G, int B, int reg, int x, int y, int offset, int sp) {
    
    *data_a_ptr = (reg << 4) | OPCODE_WBR; //opcode para WBR e endereço do registrador
    if (sp) {
        *data_b_ptr = (sp << 29) | (x << 19) | (y << 9) | offset;
        printk (KERN_INFO "setou sprite");
    } else {
        *data_b_ptr = (B << 6) | (G << 3) | R;
    }
    escrita_buffer();
    return 1;
}

static int instruction_WBM (int column, int line, int R, int G, int B) {
    //Calcula o endereço de memória do bloco com base na coluna e linha
    int endereco_memoria = (line * 80 + column); // 80: numero de colunas por linha = 245

    *data_a_ptr = (endereco_memoria << 4) | OPCODE_WBM;
    *data_b_ptr = (B << 6) | (G << 4) | R;

    escrita_buffer();
    return 1;
}

static int instruction_DP(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco) {
    *data_a_ptr = (endereco) | OPCODE_DP;
    *data_b_ptr = (forma << 31) | (B << 28) | (G << 25) | (R << 22) | (tamanho << 18) | (y << 9) | x;
    escrita_buffer();
    return 1;
}

static int instruction_WSM (int R, int G, int B, int endereco_memoria) {
    *data_a_ptr = (endereco_memoria << 4) | OPCODE_WSM;
    *data_b_ptr = (B << 6) | (G << 4) | R;

    escrita_buffer();
    return 1;
}

//Limpa a tela do monitor (640 x 480)
static int clear_screen (void) {
	int i, j;
	for (i = 0; i < 480; i++) {
		for (j = 0; j < 640; j++) {
			instruction_WBM(j, i, 0, 0, 0);	// Define o pixel na posição (j, i) para a cor preta (RGB = 0, 0, 0)
		}
	}
	return 1;
}


// Module metadata
MODULE_AUTHOR("TEC499-TP02-G02");
MODULE_DESCRIPTION("Driver de caracter pro processador gráfico");
MODULE_LICENSE("GPL");

module_init(iniciar);
module_exit(parar);
