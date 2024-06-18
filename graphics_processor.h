/**
 * Este código foi adaptado de um documento PDF.
 * Fonte: Desenvolvimento de uma Arquitetura Baseada em Sprites para criação de Jogos 2D em Ambientes
 * Reconfiguráveis utilizando dispositivos FPGA, Gabriel B. Alves e Anfranserai M. Dias, Páginas 9-10.
 *
 * URL:  https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view
 */

// Exemplos de constantes para fixar valores de movimento de um sprite
#define LEFT         0
#define RIGHT        4
#define UP           2
#define DOWN         6
#define UPPER_RIGHT  1
#define UPPER_LEFT   3
#define BOTTOM_LEFT  5
#define BOTTOM_RIGHT 7

/**
 * Estrutura que define um sprite móvel.
 * 
 * Atributos coord_x e coord_y: armazenam as coordenadas x e y do sprite. 
 * Atributo direction: armazena um número inteiro indicando o ângulo de movimento. 
 * Atriburo offset: indica o deslocamento na memória utilizado para selecionar o bitmap
 * armazenado no Processador Gráfico.
 * Atributo data_register: indica o registrador do Banco de Registradores.
 * Atributos step_x e step_y: representam os passos nas direções x e y.
 * Atributo ativo: indica se o sprite está ativo ou não.
 * Atributo collision: indica se houve uma colisão com outro sprite.
*/
typedef struct {
    int coord_x, coord_y;
    int direction, offset, data_register;
    int step_x, step_y;
    int ativo, collision;
} Sprite;

/**
 * Estrutura que define sprites fixos.
 * 
 * Não possuem movimentação durante o jogo.
 * Armazena coordenadas, deslocamentos na memória,
 * registrador de dados e estado do sprite.
 * */
typedef struct {
    int coord_x, coord_y, offset;
    int data_register, ativo;
} Sprite_Fixed;

/**
 * Posicionar um sprite na tela
 * 
 * @param registrador      Define o registrador
 * @param x                Definição da coordenada x do sprite
 * @param y                Definição da coordenada y do sprite
 * @param offset           Deslocamento na memória para selecionar o bitmap
 * @param activation_bit   Estado de ativação do sprite
 * @return                 1 caso operação seja bem sucedida, e 0 caso contrário
*/
int set_sprite(int registrador, int x, int y, int offset, int activation_bit);

/**
 * Modelar o background através de preenchimento dos blocos.
 * 
 * @param endereco_memoria    Endereço de memória correspondente ao bloco a ser preenchido
 * @param R         Componente da cor vermelha.
 * @param G         Componente da cor verde.
 * @param B         Componente da cor azul.
 * @return          1 caso operação seja bem sucedida, e 0 caso contrário.
*/
int set_background_block(int endereco_memoria, int R, int G, int B);

/**
 * Configura a cor base do background.
 * 
 * @param R   Componente da cor vermelha.
 * @param G   Componente da cor verde.
 * @param B   Componente da cor azul.
 * @return    1 caso operação seja bem sucedida, e 0 caso contrário.
*/
int set_background_color(int R, int G, int B);

/**
 * Posicionar um polígono na tela.
 * 
 * @param forma   Formato do polígono, 1 para triângulo e 0 para quadrado.
 * @param R   Componente da cor vermelha.
 * @param G   Componente da cor verde.
 * @param B   Componente da cor azul.
 * @param tamanho   Tamanho do polígono, de 1 a 15.
 * @param x   Coordenada x.
 * @param y   Coordenada y.
 * @param endereco   Endereço de memória onde o polígono será armazenado.
 * @return    1 caso operação seja bem sucedida, e 0 caso contrário.
*/
int define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco);

/**
 * Define um novo sprite.
 * 
 * @param R   Componente da cor vermelha.
 * @param G   Componente da cor verde.
 * @param B   Componente da cor azul.
 * @param endereco_memoria   Endereço de memória onde o sprite será armazenado
 * @return    1 caso operação seja bem sucedida, e 0 caso contrário.
*/
int write_sprite_mem(int R, int G, int B, int endereco_memoria);

/**
 * Responsável por atualizar as coordenadas x e y de um sprit móvel
 * de acordo ao seu ângulo de movimento e valor de deslocamento.
 * 
 * @param sp       Passagem por referência
 * @param mirror   Coordenadas do sprite
*/
void increase_coordinate(Sprite* sp, int mirror);

/**
 * Verifica se ocorreu uma colisão entre dois sprites quaisquer.
 * 
 * @param sp1   Passagem por referência da coord_x.
 * @param sp2   Passagem por referência da coord_y.
 * @return      1 caso operação seja bem sucedida, e 0 caso contrário.
*/
int collision(Sprite* sp1, Sprite* sp2);
