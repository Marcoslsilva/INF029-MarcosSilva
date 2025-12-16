#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

// M- garantindo que todas as posicoes sao NULL
int *vetorPrincipal[TAM];
int howMuchAssigned[TAM];
/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int retorno = 0;
    int *p = malloc((tamanho + 1) * sizeof(int));
    posicao--;
    // M- validações:

    // se posição é um valor válido {entre 1 e 10}
    if (ehPosicaoValida(posicao))
    {
        retorno = POSICAO_INVALIDA;
    }
    // a posicao pode já existir estrutura auxiliar
    else if (vetorPrincipal[posicao])
    {
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    }
    // o tamanho ser muito grande
    else if (p == NULL)
    {
        retorno = SEM_ESPACO_DE_MEMORIA;
    }
    // o tamanho nao pode ser menor que 1
    else if (tamanho < 1)
    {
        retorno = TAMANHO_INVALIDO;
    }
    else
    {
        // deu tudo certo, crie

        p[0] = tamanho;

        vetorPrincipal[posicao] = p;
        howMuchAssigned[posicao]++;

        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;
    posicao--;

    existeEstruturaAuxiliar = vetorPrincipal[posicao] ? 1 : 0;
   
    posicao_invalida = ehPosicaoValida(posicao) ? posicao_invalida : 0;

    if (posicao_invalida)
        retorno = POSICAO_INVALIDA;
    else
    {
        // testar se existe a estrutura auxiliar
        if (existeEstruturaAuxiliar)
        {
            int *p = vetorPrincipal[posicao];
            temEspaco = howMuchAssigned[posicao] - p[0] == 0 ? 0 : 1;
            if (temEspaco)
            {
                // insere
                p[howMuchAssigned[posicao] + 1] = valor;

                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = SUCESSO;
    posicao--;

    if (ehPosicaoValida(posicao))
    {
        retorno = POSICAO_INVALIDA;
    }
    else if (vetorPrincipal[posicao] == NULL)
    {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else if (howMuchAssigned[posicao] == 0)
    {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }
    else
    {
        int *p = vetorPrincipal[posicao];

        p[howMuchAssigned[posicao]] = 0;
        howMuchAssigned[posicao]--;
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = SUCESSO;
    int control = 0;
    int *p = vetorPrincipal[posicao];
    int isNumberFound = 0;
    posicao--;

    if (ehPosicaoValida(posicao))
    {
        retorno = POSICAO_INVALIDA;
    }
    else if (vetorPrincipal[posicao] == 0)
    {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else if (howMuchAssigned[posicao] == 0)
    {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }
    else
    {
        int limit = howMuchAssigned[posicao];

        for (int i = 1; i <= limit; i++)
        {
            if (control == 1)
            {
                p[i - 1] = p[i];
                p[i] = 0;
            }

            if (p[i] == valor && isNumberFound == 0)
            {
                p[i] = 0;
                control = 1;
                isNumberFound = 1;
                howMuchAssigned[posicao]--;
            }
        }
    }

    if (control == 0)
    {
        retorno = NUMERO_INEXISTENTE;
    }

    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 0 || posicao > TAM - 1)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
    {
        retorno = SUCESSO;
    }

    return retorno;
}

// M- Uma função que será utilizada para comparar e ordenar os vetores
int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x - y;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = 0;
    int *p = vetorPrincipal[posicao];
    posicao--;

    if (ehPosicaoValida(posicao))
    {
        retorno = POSICAO_INVALIDA;
    }
    else if (vetorPrincipal[posicao] == 0)
    {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else
    {
        for (int i = 1; i <= howMuchAssigned[posicao]; i++)
        {
            vetorAux[i - 1] = p[i];
        }
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int *p;
    int retorno = 0;

    if (ehPosicaoValida(posicao))
    {
        retorno = POSICAO_INVALIDA;
    }
    else if (vetorPrincipal[posicao] == NULL)
    {
        
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else
    {
        p = vetorPrincipal[posicao];
        for (int i = 1; i < howMuchAssigned[posicao]; i++)
        {
            vetorAux[i - 1] = p[i];
        }
    }

    qsort(vetorAux, howMuchAssigned[posicao], sizeof(int), compare_ints);

    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = 0;
    int control = 0, j = 1, k = 0;

    for (size_t i = 0; i < TAM; i++)
    {
        int *p = vetorPrincipal[i];

        if (vetorPrincipal[i] == NULL)
        {
            control++;
        }
        else
        {
            while (j <= howMuchAssigned[i])
            {
                vetorAux[k] = p[j];
                k++;
                j++;
            }

            j = 1;
        }
    }

    if (control == TAM)
    {
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int control = 0, j = 1, k = 0;

    for (size_t i = 0; i < 10; i++)
    {
        int *p = vetorPrincipal[i];

        if (howMuchAssigned[i] == 0)
        {
            control++;
        }
        else
        {
            while (j <= howMuchAssigned[i])
            {
                vetorAux[k] = p[j];
                k++;
                j++;
            }
        }

        if (control == 10)
        {
            retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
        }
        else
        {

            qsort(vetorAux, k, sizeof(int), compare_ints);
        }
    }

    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int retorno = SUCESSO;
    posicao--;

    if (ehPosicaoValida(posicao))
    {
        retorno = POSICAO_INVALIDA;
    }
    else if (vetorPrincipal[posicao] == NULL)
    {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else
    {
        int *p = vetorPrincipal[posicao];
        int sum = novoTamanho + p[0];
        if (sum > 0)
        {
            if (sum < p[0])
            {
                int limit = howMuchAssigned[posicao];
                int control = sum + 1;
                while (control <= limit)
                {
                    p[control] = 0;
                    control++;
                    howMuchAssigned[posicao]--;
                }
            }
            int *newArray = realloc(p, (sum + 1) * sizeof(int));

            if (newArray == NULL)
            {
                retorno = SEM_ESPACO_DE_MEMORIA;
            }
            else
            {
                p = newArray;

                int start = p[0] + 1;

                if (sum > p[0])
                {

                    for (int i = start; i <= sum; i++)
                    {
                        p[i] = 0;
                    }
                }

                p[0] = sum;

                vetorPrincipal[posicao] = p;
            }
        }
        else
        {
            retorno = NOVO_TAMANHO_INVALIDO;
        }
    }

    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/

int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    int retorno = 0;
    posicao--;

    if (ehPosicaoValida(posicao))
    {
        retorno = POSICAO_INVALIDA;
    }
    else if (vetorPrincipal[posicao] == NULL)
    {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else if (howMuchAssigned[posicao] == 0)
    {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }
    else
    {
        retorno = howMuchAssigned[posicao];
    }

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/

List *newList()
{

    List *newList = malloc(sizeof(List));
    newList->head = NULL;

    return newList;
}

No *create_node(int key)
{
    No *newNode = malloc(sizeof(No));
    newNode->conteudo = key;
    newNode->prox = NULL;
    return newNode;
}

List *insertionNode(No *node, List *list)
{

    if (list->head == NULL)
    {
        list->head = node;
        return list;
    }
    else
    {
        No *validator = list->head;

        while (validator->prox)
        {
            validator = validator->prox;
        }

        validator->prox = node;

        return list;
    }
}

No *montarListaEncadeadaComCabecote()
{
    for (size_t i = 0; i < TAM; i++)
    {
        int *address = vetorPrincipal[i];
        List *list = newList();
        No *node;

        if (howMuchAssigned[i])
        {
            for (int i = 1; i <= address[0]; i++)
            {
                if (address[i])
                {
                    node = create_node(address[i]);
                    list = insertionNode(node, list);
                }
                else
                {
                    break;
                }
            }
        }
    }

    return NULL;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(List *inicio, int vetorAux[])
{
    No *validator = inicio->head;
    int i = 0;

    while (validator->prox)
    {
        vetorAux[i] = validator->conteudo;
        validator = validator->prox;
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(List *inicio)
{
    No *validator = inicio->head->prox;

    if (inicio->head == NULL)
    {
        free(inicio);
    }
    else if (validator->prox == NULL)
    {
        free(inicio);
        free(validator);
    }
    else
    {
        while (validator != NULL)
        {
            No *next = validator->prox;
            free(inicio);
            free(validator);

            while (next)
            {
                validator = next->prox;
                free(next);
                next = validator;
                free(validator);
            }
        }
    }
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

*/

void inicializar()
{
    for (int i = 0; i < 10; i++)
    {
        vetorPrincipal[i] = NULL;
        howMuchAssigned[i] = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for (size_t i = 0; i < TAM; i++)
    {
        int *p = vetorPrincipal[i];
        int limit = howMuchAssigned[i];

        if (p[0] != 0)
        {
            for (int j = 1; j <= limit; j++)
            {
                p[j] = 0;
                howMuchAssigned[i]--;
            }

            free(vetorPrincipal[i]);
        }
    }
}

void dobrar(int *x){
    *x *= 2;
}