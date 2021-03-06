/* 
 * 
 * File:   exclusao.h
 * Author: gilson
 *
 * Created on 28 de Fevereiro de 2018, 16:59
 */

#ifndef EXCLUSAO_H
#define	EXCLUSAO_H

#ifdef	__cplusplus
extern "C" {
#endif



#include <time.h>
#include "global.h"

#define QUANTIA_DE_ELEMENTOS 200
#define TAMANHO_DOS_ELEMENTOS 5
#define QUANTIA_DE_DADOS_DA_TABELA (QUANTIA_DE_ELEMENTOS * TAMANHO_DOS_ELEMENTOS)
#define TAMANHO_DOS_DADOS_NA_TABELA (QUANTIA_DE_DADOS_DA_TABELA + 6)

#define ENTROU_NA_AREA_SEGURA 0
#define SAIU_NA_AREA_SEGURA 1

#define TEMPO_PARA_ENVIAR_TABELA_DE_EXCLUSAO 10//100//20//5//2 Cada unidade eh 100mS
#define NAO_EXPIRA -1
#define TEMPO_PARA_EXPIRAR_TAG_QUE_SAIU_DA_AREA_SEGURA (TEMPO_PARA_ENVIAR_TABELA_DE_EXCLUSAO * 10)
    //#define TEMPO_MAXIMO_DE_SILENCIO_DO_ZIGBEE 30000
    //#define TEMPO_PARA_EXPIRAR_OS_DADOS_DO_ZIGBEE 75//20
#define TEMPO_PARA_EXPIRAR_TAG_DA_TABELA_DE_EXCLUSAO 1900//15000//5000
    //#define TEMPO_PARA_EXPIRAR_TAG_DA_TABELA_DE_EXCLUSAO 1000//15000//5000

    struct EstruturaTabelaDeExclusao {
        //time_t MomentoQueFoiCriada;//4
        char Elementos[QUANTIA_DE_ELEMENTOS][TAMANHO_DOS_ELEMENTOS];
        char Excluido[QUANTIA_DE_ELEMENTOS];
        //unsigned int ContagemParaExpirar[QUANTIA_DE_ELEMENTOS];
        signed int ContagemParaExpirar[QUANTIA_DE_ELEMENTOS];
        //int CheckSumDaRTabela;//2
        //char *PonteiroParaOsDadosRecebidos;//2
        //int CheckSumGerado;//2

        //int QuantiaDeDadosPresentes;//2
    };

#define TAMANHO_MAXIMO_DE_RECEPCAO_DE_PACOTE ((QUANTIA_DE_ELEMENTOS * TAMANHO_DOS_ELEMENTOS) + QUANTIA_DE_ELEMENTOS * 3)


    void processaTabelaDeExclusao(void);
    //int adicionaElementoDaTabelaDeExclusao (unsigned char *Epc, int Direcao);
    int adicionaElementoDaTabelaDeExclusao(unsigned char *Epc, char MsbNumeroDoPortal, char LsbNumeroDoPOrtal, int Direcao);
    int elementroPresenteNaTabelaDeExclusao(unsigned char *Epc);
    int removeElementoDaTabelaDeExclusao(unsigned char *Epc);
    void operacoesEmTickParaEnvioDaTabelaDeExclusao(void);
    int envioDeTabelaDeExclusao(void);
    void operacaoDeCodigoCorrenteParaExclusao(void);
    int trataRecepcaoDeTabelaDeExclusao(char *Dado, int Tamanho);
    void enviaEventoDeQueUmPedestreEntrouNaAreaSeguraNoZigBee(unsigned char *Epc, time_t Momento);
    void enviaEventoDeQueUmPedestreSaiuNaAreaSeguraNoZigBee(unsigned char *Epc, time_t Momento);
    void enviaEventoDeQueUmPedestreEntrouNaAreaSeguraNa485(unsigned char *Epc, time_t Momento);
    void enviaEventoDeQueUmPedestreSaiuNaAreaSeguraNa485(unsigned char *Epc, time_t Momento);
    void logicaDeRemocaoDeTabelaDeExclusao(void);
    void logicaDeRemocaoDeTabelaDeExclusaoParaPortal();
    void iniciaExclusao(void);
    int atualizaTabelaDeExclusaoParaEnvioPorWifi(void);



    extern struct EstruturaTabelaDeExclusao __attribute__((far)) TabelaDeExclusao;


#ifdef	__cplusplus
}
#endif
extern struct EstruturaTabelaDeExclusao __attribute__((far)) TabelaDeExclusao;

#endif	/* EXCLUSAO_H */

