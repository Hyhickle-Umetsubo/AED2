/*//------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
Hyhickle Ryozo Umetsubo Gonçalves - AED2 (Exercício Dijkstra)
Condição 1 - Permitir o armazenamento de até 20 vértices
Condição 2 - Fazer a leitura dos pesos das arestas de cada vértice
Condição 3 - Considerar sempre vértices positivos
Condição 4 - Mostrar o caminho mínimo entre dois vértices solicitados
*/
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funções Usadas ao longo do Programa
void menu_inicial();
void incluir_vertice();
void listar_vertice();
void gerar_matriz();

//Buffers do Programa onde ficam todas as variaveis e os vertices
void *buffer_variaveis;
void *buffer_vertices;

typedef struct variaveis
{
    int numero_vertices;
    int escolha_menu;
    int contador;
    int contador2;
    int aux;
    int aux_peso;
    int linha;
    int coluna;
    int numero_ligacoes;
    int vertice_inicial;
    int proximo_vertice;
    int minima_distancia;
} Variaveis;

typedef struct vertices
{
    char vertice[20];
} Vertices;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que Adiciona Arestas, Pesos e calcula a Distancia Minima entre os Vertices
void gerar_matriz()
{
    Variaveis *a;
    a = buffer_variaveis;

    int matriz[a->numero_vertices][a->numero_vertices];

    //Esse laço faz com que a matriz seja preenchida inicialmente com zeros
    for (a->linha = 0; a->linha < a->numero_vertices; a->linha++)
    {
        for (a->coluna = 0; a->coluna < a->numero_vertices; a->coluna++)
        {
            matriz[a->linha][a->coluna] = 0;
        }
    }

    for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
    {
        do
        {
            printf("\nO item '%d' tem quantas ligacoes: ", a->contador + 1);
            scanf("%d", &a->numero_ligacoes);
            if (a->numero_ligacoes > a->numero_vertices)
            {
                printf("\nINVALIDO - Numero de Ligacoes maior que a Quantidade de Vertices\n");
            }
        } while (a->numero_ligacoes > a->numero_vertices);

        for (a->contador2 = 0; a->contador2 < a->numero_ligacoes; a->contador2++)
        {
            do
            {
                printf("Tem ligacao com: ");
                scanf("%d", &a->aux);
                if ((a->aux > a->numero_vertices) || (a->aux == 0))
                {
                    printf("\nINVALIDO - Ligacao com Vertice Inexistente\n");
                }
                else
                {
                    if (((matriz[a->contador][a->aux - 1]) && (matriz[a->aux - 1][a->contador])) != 0)
                    {
                        printf("\nEssa aresta ja existia, e sera alterada pelo novo peso\n");
                    }
                }
            } while ((a->aux > a->numero_vertices) || (a->aux == 0));
            printf("Qual o peso da Aresta: ");
            scanf("%d", &a->aux_peso);
            matriz[a->contador][a->aux - 1] = a->aux_peso;
            matriz[a->aux - 1][a->contador] = a->aux_peso;
        }
    }
    printf("\n\n");
    listar_vertice();

    printf("-----MATRIZ DE ADJACENCIA-----\n\n");
    //Laços para imprimir as Matrizes de forma Organizada
    printf("\t%d", 1);
    for (a->contador = 1; a->contador < a->coluna; a->contador += 1)
    {
        printf("\t%d", a->contador + 1);
    }
    printf("\n");

    printf("   ");
    for (a->contador = 0; a->contador < 10 * a->coluna; a->contador += 1)
    {
        printf("-");
    }
    printf("\n");

    for (a->linha = 0; a->linha < a->numero_vertices; a->linha++)
    {
        printf("%2d|", a->linha + 1);
        for (a->coluna = 0; a->coluna < a->numero_vertices; a->coluna++)
        {
            printf("\t%d", matriz[a->linha][a->coluna]);
        }
        printf("\n");
    }

    //Calcula o caminho minimo entre os vertices
    printf("\n\nDeseja calcular o caminho minimo entre os Vertices: \n");
    printf("1-Sim\n");
    printf("2-Nao\n");
    printf("Digite sua Escolha: ");
    scanf("%d", &a->escolha_menu);

    int cost[a->numero_vertices][a->numero_vertices];
    int distancia[a->numero_vertices];
    int vertice_visitado[a->numero_vertices];
    int antecessor[a->numero_vertices];

    switch (a->escolha_menu)
    {
    case 1:
        printf("\nDefina o Vertice Inicial: ");
        scanf("%d", &a->vertice_inicial);

        for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
        {
            for (a->contador2 = 0; a->contador2 < a->numero_vertices; a->contador2++)
            {
                if (matriz[a->contador][a->contador2] == 0)
                {
                    cost[a->contador][a->contador2] = 9999;
                }
                else
                {
                    cost[a->contador][a->contador2] = matriz[a->contador][a->contador2];
                }
            }
        }

        for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
        {
            distancia[a->contador] = cost[(a->vertice_inicial) - 1][a->contador];
            antecessor[a->contador] = (a->vertice_inicial) - 1;
            vertice_visitado[a->contador] = 0;
        }
        distancia[(a->vertice_inicial) - 1] = 0;
        vertice_visitado[(a->vertice_inicial) - 1] = 1;
        a->aux = 1;

        while (a->aux < (a->numero_vertices) - 1)
        {
            a->minima_distancia = 9999;
            for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
            {

                if (distancia[a->contador] < a->minima_distancia && ! vertice_visitado[a->contador])
                {
                    a->minima_distancia = distancia[a->contador];
                    a->proximo_vertice = a->contador;
                }
            }

            vertice_visitado[a->proximo_vertice] = 1;

            for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
            {
                if (!vertice_visitado[a->contador])
                {
                    if ((a->minima_distancia + cost[a->proximo_vertice][a->contador]) < distancia[a->contador])
                    {
                        distancia[a->contador] = a->minima_distancia + cost[a->proximo_vertice][a->contador];
                        antecessor[a->contador] = a->proximo_vertice;
                    }
                }
            }
            a->aux++;
        }

        for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
        {
            if (a->contador != (a->vertice_inicial) - 1)
            {
                printf("A distancia ate o Vertice %d tem peso equivalente a %d\n", (a->contador) + 1, distancia[a->contador]);
                printf("O caminho: %d", (a->contador) + 1);

                a->contador2 = a->contador;
                do
                {
                    a->contador2 = antecessor[a->contador2];
                    printf("<-%d", (a->contador2) + 1);
                } while (a->contador2 != (a->vertice_inicial) - 1);
            }
            printf("\n");
        }
        break;
    case 2:
        return;
        break;
    default:
        printf("Opcao Invalida");
        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que adiciona Vertices
void incluir_vertice()
{
    Variaveis *a;
    a = buffer_variaveis;
    Vertices *v;
    buffer_vertices = (Vertices *)realloc(buffer_vertices, (sizeof(Vertices) * (a->numero_vertices + 1)));
    if (buffer_vertices == NULL)
    {
        printf("\n---Erro, falta de memoria---\n");
        exit(1);
    }
    v = buffer_vertices + (sizeof(Vertices) * (a->numero_vertices));
    printf("\nInsira o nome do Vertice: ");
    scanf("%s", v->vertice);

    printf("-----VERTICE ADICIONADO COM SUCESSO-----\n");
    a->numero_vertices++;
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que lista todos os Vertices
void listar_vertice()
{
    Variaveis *a;
    Vertices *v;
    a = buffer_variaveis;
    v = buffer_vertices;
    printf("\n-----VERTICES INSERIDOS-----\n");
    for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
    {
        printf("\n%d - %s ", a->contador + 1, v->vertice);
        v++;
    }
    printf("\n\n");
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que chama o menu do programa
void menu_inicial()
{
    Variaveis *a;
    a = buffer_variaveis;
    for (;;)
    {
        printf("\n\nDeseja inserir algum vertice: \n");
        printf("1-Sim\n");
        printf("2-Nao\n");
        printf("Digite sua Escolha: ");
        scanf("%d", &a->escolha_menu);

        switch (a->escolha_menu)
        {
        case 1:
            incluir_vertice();
            break;
        case 2:
            printf("\n\nO que deseja fazer agora: \n");
            printf("1-Adicionar Pesos nas Arestas e Calcular o Caminho Minimo\n");
            printf("2-Finalizar o Programa\n");
            printf("Digite sua Escolha: ");
            scanf("%d", &a->escolha_menu);
            if (a->escolha_menu == 1)
            {
                listar_vertice();
                gerar_matriz();
            }
            if (a->escolha_menu == 2)
            {
                free(buffer_variaveis);
                free(buffer_vertices);
                return;
            }
            break;
        default:
            printf("Opcao Invalida");
            break;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    Variaveis *a;
    buffer_variaveis = malloc(sizeof(Variaveis));
    if (buffer_variaveis == NULL)
    {
        printf("Erro");
        exit(1);
    }
    a = buffer_variaveis;
    a->numero_vertices = 0;
    menu_inicial();
}