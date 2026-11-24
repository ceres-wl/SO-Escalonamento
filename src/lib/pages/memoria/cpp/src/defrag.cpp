#include "operacoes.h"

//a ideia de cada algoritmo é analisar todos os blocos ocupados e reconstruir o vetor de memoria

SaidaDefrag defrag_end(Memoria &memoria){
    vector<Bloco> ocupados;
    int memoria_livre = 0;
    for(Bloco &b : memoria.mem){
        if(!b.livre) ocupados.push_back(b);
        else memoria_livre += b.tamanho;
    }

    memoria.mem.clear();

    int endr_atual = 0;
    int blocos_movidos = 0, mem_deslocada = 0;
    for(Bloco &b : ocupados){
        if(b.endereco != endr_atual){
            blocos_movidos++;
            mem_deslocada += b.tamanho;
            b.endereco = endr_atual;
        }
        endr_atual += b.tamanho;

        memoria.mem.push_back(b);
    }
    if(memoria_livre > 0){
        Bloco restante = create_bloco(0, endr_atual, memoria_livre, true);
        memoria.mem.push_back(restante);
    }
    return {blocos_movidos, mem_deslocada, memoria};
}

SaidaDefrag defrag_init(Memoria &memoria){
    vector<Bloco> ocupados;
    int memoria_livre = 0;
    for(Bloco &b : memoria.mem){
        if(!b.livre) ocupados.push_back(b);
        else memoria_livre += b.tamanho;
    }
    
    memoria.mem.clear();

    int endr_atual = memoria.tam_total;
    int blocos_movidos = 0, mem_deslocada = 0;

    for(int i = (int)ocupados.size() - 1 ; i >= 0 ; i--){
        Bloco &b = ocupados[i];
        
        endr_atual -= b.tamanho;
        
        if(b.endereco != endr_atual){
            blocos_movidos++;
            mem_deslocada += b.tamanho;
            b.endereco = endr_atual;
        }
        
        memoria.mem.push_back(b);
    }
    if(memoria_livre > 0){
        Bloco restante = create_bloco(0, 0, memoria_livre, true);
        memoria.mem.push_back(restante);
    }
    //inverter para garantir ordenacao pelo endereco no vetor de blocos da memoria
    reverse(memoria.mem.begin(), memoria.mem.end());
    return {blocos_movidos, mem_deslocada, memoria};
}

//funcao auxiliar para analisar quantos bytes sao movidos movendo k blocos para o inicio
int simular(int k, vector<Bloco> &ocupados, int memoria_livre){
    //k no inicio
    int endr_atual = 0, mem_deslocada = 0;
    for(int i = 0 ; i < k ; i++){
        Bloco b = ocupados[i];
        if(b.endereco != endr_atual){
            mem_deslocada += b.tamanho;
            b.endereco = endr_atual;
        }
        endr_atual += b.tamanho;
    }

    //resto no fim
    endr_atual += memoria_livre;
    for(int i = k ; i < ocupados.size() ; i++){
        Bloco b = ocupados[i];
        if(b.endereco != endr_atual){
            mem_deslocada += b.tamanho;
            b.endereco = endr_atual;
        }
        endr_atual += b.tamanho;
    }

    return mem_deslocada;
}

SaidaDefrag defrag_opt(Memoria &memoria){
    vector<Bloco> ocupados;
    int memoria_livre = 0;
    for(Bloco &b : memoria.mem){
        if(!b.livre) ocupados.push_back(b);
        else memoria_livre += b.tamanho;
    }

    int melhor = __INT_MAX__; //menor quant de bytes movidos
    int k_escolhido = 0;
    for(int k = 0 ; k <= ocupados.size() ; k++){
        int tentativa = simular(k, ocupados, memoria_livre);
        if(tentativa <= melhor){
            melhor = tentativa;
            k_escolhido = k;
        }
    }

    memoria.mem.clear();

    //k no inicio
    int endr_atual = 0, mem_deslocada = 0, blocos_movidos = 0;
    for(int i = 0 ; i < k_escolhido ; i++){
        Bloco &b = ocupados[i];
        if(b.endereco != endr_atual){
            blocos_movidos++;
            mem_deslocada += b.tamanho;
            b.endereco = endr_atual;
        }
        endr_atual += b.tamanho;

        memoria.mem.push_back(b);
    }

    if(memoria_livre > 0){
        Bloco restante = create_bloco(0, endr_atual, memoria_livre, true);
        memoria.mem.push_back(restante);
    }
    
    //resto no fim
    endr_atual += memoria_livre;
    for(int i = k_escolhido ; i < ocupados.size() ; i++){
        Bloco &b = ocupados[i];
        if(b.endereco != endr_atual){
            blocos_movidos++;
            mem_deslocada += b.tamanho;
            b.endereco = endr_atual;
        }
        endr_atual += b.tamanho;

        memoria.mem.push_back(b);
    }

    return {blocos_movidos, mem_deslocada, memoria};
}

SaidaDefrag defrag(Memoria &memoria, Opcao op){
    memoria.ptr_next_fit = 0;
    
    if(memoria.mem.size() <= 1) return {0, 0};

    if(op == INIT){
        return defrag_init(memoria);
    }
    else if(op == END){
        return defrag_end(memoria);
    }
    else{
        return defrag_opt(memoria);
    }
}
