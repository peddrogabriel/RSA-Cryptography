#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

long long int eh_primo(long long int n)
{

    if(n <= 1){

        return 0;
    }

    if(n == 2){

        return 1;
    }

    else{

        if((n % 2) == 0){

            return 0;
        }
    }

    for(long long int i = 3; i <= n / i; i+=2){

        if(n % i == 0){
            
            return 0;
        }
    }

    return 1;
}

long long int mdc(long long int a, long long int b)
{
    long long int resto;

    if(b == 0)
    {
        return a;
    }

    while(a % b != 0)
    {
        resto = a % b;

        a = b;

        b = resto;
    }

    return b;
}

long long int coprimos(long long int a, long long int b)
{
    if(mdc(a,b) == 1){

        return 1;
    }

    else return 0;
}

long long int modular_otimizada(long long int a, long long int b, long long int modulo)
{
    long long int resultado = 0;

    while(b > 0)
    {
        if(b % 2 != 0){

            if(a >= modulo - resultado){

                resultado = a - (modulo - resultado);
            }

            else resultado = resultado + a;
    }

    if(a >= modulo - a){

        a = a - (modulo - a);
    }

    else a = a + a;

    b = b / 2;
    
    }

    return resultado;
}

long long int modular(long long int base, long long int expoente, long long int modulo)
{
    long long int resultado = 1;

    base = base % modulo;

    while(expoente > 0){

        if(expoente % 2 != 0){

            resultado = modular_otimizada(resultado, base, modulo);

        }

        base = modular_otimizada(base, base, modulo);

        expoente = expoente / 2;

    }
    
    return resultado;
}

long long int extensao(long long int a, long long int b)
{
    if(mdc(a,b) == 1){

    
        long long int x = 1;
        long long int x1 = 0;

        long long int y = 0;
        long long int y1 = 1;

        long long int resto, quociente;
        long long int modulo = b;

        while(b != 0){

            quociente = a / b;

            resto = a % b;

            a = b;

            b = resto;

            long long int aux_x = x;

            long long int aux_y = y;

            x = x1;

            x1 = aux_x - quociente * x1;

            y = y1;

            y1 = aux_y - quociente * y1;
        }

        x = (x % modulo + modulo) % modulo;

        return x;
    }

    else return -1;
}

long long int parametros(long long int p, long long int q, long long int *n, long long int *phi_euler)
{   
    if(p <= (LLONG_MAX / q) && p - 1 <= (LLONG_MAX / (q - 1))){

        *n = p * q;

        *phi_euler = (p-1) * (q-1); 

        return 1;
    }

    else return 0;
}
    
long long int expoente_privado(long long int e, long long int phi_euler)
{
    return extensao(e, phi_euler);  
}

typedef struct ChavesRSA{

    long long int e, d, n, phi_euler;

} ChavesRSA;

long long int chaves(long long int p, long long int q, long long int e, ChavesRSA *chaves)
{
    long long int ver1 = eh_primo(p);

    long long int ver2 = eh_primo(q);

    if(ver1 == 1 && ver2 == 1 && p != q){

        long long int ver3 = parametros(p, q, &chaves -> n, &chaves -> phi_euler);

        if(ver3 == 1){

            if(chaves -> n > 28){

                chaves -> e = e;

                if(e > 1 && e < chaves -> phi_euler && mdc(e, chaves -> phi_euler) ==1)
                {
                    chaves -> d = expoente_privado(chaves -> e, chaves -> phi_euler);

                    if(chaves -> d == -1){
                        
                        return 0;
                    }

                    return 1;
                }

                else return 0;
        
            }

            else return 0;
        }

        else return 0;
    }

    else return 0;
}

long long int conversao(char frase[], long long int convertida[])
{
    size_t tamanho = strlen(frase);

    for(long long int tam = 0; tam < tamanho; tam++)
    {
        if((frase[tam] < 65 || frase[tam] > 90) && frase[tam] != 32)
        {
            fprintf(stderr, "Mensagem invalida! Digite apenas letras maiusculas, sem pontuacao.\n");

            return 0;
        }

        if(frase[tam] == ' '){

            convertida[tam] = 28;
        }

        else{

            convertida[tam] = frase[tam] - 63;

        }
    }

    return 1; 
}

