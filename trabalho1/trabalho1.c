// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1correto.h"
#include <stdlib.h>
#define CURRENT_YEAR 2025

// Funções extras para me auxiliar a resolver as questões em momentos específicos

int isLeapYear(int year);                                                 // q1 e q2
int daysInMonth(int month, int year);                                     // q2
void tratmentString(char *str);                                           // q3
int reversingNumber(int exp, int overExp, int leftover);                  // q5
int pot10(int n);                                                         // q6
int countDigits(int n);                                                   // q6
int isWordHiddenHere(char game[8][10], char key[], int line, int column); // q7
DataQuebrada quebraData(char data[]);                                     // q1 e q2

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ // função utilizada para testes
    int i, fat = 1;

    for (i = x; i > 1; i--)
        fat = fat * i;

    return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida = 1;

    // quebrar a string data em strings sDia, sMes, sAno

    DataQuebrada dq = quebraData(data);

    // calculando se é ano bissexto
    int LeapYear = isLeapYear(dq.iAno);

    // Validando se a data é ou não válida utilizando a estrutura fornecida pelo professo

    if (dq.iDia < 1 || dq.iDia > 31)
    {
        datavalida = 0;
    }

    if (dq.iMes < 1 || dq.iMes > 12)
    {
        datavalida = 0;
    }

    if (dq.iAno > CURRENT_YEAR)
    {
        datavalida = 0;
    }

    if ((dq.iMes == 2 || dq.iMes == 4 || dq.iMes == 6 || dq.iMes == 9 || dq.iMes == 11) && dq.iDia > 30)
    {
        datavalida = 0;
    }

    if (dq.iDia == 29 && dq.iMes == 2 && LeapYear == 0)
    {
        datavalida = 0;
    }

    // printf("%s\n", data);

    if (datavalida)
        return 1;
    else
        return 0;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    // calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
    dma.qtdAnos = 0;
    dma.qtdMeses = 0;
    dma.qtdDias = 0;

    if (q1(datainicial) == 0)
    {
        dma.retorno = 2;
        return dma;
    }
    else if (q1(datafinal) == 0)
    {
        dma.retorno = 3;
        return dma;
    }
    else
    {
        // verifique se a data final não é menor que a data inicial

        DataQuebrada dqFinal = quebraData(datafinal);
        DataQuebrada dqInicial = quebraData(datainicial);

        if (dqInicial.iAno > dqFinal.iAno)
        {
            dma.retorno = 4;
            return dma;
        }
        else if ((dqInicial.iAno < dqFinal.iAno) && (dqInicial.iMes > dqFinal.iMes))
        {
            dma.retorno = 4;
            return dma;
        }
        else if ((dqInicial.iAno < dqFinal.iAno) && (dqInicial.iMes < dqFinal.iMes) && (dqInicial.iDia > dqFinal.iDia))
        {
            dma.retorno = 4;
            return dma;
        }

        // calcule a distancia entre as datas

        int current_day = dqInicial.iDia, current_month = dqInicial.iMes, current_year = dqInicial.iAno;

        // int final_day = rFinal.exit[0], final_month = rFinal.exit[1], final_year = rFinal.exit[2];

        int anos = dqFinal.iAno - dqInicial.iAno;
        int meses = dqFinal.iMes - dqInicial.iMes;
        int dias = dqFinal.iDia - dqInicial.iDia;

        if (dias < 0)
        {
            meses--;
            int mes_anterior = dqFinal.iMes - 1;
            if (mes_anterior == 0)
                mes_anterior = 12;
            int ano_anterior = (mes_anterior == 12) ? dqFinal.iAno - 1 : dqFinal.iAno;
            dias += daysInMonth(mes_anterior, ano_anterior);
        }
        if (meses < 0)
        {
            anos--;
            meses += 12;
        }

        dma.qtdAnos = anos;
        dma.qtdMeses = meses;
        dma.qtdDias = dias;
        dma.retorno = 1;

        // se tudo der certo
        dma.retorno = 1;
        return dma;
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0, i = 0;

    if (isCaseSensitive != 1)
    {
        tratmentString(texto);

        int cInt = (int)c;

        if (cInt >= 97 && cInt <= 122)
            cInt = cInt - 97 + 65;

        c = (char)cInt;
    }

    while (texto[i] != '\0')
    {
        if (c == texto[i])
        {
            qtdOcorrencias++;
        }

        i++;
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;

    int count, j = 0, k = 0, start, i = 0, control = 0;

    for (count = 0; strBusca[count] != '\0'; count++)
        ; // contando o tamanho da string de busca

    while (strTexto[i] != '\0')
    {
        if (strTexto[i] != -61)
        {

            if (k == count)
            {
                posicoes[j] = start + 1;
                posicoes[j + 1] = i - control;
                j += 2;
                k = 0;
                qtdOcorrencias++;
            }

            if (strBusca[k] == strTexto[i] && k == 0)
            {
                start = i - control;
            }

            if (strBusca[k] == strTexto[i])
            {
                k++;
            }
            else
            {
                k = 0;
            }
        }
        else
        {
            control++;
        }
        i++;
    }

    
    
    
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int exp = 1, leftover;
    int n = 0, overExp = 1;
    int hmt = 0;

    if (num >= -9 && num <= 9)
    {
        return num;
    }

    do
    {
        n = num / (exp * 10);
        exp *= 10;
        hmt++;
    } while (n > 9 || n < 0);

    overExp = exp;
    leftover = num;

    num = reversingNumber(exp, overExp, leftover);

    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;

    int digits_key = countDigits(numerobusca);
    int digits_number = countDigits(numerobase);

    int ak[20], an[20];
    int temp = numerobusca, i = 0;

    for (int e = pot10(digits_key - 1); e > 0; e /= 10)
    {
        ak[i++] = temp / e;
        temp = temp % e;
    }
    int key_len = i;

    i = 0;
    temp = numerobase;
    for (int e = pot10(digits_number - 1); e > 0; e /= 10)
    {
        an[i++] = temp / e;
        temp = temp % e;
    }
    int num_len = i;

    // --- procurar padrão ---
    int count = 0;
    for (int start = 0; start <= num_len - key_len; start++)
    {

        int match = 1;
        for (int k = 0; k < key_len; k++)
        {
            if (an[start + k] != ak[k])
            {
                match = 0;
                break;
            }
        }

        if (match)
            qtdOcorrencias++;
    }
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[5])
{
    int achou = 0;

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {

            if (matriz[i][j] == palavra[0])
            {
                if (isWordHiddenHere(matriz, palavra, i, j))
                    achou = 1;
            }
        }
    }
    return achou;
}

