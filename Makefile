# Nome do módulo
obj-m += graphics_processor_module.o

# Diretório do kernel
KDIR := /lib/modules/$(shell uname -r)/build

# Diretório do código-fonte atual
PWD := $(shell pwd)

# Alvo principal (default)
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Limpeza dos arquivos gerados pela compilação
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean