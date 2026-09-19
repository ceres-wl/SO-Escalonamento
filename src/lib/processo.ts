export class Processo {
    id: number;
    criacao: number; // Tempo de criação
    duracao: number;
    prioridade_estatica: number;
    prioridade_dinamica: number;

    constructor(id: number, criacao: number, duracao: number, prioridade_estatica: number){
        this.id = id;
        this.criacao = criacao;
        this.duracao = duracao;
        this.prioridade_estatica = prioridade_estatica;
        this.prioridade_dinamica = prioridade_estatica;
    }
}