// implementação das funções

// DataQuebrada quebraData(char data[])
// {
//     DataQuebrada dq;
//     char sDia[3];
//     char sMes[3];
//     char sAno[5];
//     int i;

//     for (i = 0; data[i] != '/'; i++)
//     {
//         sDia[i] = data[i];
//     }
//     if (i == 1 || i == 2)
//     {                   // testa se tem 1 ou dois digitos
//         sDia[i] = '\0'; // coloca o barra zero no final
//     }
//     else
//     {
//         dq.valido = 0;
//         return dq;
//     }

//     int j = i + 1; // anda 1 cada para pular a barra
//     i = 0;

//     for (; data[j] != '/'; j++)
//     {
//         sMes[i] = data[j];
//         i++;
//     }

//     if (i == 1 || i == 2)
//     {                   // testa se tem 1 ou dois digitos
//         sMes[i] = '\0'; // coloca o barra zero no final
//     }
//     else
//     {
//         dq.valido = 0;
//         return dq;
//     }

//     j = j + 1; // anda 1 cada para pular a barra
//     i = 0;

//     for (; data[j] != '\0'; j++)
//     {
//         sAno[i] = data[j];
//         i++;
//     }

//     if (i == 2 || i == 4)
//     {                   // testa se tem 2 ou 4 digitos
//         sAno[i] = '\0'; // coloca o barra zero no final
//     }
//     else
//     {
//         dq.valido = 0;
//         return dq;
//     }