void criptografar(long long int mensagem_convertida[], long long int criptografados[], long long int caracteres, ChavesRSA *chaves)
{
    for(long long int i = 0; i < caracteres; i++){

        criptografados[i]= modular(mensagem_convertida[i],chaves -> e, chaves -> n);
    }
}

long long int salvar_criptografado(long long int criptografados[], long long int quantidade, char nome_arquivo[])
{
    FILE *arquivo;

    arquivo = fopen(nome_arquivo, "w");

    if(arquivo == NULL){

        return 0;
    }

    int sucesso = 1;

    for(long long int i = 0; i < quantidade; i++){

        if(fprintf(arquivo, "%lld ", criptografados[i]) < 0){

            sucesso = 0;

            break;
        }
    }

    if(fclose(arquivo) == EOF){

        sucesso = 0;
    }

    return sucesso;
}

long long int *ler_criptografado(char nome_arquivo[], long long int *quantidade)
{
    FILE *arquivo;

    *quantidade = 0;

    long long int numero;

    arquivo = fopen(nome_arquivo, "r");

    if(arquivo != NULL){

       int leitura;

        while((leitura = fscanf(arquivo, "%lld", &numero)) == 1){

            (*quantidade)++;
        }

        if(leitura == 0){

            printf("Erro! O arquivo contem dados invalidos.\n");

            fclose(arquivo);

            return NULL;
        }

        if(*quantidade == 0)
        {
            printf("Erro! Nao existem numeros para serem lidos");

            fclose(arquivo);

            return NULL;     
        }

        long long int *armazenar = malloc((*quantidade) * sizeof(long long int));

        if(armazenar == NULL)
        {
            printf("Erro ao alocar memoria\n");

            fclose(arquivo);

            return NULL;
        }

        rewind(arquivo);

        for(long long int i = 0; i < *quantidade; i++)
        {
            if(fscanf(arquivo, "%lld", &armazenar[i]) != 1)
            {
                printf("Erro! Falha ao ler os numeros do arquivo.\n");

                free(armazenar);

                fclose(arquivo);

                return NULL;
            }
        }

        fclose(arquivo);

        return armazenar;
    }
    
    else return NULL;
}

void descriptografar(long long int criptografados[], long long int mensagem[], long long int quantidade, ChavesRSA *chaves)
{
    for(long long int i = 0; i < quantidade; i++){

        mensagem[i] = modular(criptografados[i], chaves->d, chaves->n);
    }
}

void desconversao(long long int mensagem[], char frase[], long long int quantidade)
{
    for(long long int i = 0; i < quantidade; i++){

        if(mensagem[i] == 28)
        {
            frase[i] = ' ';
        }

        else{
            
            frase[i] = mensagem[i] + 63;
        }
    }

    frase[quantidade] = '\0';
}

long long int salvar_descriptografado(char frase[], char nome_arquivo[])
{
    FILE *novo_arquivo;

    novo_arquivo = fopen(nome_arquivo, "w");

    if(novo_arquivo == NULL){

        return 0;
    }

    int sucesso = 1;

    if(fprintf(novo_arquivo, "%s", frase) < 0){

        sucesso = 0;
    }
    
    if(fclose(novo_arquivo) == EOF){

        sucesso = 0;
    }

    return sucesso;
}

long long int chave_publica(ChavesRSA *chaves, char nome_arquivo[])
{
    FILE *arquivo_publico;

    arquivo_publico = fopen(nome_arquivo,"w");

    if(arquivo_publico == NULL){

        return 0;
    }

    int sucesso = 1;
    
    if(fprintf(arquivo_publico, "%lld\n%lld", chaves->n, chaves->e) < 0){

        sucesso = 0;
    }

    if(fclose(arquivo_publico) == EOF){
        
        sucesso = 0;
    }

    return sucesso;   
}

int ler_chave_publica(char nome_arquivo[], ChavesRSA *chaves)
{
    FILE *arquivo_chave_publica;

    arquivo_chave_publica = fopen(nome_arquivo, "r");

    if(arquivo_chave_publica != NULL)
    {
        if(fscanf(arquivo_chave_publica, "%lld%lld", &chaves -> n, &chaves -> e) == 2){

            fclose(arquivo_chave_publica);

            return 1;
        }

        else{

            fclose(arquivo_chave_publica);

            return 0;
        } 
    }

    else return 0;
}

