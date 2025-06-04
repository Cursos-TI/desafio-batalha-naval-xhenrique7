#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0}; // inicializa tudo com 0 (água)

    // --------------------------
    // Posicionar os navios
    // --------------------------

    // Navio 1: Horizontal (linha 1, colunas 2 a 4)
    int linha1 = 1, coluna1 = 2;
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha1][coluna1 + i] = 3;
    }

    // Navio 2: Vertical (coluna 7, linhas 2 a 4)
    int linha2 = 2, coluna2 = 7;
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha2 + i][coluna2] = 3;
    }

    // Navio 3: Diagonal principal (linha 5, coluna 0 → 5,1 / 6,2 / 7,3)
    int linha3 = 5, coluna3 = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha3 + i][coluna3 + i] = 3;
    }

    // Navio 4: Diagonal secundária (linha 0, coluna 9 → 0,9 / 1,8 / 2,7)
    int linha4 = 0, coluna4 = 9;
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha4 + i][coluna4 - i] = 3;
    }

    // --------------------------
    // Habilidades (Cone, Cruz, Octaedro)
    // --------------------------

    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};

    // Construindo Cone (aponta para baixo)
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (2 - i) && j <= (2 + i))
                cone[i][j] = 1;
        }
    }

    // Construindo Cruz (centro e braços)
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
                cruz[i][j] = 1;
        }
    }

    // Construindo Octaedro (forma de losango)
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2)
                octaedro[i][j] = 1;
        }
    }

    // --------------------------
    // Função para aplicar habilidade ao tabuleiro
    // --------------------------
    void aplicarHabilidade(int matrizHabilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemX, int origemY) {
        for (int i = 0; i < TAM_HABILIDADE; i++) {
            for (int j = 0; j < TAM_HABILIDADE; j++) {
                int tabX = origemX + i - 2;
                int tabY = origemY + j - 2;
                if (tabX >= 0 && tabX < TAM_TABULEIRO && tabY >= 0 && tabY < TAM_TABULEIRO) {
                    if (matrizHabilidade[i][j] == 1 && tabuleiro[tabX][tabY] == 0)
                        tabuleiro[tabX][tabY] = 5;
                }
            }
        }
    }

    // --------------------------
    // Aplicar habilidades no tabuleiro
    // --------------------------

    aplicarHabilidade(cone, 2, 2);       // Cone no canto superior esquerdo
    aplicarHabilidade(cruz, 5, 5);       // Cruz no centro do tabuleiro
    aplicarHabilidade(octaedro, 8, 8);   // Octaedro no canto inferior direito

    // --------------------------
    // Exibir tabuleiro final
    // --------------------------

    printf("Tabuleiro com Navios (3) e Áreas de Habilidade (5):\n\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
