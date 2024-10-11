/* neste trabalho será adotado o
formato de imagem PGM (Portable Grey Map)*/

/* existe o formato P2 (ASCII) e o formato P5 (binário).
seu programa deve aceitar ambos.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

/*
gera um mapa LBP para a imagem, onde cada pixel é
substituído por um valor de 8 bits (entre 0 e 255)
representando a relação entre o pixel central e
seus vizinhos.
*/

/* Função para calcular o LBP */
void lbp(struct imagemPGM *img, unsigned char **lbp)
{
    int i, j;
    int **pixels = img->pixels;
    int largura = img->largura;
    int altura = img->altura;

    // Calcula o valor LBP para cada pixel, exceto as bordas
    for (i = 1; i < altura - 1; i++)
    {
        for (j = 1; j < largura - 1; j++)
        {
            int pixel_central = pixels[i][j];
            unsigned char valor = 0;

            // Calcula o valor LBP baseado nos vizinhos
            valor |= (pixels[i - 1][j - 1] > pixel_central) << 7;
            valor |= (pixels[i - 1][j] > pixel_central) << 6;
            valor |= (pixels[i - 1][j + 1] > pixel_central) << 5;
            valor |= (pixels[i][j + 1] > pixel_central) << 4;
            valor |= (pixels[i + 1][j + 1] > pixel_central) << 3;
            valor |= (pixels[i + 1][j] > pixel_central) << 2;
            valor |= (pixels[i + 1][j - 1] > pixel_central) << 1;
            valor |= (pixels[i][j - 1] > pixel_central) << 0;

            lbp[i][j] = valor;
        }
    }
}

/* Função para extrair um vetor de características que sumarize o conteúdo da imagem */
void extrair_vetor_caracteristicas(struct imagemPGM *img, double *vetor)
{
    // Verifica se a imagem é válida
    if (img == NULL || img->pixels == NULL) {
        fprintf(stderr, "Erro: imagem inválida.\n");
        return;
    }

    int i, j;
    int **pixels = img->pixels;
    int largura = img->largura;
    int altura = img->altura;
    int maximo = img->maximo;  // Valor máximo de cinza na imagem
    int histograma[256] = {0};
    int total = 0;

    // Verifica se o valor máximo é maior que 255 (escala PGM não standard)
    if (maximo > 255) {
        fprintf(stderr, "Erro: valor máximo da imagem maior que 255.\n");
        return;
    }

    // Calcula o histograma e contabiliza pixels, descartando as bordas
    for (i = 1; i < altura - 1; i++) {
        for (j = 1; j < largura - 1; j++) {
            histograma[pixels[i][j]]++;  // Incrementa a contagem para o pixel correspondente
            total++;  // Contador total de pixels processados
        }
    }

    // Se não houver pixels válidos, evita divisão por zero
    if (total == 0) {
        fprintf(stderr, "Erro: imagem sem pixels processáveis.\n");
        return;
    }

    // Normaliza o histograma e preenche o vetor de características
    for (i = 0; i < 256; i++) {
        vetor[i] = (double)histograma[i] / total;
    }
}

/* Função para calcular a distância Euclidiana */
double distancias_euclidianas(double *v1, double *v2, int n);

/* Função para gerar a imagem LBP */
void gerar_imagem_lbp(struct imagemPGM *img, int **lbp);

/* Função para gravar o vetor LBP em um arquivo binário */
void gravar_vetor_lbp(const char *nome_arquivo, double *vetor_lbp, int tamanho);

/* Função para carregar o vetor LBP de um arquivo binário */
void carregar_vetor_lbp(const char *nome_arquivo, double *vetor_lbp, int tamanho);

/* Função para normalizar o histograma da imagem */
/* Esta função será usada para normalizar o histograma da imagem
dividindo os pixels pelo total, corrigindo assim diferenças de escala*/
void normalizar_histograma(struct imagemPGM *img, double *histograma_normalizado);

/* Função para ignorar comentários em arquivos PGM */
/* Ignora linhas de comentários iniciadas com # nos arquivos PGM */
void ignora_comentarios(FILE *arquivo);

/* Função para ler uma imagem PGM (suporta P2 e P5) */
struct imagemPGM *ler_imagem(const char *nome_arquivo);

/* Função para liberar a memória da imagem */
void liberar_imagem(struct imagemPGM *img);

/* Função para escrever uma imagem PGM (mantém o formato original: P2 ou P5) */
/* As funções de leitura e escrita de imagens garantem que o formato da imagem
de saída será o mesmo da imagem de entrada, seja P2 ou P5.*/
void escrever_imagem(const char *nome_arquivo, struct imagemPGM *img, const char *tipo);

/* Função para descartar bordas da imagem após o processo de convolução */
struct imagemPGM *descartar_bordas(struct imagemPGM *img);