int main(int argc, char *argv[])
{
    char *mensagem;

    ChavesRSA minha_chave;

    if(argc < 2)
    {
        fprintf(stderr, "Argumentos insuficientes.\n");
        return 1;
    }

    if(strcmp(argv[1], "criptografar") == 0){

        if(argc != 5)
        {
            fprintf(stderr, "Uso: programa criptografar <mensagem> <e> <n>\n");
            return 1;
        }

        mensagem = argv[2];

        size_t caracteres = strlen(mensagem);

        if(caracteres == 0)
        {
            fprintf(stderr, "Mensagem vazia.\n");
            return 1;
        }

        long long int *mensagem_convertida = malloc(caracteres * sizeof(long long int));

        long long int *criptografados = malloc(caracteres * sizeof(long long int));

        if(mensagem_convertida == NULL || criptografados == NULL)
        {
            fprintf(stderr, "Erro ao alocar memoria.\n");

            free(mensagem_convertida);
            free(criptografados);

            return 1;
        }

        int ver = conversao(mensagem, mensagem_convertida);

        if(ver == 0){

            free(mensagem_convertida);
            free(criptografados);

            return 1;
        }

        else{

            minha_chave.e = strtoll(argv[3], NULL, 10);
            minha_chave.n = strtoll(argv[4], NULL, 10);

            criptografar(mensagem_convertida, criptografados, caracteres, &minha_chave);

            for(long long int i = 0; i < caracteres; i++){

                fprintf(stdout, "%lld ", criptografados[i]);
            }

            printf("\n");

            free(mensagem_convertida);
            free(criptografados);

            return 0;
        }

    }

    else if(strcmp(argv[1], "descriptografar") == 0)
    {
        if(argc != 5)
        {
            fprintf(stderr, "Uso: programa descriptografar <cifra> <d> <n>\n");
            return 1;
        }

        mensagem = argv[2];

        minha_chave.d = strtoll(argv[3], NULL, 10);
        minha_chave.n = strtoll(argv[4], NULL, 10);

        size_t tamanho = strlen(mensagem);

        long long int *criptografados = malloc((tamanho + 1) * sizeof(long long int));

        if(criptografados == NULL)
        {
            fprintf(stderr, "Erro ao alocar memoria.\n");
            return 1;
        }

        long long int quantidade = 0;

        char *palavra = strtok(mensagem, " ");

        while(palavra != NULL)
        {
            criptografados[quantidade] = strtoll(palavra, NULL, 10);

            quantidade++;

            palavra = strtok(NULL, " ");
        }

        if(quantidade == 0)
        {
            fprintf(stderr, "Nenhum numero foi informado.\n");
            free(criptografados);
            return 1;
        }

        long long int *mensagem_recuperada = malloc(quantidade * sizeof(long long int));
        char *frase_recuperada = malloc((quantidade + 1) * sizeof(char));

        if(mensagem_recuperada == NULL || frase_recuperada == NULL)
        {
            fprintf(stderr, "Erro ao alocar memoria.\n");

            free(criptografados);
            free(mensagem_recuperada);
            free(frase_recuperada);

            return 1;
        }

        descriptografar(criptografados, mensagem_recuperada, quantidade, &minha_chave);

        desconversao(mensagem_recuperada, frase_recuperada, quantidade);

        printf("%s\n", frase_recuperada);

        free(criptografados);
        free(mensagem_recuperada);
        free(frase_recuperada);

        return 0;
    }

    else
    {
        if(argc != 4){

            fprintf(stderr, "Uso: programa <p> <q> <e>\n");

            return 1;
        }
        
        long long int p = strtoll(argv[1], NULL, 10);

        long long int q = strtoll(argv[2], NULL, 10);

        long long int e = strtoll(argv[3], NULL, 10);
        
        long long int resultado = chaves(p, q, e, &minha_chave);

        if(resultado == 0)
        {
            fprintf(stderr, "Erro: parametros invalidos.\n");

            return 1;
        }

        printf("%lld %lld %lld\n", minha_chave.n, minha_chave.e, minha_chave.d);
    }

    return 0;
}