//     dq.iDia = atoi(sDia);
//     dq.iMes = atoi(sMes);
//     dq.iAno = atoi(sAno);

//     dq.valido = 1;

//     return dq;
// }

int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int daysInMonth(int month, int year)
{
    if (month == 2)
        return isLeapYear(year) ? 29 : 28;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    return 31;
}

void tratmentString(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= "z")
        {
            str[i] = str[i] - 'a' + 'A';
        }

        i++;
    }
}

int reversingNumber(int exp, int overExp, int leftover)
{
    int n = 0;

    if (overExp < 1)
    {
        return n;
    }

    n = leftover / overExp;
    leftover %= overExp;
    n *= exp / overExp;
    overExp /= 10;

    n += reversingNumber(exp, overExp, leftover);

    return n;
}

int pot10(int n)
{
    int r = 1;
    while (n--)
        r *= 10;

    return r;
}

int countDigits(int n)
{
    int d = 0;
    if (n == 0)
        return 1;

    while (n > 0)
    {
        d++;
        n /= 10;
    }
    return d;
}

int isWordHiddenHere(char game[8][10], char key[], int line, int column)
{
    // percorrendo na linha
    int k = 1;
    int final, start;

    for (int j = column + 1; j <= 10 && k < 5; j++)
    {
        if (game[line][j] == key[k])
            k++;
        else
            break;
    }
    if (k == 5)
        return 1;

    // percorrendo a linha invertida (De trás pra frente)

    for (int i = column; i >= 0; i--)
    {
        if (game[i][column] == key[k])
            k++;
        else
            break;
    }

    if (k == 5)
        return 1;

    // percorrendo a coluna

    k = 1;
    for (int i = line + 1; i <= 8 && k < 5; i++)
    {
        if (game[i][column] == key[k])
            k++;
        else
            break;
    }
    if (k == 5)
        return 1;

    // percorrendo a coluna invertida

    k = 1;
    for (int i = line - 1; i >= 0 && k < 5; i--)
    {
        if (game[i][column] == key[k])
            k++;
        else
            break;
    }
    if (k == 5)
        return 1;

    // achando na diagonal
    k = 1;
    for (int i = line + 1, j = column + 1; i < 8 && j < 10 && k < 5; i++, j++)
    {
        if (game[i][j] == key[k])
            k++;
        else
            break;
    }
    if (k == 5)
        return 1;

    // diagonal secundária

    k = 1;
    for (int i = line + 1, j = column - 1; i < 8 && j >= 0 && k < 5; i++, j--)
    {
        if (game[i][j] == key[k])
            k++;
        else
            break;
    }
    if (k == 5)
        return 1;

    // diagonal invertida

    for (int i = line - 1, j = column - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (game[i][j] == key[k])
            k++;
        else
            break;
    }
    if (k == 5)
        return 1;

    // diagonal secundária invertida

    for (int i = line - 1, j = column + 1; i >= 0 && j < 10; i--, j++)
    {
        if (game[i][j] == key[k])
            k++;
        else
            break;
    }
    if (k == 5)
        return 1;

    return 0;
}

DataQuebrada quebraData(char data[])
{
    char day_char[3], month_char[3], year_char[5];
    int day, month, year;
    int i = 0;

    int control = 0;
    int j = 0;

    DataQuebrada dq;

    while (data[i] != '\0')
    {

        if (data[i] == '/')
        {
            if (control == 0)
            {
                day_char[j] = '\0';
            }
            if (control == 1)
            {
                month_char[j] = '\0';
            }

            control++;
            j = 0;
        }

        if (control == 0)
        {
            day_char[j] = data[i];
            j++;
        }
        if (control == 1 && data[i] != '/')
        {
            month_char[j] = data[i];
            j++;
        }
        if (control == 2 && data[i] != '/')
        {
            year_char[j] = data[i];
            j++;
        }

        i++;
    }

    year_char[j] = '\0';

    day = atoi(day_char);
    month = atoi(month_char);
    year = atoi(year_char);

    dq.iDia = day;
    dq.iMes = month;
    dq.iAno = year;
    dq.valido = 1;

    return dq;
}
