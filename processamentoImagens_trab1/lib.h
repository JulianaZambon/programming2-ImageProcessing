/* Autora: Juliana Zambon (jz22), GRR20224168 */

#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>

/* Estrutura para armazenar a imagem PGM */
struct imagemPGM
{
    int largura;            /* Largura da imagem em pixels */
    int altura;             /* Altura da imagem em pixels */
    int maximo;             /* Valor máximo de cinza (branco) */
    unsigned char **pixels; /* Matriz de pixels (valores de 0 a 255) */
    char tipo[4];           /* Tipo da imagem (P2 ou P5) */
};

/* Estrutura para armazenar o histograma LBP */
struct LBPHistograma
{
    int histograma[256]; /* Frequência de cada padrão LBP */
    double tamanho;
};

/* Aloca memória para a imagem PGM */
struct imagemPGM *alocar_imagem();

/* Aloca memória para o histograma LBP */
struct LBPHistograma *alocar_histograma();

/* Aloca memória para os pixels da imagem */
void alocar_pixels(struct imagemPGM *img);

/* Ignorar Linhas de Comentário: garantir que os comentários
(linhas que começam com #) sejam ignorados ao ler arquivos P2 e P5*/
void ignorar_comentarios(FILE *arquivo);

/* Preenche a matriz de pixels para o formato P2 */
struct imagemPGM *preencher_pixels_P2(FILE *arquivo, struct imagemPGM *img);

/* Preenche a matriz de pixels para o formato P5 */
struct imagemPGM *preencher_pixels_P5(FILE *arquivo, struct imagemPGM *img);

/* Função para ler a imagem PGM */
struct imagemPGM *ler_imagem(FILE *arquivo, struct imagemPGM *img);

/* Inicializa uma nova imagem para armazenar o resultado do LBP */
void inicializar_nova_imagem(struct imagemPGM *nova_img, struct imagemPGM *imagemPGM);

/* Calcula o LBP para um pixel específico da imagem */
/* Remover Bordas Durante a Convolução: garantir que as bordas da imagem original não sejam processadas.
Assegurando que o cálculo comece após as bordas (por exemplo, começando de 1 até altura - 1 e largura - 1).*/
void calcula_lbp(struct imagemPGM *img, struct imagemPGM *nova, int i, int j);

/* Gera a imagem LBP a partir da imagem original */
void gerar_lbp(struct imagemPGM *img, struct imagemPGM *nova);

/* Gera a imagem de saída no formato PGM */
/* Formato de Saída: capaz de determinar o formato da imagem de entrada
e gerar a saída correspondente no mesmo formato (P2 ou P5)*/
void gerar_imagem_saida(struct imagemPGM *nova, FILE *arquivo_saida);

/* Gera o histograma LBP de uma imagem */
/* Normalização do Histograma: garantindo que a contagem de pixels de cada tom seja dividida
pelo total de pixels na imagem.*/
void gerar_histograma(struct imagemPGM *nova, struct LBPHistograma *lbp_hist, char *arquivo_entrada);

/* Calcula a distância euclidiana entre dois histogramas LBP */
double distancia_euclidiana(struct LBPHistograma *hist1, struct LBPHistograma *hist2);

/* Lê um histograma LBP a partir de um arquivo de texto */
struct LBPHistograma *ler_histLBP(FILE *arquivo, struct LBPHistograma *histograma);

/* Comparar uma imagem de teste com todas as imagens da base de referência */
/* Exibir a imagem mais similar e a distância */
/* printf("Imagem mais similar: %s %.6f\n", img_similar, distancia); */
void encontrar_imagem_similar(char *diretorio, struct LBPHistograma *histograma_teste, double *distancia, char menor_distancia[256]);

/* Lê o conteúdo de um diretório e retorna uma lista de arquivos de imagem */
void ler_diretorio(char *nome_diretorio);

/* Converte uma imagem PGM para o formato LBP */
void converter_lbp(char arquivo_entrada[256]);

/* Libera a memória alocada para uma imagem PGM */
void liberar_imagem(struct imagemPGM *img);

#endif /* LIB_H */